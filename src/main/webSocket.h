#include <Wire.h>
#include <WebSocketsServer.h>
#include "relayController.h"

#ifndef WEB_SOCKET_H
#define WEB_SOCKET_H
  void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
  void socketEmitRelayStatus();
  void emitClock();
  extern WebSocketsServer webSocket;
  extern RelayController relay;


#endif