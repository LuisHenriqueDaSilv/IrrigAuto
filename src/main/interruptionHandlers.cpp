#include "interruptionHandlers.h"
#include <Arduino.h>

void IRAM_ATTR handleManualButtonChange() {
  unsigned long currentTime = millis();
  if (currentTime - lastClickTime > DEBOUNCE_TIME) {
    lastClickTime = currentTime;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(buttonSemaphoreChange, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
      portYIELD_FROM_ISR();
    }
  }
}