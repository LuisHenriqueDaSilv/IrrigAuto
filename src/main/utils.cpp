#include "utils.h"
#include "eepromManager.h"

bool checkIfItShouldbeTurnedOn(
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
    if(currentMinuteOfTheDay >= minuteOfTheDayToTurnOn && currentMinuteOfTheDay < minuteOfTheDayToTurnOff){
      return true;
    }else { return false; }
  }else if(minuteOfTheDayToTurnOff < minuteOfTheDayToTurnOn) {
    int tempoQueODispositivoVaiFicarLigado = (minuteOfTheDayToTurnOff + 1440) - minuteOfTheDayToTurnOn;
    int minutosLigadoNoPrimeiroDia = 1440 - minuteOfTheDayToTurnOn; // 1440 é a quantidade de minutos em 24 horas
    int minutosLigadoNoSegundoDia =  tempoQueODispositivoVaiFicarLigado - minutosLigadoNoPrimeiroDia;
    if(currentMinuteOfTheDay >= minuteOfTheDayToTurnOn || currentMinuteOfTheDay < minutosLigadoNoSegundoDia){
      return true;
    } else { return false; }
  } else { return false; }
}

int getNumberOfRoutines(String routines){
  return(routines.length() / ROUTINE_LENGTH);
}

String numberToTwoChars(int number){
  if(number<10){
    return "0"+String(number);
  } else {
    return String(number);
  }
}