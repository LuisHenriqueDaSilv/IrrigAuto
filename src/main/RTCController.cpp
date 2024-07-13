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

void RTCController::configureClock(){
  String clientHours = server.arg(0);
  String clientMinutes = server.arg(1);

  rtc.adjust(DateTime(2021, 1, 21, atoi(clientHours.c_str()), atoi(clientMinutes.c_str()), 0));

  server.sendHeader("Location", "/",true); 
  server.send(302, "text/plain", "");
}