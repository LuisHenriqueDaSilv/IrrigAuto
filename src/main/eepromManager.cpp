#include "eepromManager.h"

#include <EEPROM.h>

#include "utils.h"

void saveRoutineInEEPROM(
  int hourToTurnON,
  int minuteToTurnOn,
  int hourToTurnOff,
  int minuteToTurnOFF
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
  EEPROM.end();    
}

void saveRoutinesString(String routines){
  int routinesLenght = routines.length();
  int numberOfRoutines = getNumberOfRoutines(routines);
  for(int i = 0; i < numberOfRoutines; i = i + 1){ 
    int hourToTurnOn = atoi(routines.substring(i*8, i*8+2).c_str());
    int minuteToTurnOn = atoi(routines.substring(i*8+2, i*8+4).c_str());
    int hourToTurnOff = atoi(routines.substring(i*8+4, i*8+6).c_str());
    int minuteToTurnOff = atoi(routines.substring(i*8+6, i*8+8).c_str());
    saveRoutineInEEPROM(hourToTurnOn, minuteToTurnOn, hourToTurnOff, minuteToTurnOff);
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