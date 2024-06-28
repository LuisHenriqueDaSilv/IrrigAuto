#include "relayController.h"

#ifndef PAGES_H
#define PAGES_H
  #include <Wire.h>
  extern RelayController relay;
  class Pages {
    public:
      static String landingPage();
      static String clockAdjustPage();
      static String createRoutinePage();
  };
#endif