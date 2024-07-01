#include <EEPROM.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <array>

#include "utils.h"
#include "eepromManager.h"
#include "pages.h"
#include "RTCController.h"
#include "routinesController.h"
#include "relayController.h"

const char* ssid     = "sistema_de_irrigacao";
const char* password = "123456789";

WebServer server(80);
RelayController relay;

void initWiFi() {
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  // Serial.print("Connecting to WiFi ..");
  // while (WiFi.status() != WL_CONNECTED){
  // Serial.print('.');
  // delay(1000);
  // }
  // Serial.println(WiFi.localIP());

  IPAddress local_ip(192,168,1,1);
  IPAddress gateway(192,168,1,1);
  IPAddress subnet(255,255,255,0);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

}
void setup() {
  Serial.begin(115200);
	pinMode(relay.port, OUTPUT);
  initWiFi();

	server.on("/", [](){server.send(200, "text/html", Pages::landingPage());});
	server.on("/configurar-relogio", [](){server.send(200, "text/html", Pages::clockAdjustPage());});
	server.on("/configurar-rotina", [](){server.send(200, "text/html", Pages::createRoutinePage());});
	server.on("/excluir-rotina", RoutinesController::delete_);
	server.on("/apagar-rotinas", RoutinesController::deleteAll);
	server.on("/adicionar-rotina", RoutinesController::create);
	server.on("/rotinas", RoutinesController::readAll);
	server.on("/setar-relogio", RTCController::configureClock);
	server.on("/relogio", RTCController::readNow);
  server.on("/mudar-rele", [](){relay.manuallyTurn();});
	server.on("/status", [](){relay.getStatus();});

  server.begin();
  Serial.println("HTTP server beginned");

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

void loop(){

  std::array<int,3> now = RTCController::getNow();
  int currentMinuteOfTheDay = (now[0]*60) + now[1];
  bool deviceMustBeTurnedOn = false;

  String routines = getRoutinesInEEPROM();
  int numberOfRoutines = getNumberOfRoutines(routines);
  if(numberOfRoutines > 0){

    for(int i = 0; i < numberOfRoutines; i = i + 1){
      int hourToTurnOn = atoi(routines.substring(i*8, i*8+2).c_str());
      int minuteToTurnOn = atoi(routines.substring(i*8+2, i*8+4).c_str());
      int hourToTurnOff = atoi(routines.substring(i*8+4, i*8+6).c_str());
      int minuteToTurnOff = atoi(routines.substring(i*8+6, i*8+8).c_str());

      int minuteOfTheDayToTurnOn = (hourToTurnOn*60) + minuteToTurnOn;
      int minuteOfTheDayToTurnOff = (hourToTurnOff*60) + minuteToTurnOff;

      if(!deviceMustBeTurnedOn){
        deviceMustBeTurnedOn = checkIfItShouldbeTurnedOn(
          currentMinuteOfTheDay, 
          minuteOfTheDayToTurnOn, 
          minuteOfTheDayToTurnOff,
          relay.manuallyTurnedOn,
          relay.manuallyTurnedOff
        );
      }
    }
  } else {
    deviceMustBeTurnedOn = checkIfItShouldbeTurnedOn(
      currentMinuteOfTheDay, 
      currentMinuteOfTheDay+2, 
      currentMinuteOfTheDay+4,
      relay.manuallyTurnedOn,
      relay.manuallyTurnedOff
    );
  }

  if((deviceMustBeTurnedOn && !relay.isOn)){
    relay.turnOn();
  } else if((!deviceMustBeTurnedOn && relay.isOn)) {
    relay.turnOff();
  }
	
	server.handleClient();
}
