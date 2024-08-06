#include <Wire.h>
#include <WebSocketsServer.h>

#ifndef WEB_SOCKET_H
#define WEB_SOCKET_H
  class WebSocket {
    public: 
      WebSocketsServer socket = WebSocketsServer(81);
      WebSocket();
      void begin();
      void emitEvent(String buffer);
  };
#endif