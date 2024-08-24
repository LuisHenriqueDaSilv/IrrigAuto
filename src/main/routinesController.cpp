#include "routinesController.h"

void RoutinesController::create(
  int hourToTurnOn, 
  int minuteToTurnOn, 
  int hourToTurnOff, 
  int minuteToTurnOff, 
  int relayIndex
){
  addRoutineInEEPROM(
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
  int numberOfRoutines = calcNumberOfRoutines(routines); 
  writeValuesInEEPROM(routines, numberOfRoutines);
}

bool RoutinesController::shouldItbeTurnedOn(
  int currentMinuteOfTheDay, 
  int minuteOfTheDayToTurnOn, 
  int minuteOfTheDayToTurnOff,
  bool manuallyTurnedOn,
  bool manuallyTurnedOff
){
  if(currentMinuteOfTheDay == minuteOfTheDayToTurnOff || currentMinuteOfTheDay == minuteOfTheDayToTurnOn){
    manuallyTurnedOn = false;
    manuallyTurnedOff = false;
  }

  if(manuallyTurnedOn){ return true; }
  if(manuallyTurnedOff){ return false; }
  if(minuteOfTheDayToTurnOff > minuteOfTheDayToTurnOn){
    return (currentMinuteOfTheDay >= minuteOfTheDayToTurnOn && currentMinuteOfTheDay < minuteOfTheDayToTurnOff);
  }
  if(minuteOfTheDayToTurnOff < minuteOfTheDayToTurnOn) {
    int howLongTheDeviceWillStayOn = (minuteOfTheDayToTurnOff + 1440) - minuteOfTheDayToTurnOn;
    int minutesOnFirstDay = 1440 - minuteOfTheDayToTurnOn; // 1440 é a quantidade de minutos em 24 horas
    int minutesOnSecondDay =  howLongTheDeviceWillStayOn - minutesOnFirstDay;
    return (currentMinuteOfTheDay >= minuteOfTheDayToTurnOn || currentMinuteOfTheDay < minutesOnSecondDay);
  }

  return false;

}

int RoutinesController::calcNumberOfRoutines(String routines){
  return(routines.length() / ROUTINE_LENGTH);
}

RoutineStruct RoutinesController::convertStringToRoutine(String routine){
  int hourToTurnOn = atoi(routine.substring(ROUTINE_LENGTH, ROUTINE_LENGTH+2).c_str());
  int minuteToTurnOn = atoi(routine.substring(ROUTINE_LENGTH+2, ROUTINE_LENGTH+4).c_str());
  int hourToTurnOff = atoi(routine.substring(ROUTINE_LENGTH+4, ROUTINE_LENGTH+6).c_str());
  int minuteToTurnOff = atoi(routine.substring(ROUTINE_LENGTH+6, ROUTINE_LENGTH+8).c_str());
  int relayIndex = atoi(routine.substring(ROUTINE_LENGTH+8, ROUTINE_LENGTH+10).c_str());
  return { hourToTurnOn, minuteToTurnOn, hourToTurnOff, minuteToTurnOff, relayIndex };
}
