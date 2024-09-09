#include "httpServer.h"


HTTPServer::HTTPServer() : server(80) {}

void HTTPServer::setRoutes(){
	server.on("/", [this](){server.send(200, "text/html", Pages::landingPage());});
	server.on("/configurar-relogio", [this](){server.send(200, "text/html", Pages::clockAdjustPage());});
	server.on("/configurar-rotina", [this](){server.send(200, "text/html", Pages::createRoutinePage());});
	server.on("/excluir-rotina", [this](){handleDeleteRoutineRequest(server);});
	server.on("/apagar-rotinas", [this](){handleDeleteAllRoutinesRequest(server);});
	server.on("/adicionar-rotina", [this](){handleCreateRoutineRequest(server);});
	server.on("/rotinas", [this](){handleReadAllRoutinesRequest(server);});
	server.on("/setar-relogio", [this](){handleConfigureClockRequest(server);});
	server.on("/mudar-rele", [this](){handleToggleRelayRequest(server);});
	server.on("/rede", [this](){server.send(200, "text/html", Pages::configureNetwork());});
	server.on("/configurar-rede", [this](){handleConfigureNetwork(server);});
}

void HTTPServer::handleClient(){
	server.handleClient();
}

void HTTPServer::begin(){
  setRoutes();
  server.begin();
  Serial.println("HTTP server started");
}

void HTTPServer::handleConfigureClockRequest(WebServer& server){
  String buf = "";
  String sentHours = server.arg(0);
  String sentMinutes = server.arg(1);
  String sentDay = server.arg(2);
  
  bool lengthOfSentValuesIsInvalid = ( 
    (sentHours.isEmpty() || sentMinutes.isEmpty() || sentDay.isEmpty()) && 
    (sentHours.length() > 2 || sentMinutes.length() > 2 || sentDay.length() > 1)
  ); 
  if(lengthOfSentValuesIsInvalid){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Horario inválido\"}");
    return;
  }

	int hours = atoi(sentHours.c_str());
	int minutes = atoi(sentMinutes.c_str());
	int day = atoi(sentDay.c_str());
  bool sentValuesNotIsANumber = (
    (
      hours == 0 && !sentHours.equals("0") && !sentHours.equals("00")
    ) || (
      minutes == 0 && !sentMinutes.equals("0") && !sentMinutes.equals("00")
    ) || (
      day == 0 && !sentDay.equals("0") && !sentDay.equals("00")
    )
  );
  if(sentValuesNotIsANumber){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Horario inválido\"}");
    return;
  }
  bool theSentTimeIsWithinADayRange = hours > 23 || hours <0 || minutes > 59 || minutes <0 || day < 0 || day > 6;
  if(theSentTimeIsWithinADayRange){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Horario inválido\"}");
    return;
  }

	RTCController::configureClock(hours, minutes, day);
  server.send(200, "text/json", "{\"status\": \"success\"}");
}

void HTTPServer::handleToggleRelayRequest(WebServer& server){

  String sentId = server.arg(0);
  bool lengthOfSentIdIsInvalid = sentId.isEmpty() || sentId.length() > 1;
  if(lengthOfSentIdIsInvalid){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Id inválido\"}");
    return;
  }
  int id = atoi(sentId.c_str());
  bool sentIdNotIsANumber = !sentId.equals("0")  && id == 0;
  if(sentIdNotIsANumber){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Id inválido\"}");
    return;
  }
  bool sentIdIsInvalid = id < 1 || id > NUMBER_OF_RELAYS;
  if(sentIdIsInvalid){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Id inválido\"}");
    return;
  }

  RelayController::toggleRelayById(id);
  server.send(200, "text/json", "{\"status\": \"success\"}");
}

void HTTPServer::handleDeleteRoutineRequest(WebServer& server){
  String data = server.arg(0);
  Serial.println(data);
  bool sentDataLengthIsInvalid = data.isEmpty() || data.length() > ROUTINE_LENGTH;
  if(sentDataLengthIsInvalid){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Rotina inválida\"}");
    return;
  }

  int sentValues[ROUTINE_LENGTH/2];
  bool someSentCharIsNotANumber = false;
  for(int i = 0; i<ROUTINE_LENGTH; i+=2){
    String valueString = data.substring(i, i+2);
    int valueInt = atoi(valueString.c_str());
    if(valueInt == 0 && !valueString.equals("0") && !valueString.equals("00")){
      someSentCharIsNotANumber = true;
      break;
    }
    sentValues[i/2] = valueInt;
  }

  if(someSentCharIsNotANumber){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Rotina inválida\"}");
    return;
  }

  RoutineStruct routineToDelete = {
    sentValues[0],
    sentValues[1],
    sentValues[2],
    sentValues[3],
    sentValues[4]
  }; 
  bool routineExist = RoutinesController::routineExist(routineToDelete);
  if(!routineExist){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Rotina não encontrada\"}");
    return; 
  }

	RoutinesController::delete_(routineToDelete);
  server.send(200, "text/json", "{\"status\": \"success\"}");
}

void HTTPServer::handleDeleteAllRoutinesRequest(WebServer& server){
	RoutinesController::deleteAll();
  server.send(200, "text/json", "{\"status\": \"success\"}");
}

void HTTPServer::handleReadAllRoutinesRequest(WebServer& server){
  std::list<RoutineStruct> routines = RoutinesController::getRoutines();
  String routinesString = "";
  for(RoutineStruct routine: routines){
    routinesString += 
      numberToTwoChars(routine.hourToTurnOn) +
      numberToTwoChars(routine.minuteToTurnOn) +
      numberToTwoChars(routine.hourToTurnOff) +
      numberToTwoChars(routine.minuteToTurnOff) +
      numberToTwoChars(routine.relayIndex);
  }
  String buf = "{ \"routines\": \"" + routinesString + "\", \"number\": \""+ routines.size() +"\"}";
  server.send(200, "text/json", buf);
}

void HTTPServer::handleCreateRoutineRequest(WebServer& server){
  String data = server.arg(0);
  bool sentDataLengthIsInvalid = data.isEmpty() || data.length() > ROUTINE_LENGTH;
  if(sentDataLengthIsInvalid){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Rotina inválida\"}");
    return;
  }

  int sentValues[ROUTINE_LENGTH/2];
  bool someSentCharIsNotANumber = false;
  for(int i = 0; i<ROUTINE_LENGTH; i+=2){
    String valueString = data.substring(i, i+2);
    int valueInt = atoi(valueString.c_str());
    if(valueInt == 0 && !valueString.equals("0") && !valueString.equals("00")){
      someSentCharIsNotANumber = true;
      break;
    }
    sentValues[i/2] = valueInt;
  }

  if(someSentCharIsNotANumber){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Rotina inválida\"}");
    return;
  }

  RoutineStruct newRoutine = {
    sentValues[0],
    sentValues[1],
    sentValues[2],
    sentValues[3],
    sentValues[4]
  };

  bool routineExists = RoutinesController::routineExist(newRoutine);
  if(routineExists){
    String buf = "{\"status\": \"error\", \"message\": \"Rotina já existente\"}";
    server.send(400, "text/json", buf);
    return;
  }

  std::list<RoutineStruct> savedRoutines = RoutinesController::getRoutines();
	RoutinesController::createRoutine(
    newRoutine, 
    savedRoutines.size()
  );

  String buf = "{\"status\": \"success\"}";
  server.send(200, "text/json", buf);
}

void HTTPServer::handleConfigureNetwork(WebServer& server){
  // Caso a configuração esteja sendo feita em modo de terceiro, verifica se a rede já existe 
  String sentSsid = server.arg(0);
  String sentPassword = server.arg(1);
  String sentMode = server.arg(2);

  if(sentSsid.isEmpty() || sentPassword.isEmpty() || sentMode.isEmpty()){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Informações não suficientes\"}");
    return;
  }

  if(sentSsid.length() > 32){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"SSID inválido\"}");
    return;
  }

  if(sentPassword.length() < 8 || sentPassword.length() > 63){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Senha inválida\"}");
    return;
  }

  if(!sentMode.equals("AP") && !sentMode.equals("STA")){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Modo inválido\"}");
    return;
  }

  bool networkAlreadyExists = false;
  std::list<String> wifiLists = WifiManager::scanWifi();
  for(String SSID: wifiLists){
    if(SSID.equals(sentSsid)){
      networkAlreadyExists = true;
    }
    break;
  }

  if(networkAlreadyExists && sentMode.equals("AP")){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Impossivel criar a rede informada, aparentemente ela já existe\"}");
    return;
  }

  if(sentMode.equals("STA") && !networkAlreadyExists){
    server.send(400, "text/json", "{\"status\": \"error\", \"message\": \"Rede não encontrada\"}");
    return;
  }
  server.sendHeader("Location", "/", true);
  server.send(200, "text/json", "");
  WifiManager::saveWifiInfos(sentSsid, sentPassword, sentMode);

}