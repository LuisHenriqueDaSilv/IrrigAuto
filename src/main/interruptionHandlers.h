#include <Wire.h> 

#ifndef INTERRUPTION_HANDLERS_H
#define INTERRUPTION_HANDLERS_H

  const int DEBOUNCE_TIME = 300;

  extern SemaphoreHandle_t fisicallyToggleRelaySemaphore;
  extern SemaphoreHandle_t changeWifiModeSemaphore;
  void IRAM_ATTR handleManualButtonChange();
  void IRAM_ATTR handleChangeWifiModeButton();
  extern volatile unsigned long lastClickTime;
#endif