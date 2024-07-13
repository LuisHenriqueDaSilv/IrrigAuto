#include "relayController.h"
#include "Arduino.h"
#include "webSocket.h"

void RelayController::turnOff(){
  isOn = false;
  digitalWrite(port, LOW);
  socketEmitRelayStatus();
}

void RelayController::turnOn(){
  isOn = true;
  digitalWrite(port, HIGH);
  socketEmitRelayStatus();
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
}