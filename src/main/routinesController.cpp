#include "routinesController.h"

bool RoutinesController::createRoutine(
  RoutineStruct routine,
  int routineIndex
){
  int firstEmptyAddressInEEPROM = routineIndex*(ROUTINE_LENGTH/2);
  if(firstEmptyAddressInEEPROM+(ROUTINE_LENGTH/2) >= EEPROM_SIZE) { 
    return false; // Limit reached
  } 
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.write(firstEmptyAddressInEEPROM, routine.hourToTurnOn);
  EEPROM.write(firstEmptyAddressInEEPROM+1, routine.minuteToTurnOn);
  EEPROM.write(firstEmptyAddressInEEPROM+2, routine.hourToTurnOff);
  EEPROM.write(firstEmptyAddressInEEPROM+3, routine.minuteToTurnOff);
  EEPROM.write(firstEmptyAddressInEEPROM+4, routine.relayIndex);
  EEPROM.commit();
  EEPROM.end();
  return true; // Sucess
}

void RoutinesController::saveRoutines(std::list<RoutineStruct> routines){
  Serial.print("Salvando");
  Serial.print(routines.size());
  int i = 0;
  for(RoutineStruct routine: routines){
    bool creationSucess = createRoutine(routine, i);
    if(!creationSucess){break;}
    i++;
  }
}

void RoutinesController::deleteAll(){
  clearEEPROM();
  for(RelayController relay: relays){
    relay.turnOff();
  }
}

bool RoutinesController::delete_(RoutineStruct routineToDelete){
  std::list<RoutineStruct> routines = getRoutines();
  for(RoutineStruct routine: routines){
    if( routine == routineToDelete ){
      Serial.println("Encontrei");
      routines.remove(routineToDelete);
      deleteAll();
      saveRoutines(routines);
      return true; // Sucess
    }  
  };
  return false; // Routine not found
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


std::list<RoutineStruct> RoutinesController::getRoutines(){
  std::list<RoutineStruct> listOfRoutines;
  bool endOfEEPROM = false;
  int EEPROMAddressCounter = 0;

  EEPROM.begin(EEPROM_SIZE);
  while ( !endOfEEPROM && EEPROMAddressCounter < EEPROM_SIZE ){
    int hourToTurnON    = EEPROM.read(EEPROMAddressCounter );
    int minuteToTurnOn  = EEPROM.read(EEPROMAddressCounter+1);
    int hourToTurnOff   = EEPROM.read(EEPROMAddressCounter+2);
    int minuteToTurnOFF = EEPROM.read(EEPROMAddressCounter+3);
    int relayIndex      = EEPROM.read(EEPROMAddressCounter+4);

    if( hourToTurnON == 0 && minuteToTurnOn == 0 && hourToTurnOff == 0 && minuteToTurnOFF == 0 ) {
      endOfEEPROM = true;
      continue;
    }
    RoutineStruct newRoutine = {
      hourToTurnON,
      minuteToTurnOn,
      hourToTurnOff,
      minuteToTurnOFF,
      relayIndex
    };
    listOfRoutines.push_back(newRoutine);
    EEPROMAddressCounter += ROUTINE_LENGTH/2;
  }
  EEPROM.end();

  return listOfRoutines;
}

bool RoutinesController::routineExist(RoutineStruct routineToSearch){
  std::list<RoutineStruct> routines = getRoutines();
  for(RoutineStruct routine: routines ){
    if(routineToSearch == routine){
      return true;
    }
  }
  return false;
}

