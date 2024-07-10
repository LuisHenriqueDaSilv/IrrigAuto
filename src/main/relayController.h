#include <WebServer.h>

#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H
  extern WebServer server;
  class RelayController {
    public:
      const int port = 18;
      bool isOn;
      bool manuallyTurnedOn = false;
      bool manuallyTurnedOff = false;
    
      void turnOff();
      void turnOn();
      // Routes:
      void getStatus();
      void clientTurnOn();
      void clientTurnOff();
      void manuallyToggleRelayState();
      void physicallyToggleRelayState();
      
  };
  
#endif