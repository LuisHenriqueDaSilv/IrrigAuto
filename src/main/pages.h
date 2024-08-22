#include "relayController.h"

#ifndef PAGES_H
#define PAGES_H
  #include <Wire.h>
  extern RelayController relays[NUMBER_OF_RELAYS];
  class Pages {
    public:
      static String landingPage();
      static String clockAdjustPage();
      static String createRoutinePage();
      static String configureNetwork();
  };
#endif