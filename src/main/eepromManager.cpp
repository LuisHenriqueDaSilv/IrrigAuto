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
  EEPROM.begin(EEPROM_SIZE);
  for(int i = 0; i < routinesLenght/2; i+=2){
    //                                    [i, i+2[
    int routineBlock = atoi(routines.substring(i,i+2).c_str());
    EEPROM.write(i, routineBlock);
  }
  EEPROM.end(); 
}

void clearEEPROM(){
    EEPROM.begin(512);  

  Serial.println("Limpando EEPROM!");
  for (int i = 0; i <= EEPROM_SIZE; i++) {
    EEPROM.write(i, 0);
  }
  Serial.println("EEPROM apagada!");
  EEPROM.write(FIRST_EEPROM_ADDRESS, (byte) 0);
  EEPROM.commit();
  EEPROM.end();
}