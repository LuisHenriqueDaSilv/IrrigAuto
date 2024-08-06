#include <RTClib.h>
#include <WebServer.h>

#ifndef RTC_CONTROLLER_H
#define RTC_CONTROLLER_H
  class RTCController {
    public: 
      static RTC_DS3231 rtc;
      static std::array<int, 3> getNow();
      static void configureClock(int hour, int minute);
  };
#endif