#include "webSocket.h"
#include "RTCController.h"
#include "utils.h"

WebSocket::WebSocket(){
}

void WebSocket::begin(){
  socket.begin();
  Serial.println("WebSocket server beginned");
}

void WebSocket::emitEvent(String buffer){
  socket.broadcastTXT(buffer);
}