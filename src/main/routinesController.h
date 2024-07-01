#include "relayController.h"

#ifndef ROUTINES_CONTROLLER_H
#define ROUTINES_CONTROLLER_H
  #include "Wire.h"
  #include <WebServer.h>
  extern RelayController relay;
  extern WebServer server;
  class RoutinesController {
    public: 
      static void create();
      static void delete_();
      static void deleteAll();
      static void readAll();
  };
#endif