#include <WebServer.h>
#include <WiFi.h>
#include <list>
#include "pages.h"
#include "routinesController.h"
#include "RTCController.h"
#include "relayController.h"
#include "utils.h"
#include "eepromManager.h"
#include "WifiManager.h"

#ifndef HTTPSERVER_H
#define HTTPSERVER_H
class HTTPServer {
  private: 
    WebServer server;
    static void handleConfigureClockRequest(WebServer& server);
    static void handleToggleRelayRequest(WebServer& server);
    static void handleDeleteRoutineRequest(WebServer& server);
    static void handleDeleteAllRoutinesRequest(WebServer& server);
    static void handleConfigureNetwork(WebServer& server);
    static void handleReadAllRoutinesRequest(WebServer& server);
    static void handleCreateRoutineRequest(WebServer& server);
  public:
    HTTPServer();
    void setRoutes();
    void begin();
    void handleClient();
};
#endif