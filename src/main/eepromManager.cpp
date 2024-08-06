#include "eepromManager.h"

#include <EEPROM.h>

#include "utils.h"

void saveRoutineInEEPROM(
  int hourToTurnON,
  int minuteToTurnOn,
  int hourToTurnOff,
  int minuteToTurnOFF,
  int relayIndex
){
  String routines = getRoutinesInEEPROM();
  // A string contendo todas as rotinas é dividida em rotinas de tamanho "ROUTINE_LENGTH".
  // Cada rotina é organizada em blocos de hora e minuto, tendo dois caracteres cada bloco.
  // Sendo assim, todas as rotinas têm valor par.
  // Cada bloco da rotina é dado por um valor entre 0 e 60, sendo salvo em um endereço da EEPROM
  // Tornando viavel o seguinte cálculo:
  int firstEmptyAddresInEEPROM = routines.length()/2;
  if(firstEmptyAddresInEEPROM+4 >= EEPROM_SIZE ){
    return;
  }
  EEPROM.begin(EEPROM_SIZE);
  //           addrs                       value
  EEPROM.write(firstEmptyAddresInEEPROM,   hourToTurnON);
  EEPROM.write(firstEmptyAddresInEEPROM+1, minuteToTurnOn);
  EEPROM.write(firstEmptyAddresInEEPROM+2, hourToTurnOff);
  EEPROM.write(firstEmptyAddresInEEPROM+3, minuteToTurnOFF);
  EEPROM.write(firstEmptyAddresInEEPROM+4, relayIndex);
  EEPROM.end();    
}

void saveRoutinesString(String routines){
  int routinesLenght = routines.length();
  int numberOfRoutines = getNumberOfRoutines(routines);
  for(int i = 0; i < numberOfRoutines; i = i + 1){ 
    int hourToTurnOn = atoi(routines.substring(i*ROUTINE_LENGTH, i*ROUTINE_LENGTH+2).c_str());
    int minuteToTurnOn = atoi(routines.substring(i*ROUTINE_LENGTH+2, i*ROUTINE_LENGTH+4).c_str());
    int hourToTurnOff = atoi(routines.substring(i*ROUTINE_LENGTH+4, i*ROUTINE_LENGTH+6).c_str());
    int minuteToTurnOff = atoi(routines.substring(i*ROUTINE_LENGTH+6, i*ROUTINE_LENGTH+8).c_str());
    int relayIndex = atoi(routines.substring(i*ROUTINE_LENGTH+8, i*ROUTINE_LENGTH+10).c_str());
    saveRoutineInEEPROM(hourToTurnOn, minuteToTurnOn, hourToTurnOff, minuteToTurnOff, relayIndex);
  }
}

void clearEEPROM(){
  EEPROM.begin(512);  

  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  EEPROM.end();
}


String getRoutinesInEEPROM(){
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