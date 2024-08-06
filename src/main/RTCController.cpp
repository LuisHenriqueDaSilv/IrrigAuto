#include "RTCController.h"
#include <RTClib.h>
#include <array>
#include "utils.h"

RTC_DS3231 RTCController::rtc;

std::array<int, 3> RTCController::getNow(){
	DateTime now = rtc.now();
  int hora = now.hour();
  int minuto = now.minute();
  int segundo = now.second();
	return {hora, minuto, segundo};
}

void RTCController::configureClock(int hour, int minute){
  rtc.adjust(DateTime(2021, 1, 21, hour, minute, 0));
}