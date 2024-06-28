#include "eepromManager.h"

#include <EEPROM.h>
#include <Wire.h>

#include "utils.h"

String getRoutinesInEEPROM(){
  String routines = "";
  bool endOfEEPROM = false;
  int EEPROMAddressCounter = 0;

  EEPROM.begin(EEPROM_SIZE);
  while ( !endOfEEPROM ){
    int hourToTurnON    = EEPROM.read(EEPROMAddressCounter );
    int minuteToTurnOn  = EEPROM.read(EEPROMAddressCounter+1);
    int hourToTurnOff   = EEPROM.read(EEPROMAddressCounter+2);
    int minuteToTurnOFF = EEPROM.read(EEPROMAddressCounter+3);

    if( hourToTurnON == 0 && minuteToTurnOn == 0 && hourToTurnOff == 0 && minuteToTurnOFF == 0 ) {
      endOfEEPROM = true;
      continue;
    }
    routines += (
      numberToTwoChars(hourToTurnON)+
      numberToTwoChars(minuteToTurnOn) + 
      numberToTwoChars(hourToTurnOff) +
      numberToTwoChars(minuteToTurnOFF)
    );
    EEPROMAddressCounter += 4;
  }
  EEPROM.end();
  return routines;
}