#include <RTClib.h>
#include <WebServer.h>

#ifndef RTC_CONTROLLER_H
#define RTC_CONTROLLER_H
  struct NowStruct {
    int hour;
    int minute;
    int second;
    int day;
  };
  class RTCController {
    public: 
      static RTC_DS3231 rtc;
      static NowStruct getNow();
      static void configureClock(int hour, int minute, int day);
  };
#endif