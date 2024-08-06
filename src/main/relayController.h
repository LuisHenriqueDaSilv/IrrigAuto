#include "interruptionHandlers.h"
#include "webSocket.h"


#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

  #define NUMBER_OF_RELAYS 4

  extern WebSocket webSocket;
  class RelayController {
    public:
      RelayController();
      RelayController(int port, int buttonPort, int id_);

      static void emitStatus(int id, bool status);
      static void toggleRelayById(int id);

      int port;
      int id;
      int buttonPort;
      bool isOn;
      bool manuallyTurnedOn = false;
      bool manuallyTurnedOff = false;
    
      void turnOff();
      void turnOn();
      // Routes:
      void clientTurnOn();
      void clientTurnOff();
      void manuallyToggleRelayState();
      
  };
  extern RelayController relays[NUMBER_OF_RELAYS];
#endif