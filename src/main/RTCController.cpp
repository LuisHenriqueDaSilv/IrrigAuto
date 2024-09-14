#include "RTCController.h"
#include <RTClib.h>
#include <array>
#include "utils.h"

RTC_DS3231 RTCController::rtc;
String RTCController::weekDays[7] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};
NowStruct RTCController::getNow(){
	DateTime now = rtc.now();
  int hora = now.hour();
  int minuto = now.minute();
  int segundo = now.second();
  int day = now.dayOfTheWeek(); 
	return {hora, minuto, segundo, day};
}

void RTCController::configureClock(int hour, int minute, int day){
  // 08/09/2024 é um domingo. 
  // Sendo day o dia da semana, começando por domingo = 0
  // Somar day ao dia 8 resulta no dia da semana correto.
  rtc.adjust(DateTime(2024, 9, 8+day, hour, minute, 0)); 
}