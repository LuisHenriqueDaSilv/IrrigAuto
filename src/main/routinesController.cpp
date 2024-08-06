#include "routinesController.h"

#include "relayController.h"
#include "eepromManager.h"
#include "utils.h"

void RoutinesController::create(
  int hourToTurnOn, 
  int minuteToTurnOn, 
  int hourToTurnOff, 
  int minuteToTurnOff, 
  int relayIndex
){
  saveRoutineInEEPROM(
    hourToTurnOn,
    minuteToTurnOn,
    hourToTurnOff,
    minuteToTurnOff,
    relayIndex
  );
}

void RoutinesController::deleteAll(){
  clearEEPROM();
  for(RelayController relay: relays){
    relay.turnOff();
  }
}

void RoutinesController::delete_(String routineToDelete){
  String routines = getRoutinesInEEPROM();
  int indexOfRoutineToDelete = routines.indexOf(routineToDelete);
  routines.remove(indexOfRoutineToDelete, ROUTINE_LENGTH);
  clearEEPROM();
  saveRoutinesString(routines);

}