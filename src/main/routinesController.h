#include "Wire.h"
#include "relayController.h"

#ifndef ROUTINES_CONTROLLER_H
#define ROUTINES_CONTROLLER_H
  extern RelayController relays[4];
  class RoutinesController {
    public: 
      static void create(
        int hourToTurnOn,
        int minuteToTurnOn,
        int hourToTurnOff,
        int minuteToTurnOff,
        int relayIndex
      );
      static void delete_(String routineToDelete);
      static void deleteAll();
      static void readAll();
  };
#endif