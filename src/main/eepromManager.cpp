#include "eepromManager.h"

void addRoutineInEEPROM(
  int hourToTurnON,
  int minuteToTurnOn,
  int hourToTurnOff,
  int minuteToTurnOFF,
  int relayIndex,
  int routineDays
){
  String routines = readRoutinesInEEPROM();
  int firstEmptyAddresInEEPROM = routines.length()/2;
  if(firstEmptyAddresInEEPROM+NUMBER_OF_ROUTINE_PARTS >= EEPROM_SIZE ){ return; }
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.write(firstEmptyAddresInEEPROM,   hourToTurnON);
  EEPROM.write(firstEmptyAddresInEEPROM+1, minuteToTurnOn);
  EEPROM.write(firstEmptyAddresInEEPROM+2, hourToTurnOff);
  EEPROM.write(firstEmptyAddresInEEPROM+3, minuteToTurnOFF);
  EEPROM.write(firstEmptyAddresInEEPROM+4, relayIndex);
  EEPROM.write(firstEmptyAddresInEEPROM+5, routineDays);
  EEPROM.commit();
  EEPROM.end();    
}

void writeValuesInEEPROM(String routines, int numberOfRoutines){
  int routinesLenght = routines.length();
  EEPROM.begin(EEPROM_SIZE);
  int addresCounter = 0;
  for(int i = 0; i < routinesLenght; i+=2){
    int value = atoi(routines.substring(i, i+2).c_str());
    EEPROM.write(addresCounter, value);
    addresCounter++;
  }
  EEPROM.commit();
  EEPROM.end();
}

void clearEEPROM(){
  EEPROM.begin(512);
  for (int i = 0; i < EEPROM_SIZE; i++) { EEPROM.write(i, 0); }
  EEPROM.commit();
  EEPROM.end();
}

String readRoutinesInEEPROM(){
  String routines = "";
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
    routines += (
      numberToTwoChars(hourToTurnON)+
      numberToTwoChars(minuteToTurnOn) + 
      numberToTwoChars(hourToTurnOff) +
      numberToTwoChars(minuteToTurnOFF) +
      numberToTwoChars(relayIndex)
    );
    EEPROMAddressCounter += ROUTINE_LENGTH/2;
  }
  EEPROM.end();
  return routines;
}
