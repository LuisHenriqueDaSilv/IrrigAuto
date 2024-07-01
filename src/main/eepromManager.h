#include <Wire.h>

#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

  constexpr int EEPROM_SIZE = 512;
  constexpr int ROUTINE_LENGTH = 8;

  void saveRoutineInEEPROM(
    int hourToTurnON,
    int minuteToTurnOn,
    int hourToTurnOff,
    int minuteToTurnOFF
  );

  void saveRoutinesString(String routines);

  void clearEEPROM();

  String getRoutinesInEEPROM();

#endif