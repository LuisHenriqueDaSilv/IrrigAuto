#include <Arduino.h>
#include "relayController.h"
#include "utils.h"

RelayController::RelayController(){};
RelayController::RelayController(int port_, int buttonPort_, int id_){
  port = port_;
  buttonPort = buttonPort_;
  id = id_;
  isOn = false;
	pinMode(port_, OUTPUT);
  pinMode(buttonPort_, INPUT_PULLUP);
  digitalWrite(port_, LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPort), handleToggleRelayInterruption, RISING );
}

void RelayController::emitStatus(int id, bool status){
  String buffer = "{\"id\": \""+numberToTwoChars(id)+"\", \"isOn\":\""+String(status)+"\"}";
  webSocket.emitEvent("{\"event\": \"relayChange\", \"buffer\": "+buffer+"}");
}

void RelayController::turnOff(){
  isOn = false;
  digitalWrite(port, LOW);
  emitStatus(id, isOn);
}

void RelayController::turnOn(){
  isOn = true;
  digitalWrite(port, HIGH);
  emitStatus(id, isOn);
}

void RelayController::clientTurnOn(){
  turnOn();
  manuallyTurnedOn = true;
  manuallyTurnedOff = false;
}

void RelayController::clientTurnOff(){
  turnOff();
  manuallyTurnedOn = false;
  manuallyTurnedOff = true;
}

void RelayController::toggleRelayById(int id){
  relays[id-1].manuallyToggleRelayState();
}

void RelayController::manuallyToggleRelayState(){
  if(isOn){ clientTurnOff(); } else {clientTurnOn();}
}