#include <Wire.h> 
#include <Arduino.h>

#ifndef INTERRUPTION_HANDLERS_H
#define INTERRUPTION_HANDLERS_H
  const int DEBOUNCE_TIME = 10;

  extern volatile unsigned long fisicalButtonsLastClickTime;
  extern SemaphoreHandle_t toggleRelayInterruptionSemaphore;
  extern SemaphoreHandle_t changeWifiModeInterruptionSemaphore;

  void IRAM_ATTR handleToggleRelayInterruption();
  void IRAM_ATTR handleChangeWifiModeInterruption();
#endif