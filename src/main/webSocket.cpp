#include "webSocket.h"
#include "RTCController.h"
#include "utils.h"


void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    if (strcmp((char *)payload, "mudar-rele") == 0) {
      relay.manuallyToggleRelayState();
    }
  }
}

void socketEmitRelayStatus(){
  webSocket.broadcastTXT("{\"event\": \"relayChange\", \"buffer\":\""+String(relay.isOn)+"\"}" );
}

void emitClock(){
  std::array<int, 3> now = RTCController::getNow();
  String hours = numberToTwoChars(now[0]);
  String minutes = numberToTwoChars(now[1]);
  String buf = "{ \"hora\" : \""+ hours + "\", \"minuto\" : \""+ minutes +"\" }";
  webSocket.broadcastTXT("{\"event\": \"clockUpdate\", \"buffer\":"+buf+"}" );
}