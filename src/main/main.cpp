#include <EEPROM.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <RTClib.h>
#include <array>

#include "utils.h"
#include "eepromManager.h"
#include "pages.h"
#include "RTCController.h"
#include "routinesController.h"
#include "relayController.h"
#include "webSocket.h"
#include "interruptionHandlers.h"
#include "httpServer.h"

RelayController relays[NUMBER_OF_RELAYS];
WebSocket webSocket;
HTTPServer httpServer;
volatile unsigned long lastClickTime = 0;
SemaphoreHandle_t buttonSemaphoreChange;

const char* ssid     = "sistema_de_irrigacao";
const char* password = "123456789";
void initWiFi(){
  IPAddress local_ip(192,168,1,1);
  IPAddress gateway(192,168,1,1);
  IPAddress subnet(255,255,255,0);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
}

void setup() {
  Serial.begin(115200);
  initWiFi();

  buttonSemaphoreChange = xSemaphoreCreateBinary();
  if (buttonSemaphoreChange == NULL) {
    Serial.println("Failed to create semaphore");
    while (1);
  }

  relays[0] = RelayController(14,34, 1);
  relays[1] = RelayController(27,35, 2);
  relays[2] = RelayController(26,32, 3);
  relays[3] = RelayController(25,33, 4);

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

  Serial.println(WiFi.localIP());
  Serial.println();

}

int lastMinuteInLoop = -1;
void loop(){

  std::array<int,3> now = RTCController::getNow();
  if(lastMinuteInLoop != now[1]){

    std::array<int, 3> now = RTCController::getNow();
    String hours = numberToTwoChars(now[0]);
    String minutes = numberToTwoChars(now[1]);
    String buf = "{ \"hora\" : \""+ hours + "\", \"minuto\" : \""+ minutes +"\" }";
    webSocket.emitEvent("{\"event\": \"clockUpdate\", \"buffer\":"+buf+"}");

    lastMinuteInLoop = now[1];
    int currentMinuteOfTheDay = (now[0]*60) + now[1];
    bool deviceMustBeTurnedOn = false;

    String routines = getRoutinesInEEPROM();
    int numberOfRoutines = getNumberOfRoutines(routines);
    bool portsStatus[NUMBER_OF_RELAYS] = {0};

    if(numberOfRoutines > 0){
 
      for(int i = 0; i < numberOfRoutines; i = i + 1){
        int hourToTurnOn = atoi(routines.substring(i*ROUTINE_LENGTH, i*ROUTINE_LENGTH+2).c_str());
        int minuteToTurnOn = atoi(routines.substring(i*ROUTINE_LENGTH+2, i*ROUTINE_LENGTH+4).c_str());
        int hourToTurnOff = atoi(routines.substring(i*ROUTINE_LENGTH+4, i*ROUTINE_LENGTH+6).c_str());
        int minuteToTurnOff = atoi(routines.substring(i*ROUTINE_LENGTH+6, i*ROUTINE_LENGTH+8).c_str());
        int relayIndex = atoi(routines.substring(i*ROUTINE_LENGTH+8, i*ROUTINE_LENGTH+10).c_str());

        int minuteOfTheDayToTurnOn = (hourToTurnOn*60) + minuteToTurnOn;
        int minuteOfTheDayToTurnOff = (hourToTurnOff*60) + minuteToTurnOff;

        if(!portsStatus[relayIndex-1]){
            portsStatus[relayIndex-1] = checkIfItShouldbeTurnedOn(
              currentMinuteOfTheDay, 
              minuteOfTheDayToTurnOn, 
              minuteOfTheDayToTurnOff,
              relays[relayIndex-1].manuallyTurnedOn,
              relays[relayIndex-1].manuallyTurnedOff
            );
        }
      }

      for(int i = 0; i< NUMBER_OF_RELAYS; i++){
        if(portsStatus[i] && !relays[i].isOn){ relays[i].turnOn(); } 
        else if(!portsStatus[i] && relays[i].isOn) { relays[i].turnOff(); }
      }
    } else {
      for(RelayController relay: relays){
        bool relayMustBeTurnedOn = checkIfItShouldbeTurnedOn(
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
  

  if (xSemaphoreTake(buttonSemaphoreChange, 0) == pdTRUE) {
    for(int i =0; i<NUMBER_OF_RELAYS; i++){
      int status = digitalRead(relays[i].buttonPort);
      if(status == 1){
        relays[i].manuallyToggleRelayState();
      } 
    }
  }
  httpServer.handleClient();
  webSocket.socket.loop();
}