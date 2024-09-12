#include <EEPROM.h>
#include <list>
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
    int days;
    bool operator==(const RoutineStruct& other) const {
      return (
        hourToTurnOn == other.hourToTurnOn && 
        minuteToTurnOn == other.minuteToTurnOn && 
        hourToTurnOff == other.hourToTurnOff && 
        minuteToTurnOff == other.minuteToTurnOff && 
        relayIndex == other.relayIndex&& 
        days == other.days
      );
    }
  };
  extern RelayController relays[4];
  class RoutinesController {
    public: 
      static bool createRoutine(
        RoutineStruct routine,
        int routineIndex
      );
      static bool delete_(RoutineStruct routineToDelete);
      static void deleteAll();
      static bool shouldItbeTurnedOn(
        int currentMinuteOfTheDay,
        int minuteOfTheDayToTurnOn,
        int minuteOfTheDayToTurnOff,
        bool manuallyTurnedOn,
        bool manuallyTurnedOff
      );
      static std::list<RoutineStruct> getRoutines();
      static void saveRoutines(std::list<RoutineStruct> routines);
      static bool routineExist(RoutineStruct routine);
  };
#endif