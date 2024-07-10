#include "relayController.h"
#include "Arduino.h"

void RelayController::turnOff(){
  isOn = false;
  digitalWrite(port, LOW);
}

void RelayController::turnOn(){
  isOn = true;
  digitalWrite(port, HIGH);
}

void RelayController::getStatus(){
  String buf = "{ \"status\" : \""+ String(isOn) +  "\" }";
  server.send(200, "text/json", buf); 
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

void RelayController::manuallyToggleRelayState(){
  if(isOn){ clientTurnOff(); } else {clientTurnOn();}
  server.send(200, "text/json", "");
}

void RelayController::physicallyToggleRelayState(){
  if(isOn){ clientTurnOff(); } else {clientTurnOn();}
}