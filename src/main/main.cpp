#include <Wire.h>
#include <SPI.h>
#include <array>


#include "utils.h"
#include "eepromManager.h"
#include "RTCController.h"
#include "routinesController.h"
#include "relayController.h"
#include "webSocket.h"
#include "interruptionHandlers.h"
#include "httpServer.h"
#include "WifiManager.h"

Preferences preferences;
RelayController relays[NUMBER_OF_RELAYS];
WebSocket webSocket;
HTTPServer httpServer;
SemaphoreHandle_t toggleRelayInterruptionSemaphore;
SemaphoreHandle_t changeWifiModeInterruptionSemaphore;

volatile unsigned long fisicalButtonsLastClickTime = 0;

void setup() {
  Serial.begin(115200);

  toggleRelayInterruptionSemaphore = xSemaphoreCreateBinary();
  changeWifiModeInterruptionSemaphore = xSemaphoreCreateBinary();
  if(toggleRelayInterruptionSemaphore == NULL || changeWifiModeInterruptionSemaphore == NULL) {
    Serial.println("Failed to create semaphore");
    while (1);
  }

  relays[0] = RelayController(14,34,1);
  relays[1] = RelayController(27,35,2);
  relays[2] = RelayController(26,32,3);
  relays[3] = RelayController(25,33,4);

  WifiManager::begin();
  webSocket.begin();
  httpServer.begin();

	if(!RTCController::rtc.begin()){
		while(1){
			Serial.println("DS3231 não encontrado");
		};
	}
	if(RTCController::rtc.lostPower()){
		Serial.println("DS3231 OK!");
		RTCController::rtc.adjust(DateTime(2023, 5, 06, 15, 00, 00)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
	}
}

int lastMinuteInLoop = -1;
int lastChangeWifiClick = 0;
int changeWifiButtonStatus = 0;
bool resetWifi = false;
void loop(){
  
  NowStruct now = RTCController::getNow();
  if(lastMinuteInLoop != now.minute){
    String hours = numberToTwoChars(now.hour);
    String minutes = numberToTwoChars(now.minute);
    String buf = "{ \"hora\" : \""+ hours + "\", \"minuto\" : \""+ minutes +"\", \"dia\": \""+RTCController::weekDays[now.day]+"\"}";
    webSocket.emitEvent("{\"event\": \"clockUpdate\", \"buffer\":"+buf+"}");

    lastMinuteInLoop = now.minute;
    int currentMinuteOfTheDay = (now.hour*60) + now.minute;
    bool deviceMustBeTurnedOn = false;

    std::list<RoutineStruct> routines = RoutinesController::getRoutines();
    bool portsStatus[NUMBER_OF_RELAYS] = {0};

    if(routines.size() > 0){
      for(RoutineStruct routine: routines){
        int minuteOfTheDayToTurnOn = (routine.hourToTurnOn*60) + routine.minuteToTurnOn;
        int minuteOfTheDayToTurnOff = (routine.hourToTurnOff*60) + routine.minuteToTurnOff;

        String routineDaysBinary = String(routine.days, BIN);
        if(routineDaysBinary.length() < 7){
          int numberOfZeros = 7 - routineDaysBinary.length();
          String complement = "";
          for(int i = 0; i< numberOfZeros; i++){
            complement+="0";
          }
          routineDaysBinary = complement+routineDaysBinary;
        }


        bool routineIsActivedToday = false;
        // So o dia atual está ativo na rotina

        // Se estava no dia anterior e estamos no intervalo antes da hora de desligar
        int previousDayIndex = now.day == 0? 6:now.day-1;
        routineIsActivedToday = routineDaysBinary.charAt(now.day) == '1' || (minuteOfTheDayToTurnOff < minuteOfTheDayToTurnOn && routineDaysBinary.charAt(previousDayIndex) == '1');

        if(routineIsActivedToday){
          if(!portsStatus[routine.relayIndex-1]){
            portsStatus[routine.relayIndex-1] = RoutinesController::shouldItbeTurnedOn(
              currentMinuteOfTheDay, 
              minuteOfTheDayToTurnOn, 
              minuteOfTheDayToTurnOff,
              relays[routine.relayIndex-1].manuallyTurnedOn,
              relays[routine.relayIndex-1].manuallyTurnedOff
            );
          }
        }


      }

      for(int i = 0; i< NUMBER_OF_RELAYS; i++){
        if(portsStatus[i] && !relays[i].isOn){ relays[i].turnOn(); }
        else if(!portsStatus[i] && relays[i].isOn) { relays[i].turnOff(); }
      }
    } else {
      for(RelayController relay: relays){
        bool relayMustBeTurnedOn = RoutinesController::shouldItbeTurnedOn(
          currentMinuteOfTheDay, 
          currentMinuteOfTheDay+2,
          currentMinuteOfTheDay+4,
          relay.manuallyTurnedOn,
          relay.manuallyTurnedOff
        );
        if(relayMustBeTurnedOn && !relay.isOn){ relay.turnOn(); } 
        else { relay.turnOff(); }
      }
    }
  }

  if (xSemaphoreTake(toggleRelayInterruptionSemaphore, 0) == pdTRUE) {
    for(int i =0; i<NUMBER_OF_RELAYS; i++){
      int status = digitalRead(relays[i].buttonPort);
      if(status == 1){ relays[i].manuallyToggleRelayState(); } 
    }
  }
  if(changeWifiButtonStatus && !resetWifi && millis() - lastChangeWifiClick > 5000){
    
    WifiManager::initWifiResetProcess();
    resetWifi = true;
  }
  if (xSemaphoreTake(changeWifiModeInterruptionSemaphore, 0) == pdTRUE) {
    if(resetWifi){
      WifiManager::resetWifi();
      resetWifi = false;
    }
    changeWifiButtonStatus = digitalRead(WifiManager::changeWifiModeButtonPort);
    lastChangeWifiClick = millis();
  }
  httpServer.handleClient();
  webSocket.socket.loop();
}