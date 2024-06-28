
#ifndef UTILS_H
#define UTILS_H
  #include <Wire.h>
  String numberToTwoChars(int number);
  int getNumberOfRoutines(String routines);
  bool checkIfItShouldbeTurnedOn(
    int currentMinuteOfTheDay,
    int minuteOfTheDayToTurnOn,
    int minuteOfTheDayToTurnOff,
    bool manuallyTurnedOn,
    bool manuallyTurnedOff
  );
#endif