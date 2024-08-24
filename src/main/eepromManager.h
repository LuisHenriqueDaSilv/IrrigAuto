
#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H
  #include <Wire.h>
  #include <EEPROM.h>
  #include "utils.h"

  constexpr int EEPROM_SIZE = 512;
  constexpr int ROUTINE_LENGTH = 10;

  void addRoutineInEEPROM(
    int hourToTurnON,
    int minuteToTurnOn,
    int hourToTurnOff,
    int minuteToTurnOFF,
    int relayIndex
  );

  void writeValuesInEEPROM(String routines, int numberOfRoutines);
  void clearEEPROM();

  String getRoutinesInEEPROM();

#endif