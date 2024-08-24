#include "interruptionHandlers.h"

void IRAM_ATTR handleToggleRelayInterruption() {
  unsigned long currentTime = millis();
  if (currentTime - fisicalButtonsLastClickTime > DEBOUNCE_TIME) {
    fisicalButtonsLastClickTime = currentTime;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(toggleRelayInterruptionSemaphore, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
      portYIELD_FROM_ISR();
    }
  }
}

void IRAM_ATTR handleChangeWifiModeInterruption() {
  unsigned long currentTime = millis();
  if (currentTime - fisicalButtonsLastClickTime > DEBOUNCE_TIME) {
    fisicalButtonsLastClickTime = currentTime;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(changeWifiModeInterruptionSemaphore, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
      portYIELD_FROM_ISR();
    }
  }
}