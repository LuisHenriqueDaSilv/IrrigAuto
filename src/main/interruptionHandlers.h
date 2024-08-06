#include <Wire.h> 

#ifndef INTERRUPTION_HANDLERS_H
#define INTERRUPTION_HANDLERS_H

  const int DEBOUNCE_TIME = 300;

  extern SemaphoreHandle_t buttonSemaphoreChange;
  void IRAM_ATTR handleManualButtonChange();
  extern volatile unsigned long lastClickTime;
#endif