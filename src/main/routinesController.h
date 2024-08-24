#include "relayController.h"
#include "Wire.h"
#include "relayController.h"
#include "eepromManager.h"
#include "utils.h"

#ifndef ROUTINES_CONTROLLER_H
#define ROUTINES_CONTROLLER_H
  struct RoutineStruct {
      int hourToTurnOn;
      int minuteToTurnOn;
      int hourToTurnOff;
      int minuteToTurnOff;
      int relayIndex;
  };
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
      static int calcNumberOfRoutines(String routines);
      static bool shouldItbeTurnedOn(
        int currentMinuteOfTheDay,
        int minuteOfTheDayToTurnOn,
        int minuteOfTheDayToTurnOff,
        bool manuallyTurnedOn,
        bool manuallyTurnedOff
      );
      static RoutineStruct convertStringToRoutine(String routine);
  };
#endif