#include "routinesController.h"

#include "relayController.h"
#include "eepromManager.h"

void RoutinesController::create(){
  String horaLiga1 = server.arg(0);
  String minutoLiga1 = server.arg(1);
  String horaDesliga1 = server.arg(2);
  String minutoDesliga1 = server.arg(3);

  int horaLigaInt = atoi(horaLiga1.c_str());
  int minutoLigaInt = atoi(minutoLiga1.c_str()); 
  int horaDesligaInt = atoi(horaDesliga1.c_str()); 
  int minutoDesligaInt = atoi(minutoDesliga1.c_str()); 
  
  saveRoutineInEEPROM(
    horaLigaInt,
    minutoLigaInt,
    horaDesligaInt,
    minutoDesligaInt
  );

  server.sendHeader("Location", "/", true); 
  server.send(302, "text/plain", "");
}

void RoutinesController::deleteAll(){
  clearEEPROM();
  getRoutinesInEEPROM();

  relay.turnOff();

  server.sendHeader("Location", "/",true);
  server.send(302, "text/plain", "");
}

void RoutinesController::delete_(){
  String routineToDelete = server.arg(0);

  String routines = getRoutinesInEEPROM();
  int indexOfRoutineToDelete = routines.indexOf(routineToDelete);
  routines.remove(indexOfRoutineToDelete, 8);
  clearEEPROM();
  saveRoutinesString(routines);

  server.sendHeader("Location", "/",true); 
  server.send(302, "text/plain", "");
}