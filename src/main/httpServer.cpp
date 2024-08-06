#include "httpServer.h"
#include "pages.h"
#include "routinesController.h"
#include "RTCController.h"
#include "relayController.h"
#include "utils.h"
#include "eepromManager.h"

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
  String clientHours = server.arg(0);
  String clientMinutes = server.arg(1);

	int hours = atoi(clientHours.c_str());
	int minutes = atoi(clientMinutes.c_str());

	RTCController::configureClock(hours, minutes);
  server.sendHeader("Location", "/",true); 
  server.send(302, "text/plain", "");
}

void HTTPServer::handleToggleRelayRequest(WebServer& server){
  int id = atoi(server.arg(0).c_str());
  RelayController::toggleRelayById(id);
  server.send(200, "text/plain", "");
}

void HTTPServer::handleDeleteRoutineRequest(WebServer& server){
  String routineToDelete = server.arg(0);
	RoutinesController::delete_(routineToDelete);
  server.send(200, "text/plain", "");
}

void HTTPServer::handleDeleteAllRoutinesRequest(WebServer& server){
	RoutinesController::deleteAll();
	server.sendHeader("Location", "/",true);
  server.send(302, "text/plain", "");
}

void HTTPServer::handleReadAllRoutinesRequest(WebServer& server){
  String routines = getRoutinesInEEPROM();
  int numberOfRoutines = getNumberOfRoutines(routines);
  String buf = "{ \"routines\": \"" + routines + "\", \"number\": \""+ numberOfRoutines +"\"}";
  server.send(200, "text/json", buf);
}

void HTTPServer::handleCreateRoutineRequest(WebServer& server){
  String hourToTurnOnStr = server.arg(0);
  String minuteToTurnOnStr = server.arg(1);
  String hourToTurnOffStr = server.arg(2);
  String minuteToTurnOffStr = server.arg(3);
  String relayIndexStr = server.arg(4);

  int hourToTurnOn = atoi(hourToTurnOnStr.c_str());
  int minuteToTurnOn = atoi(minuteToTurnOnStr.c_str()); 
  int hourToTurnOff = atoi(hourToTurnOffStr.c_str()); 
  int minuteToTurnOff = atoi(minuteToTurnOffStr.c_str()); 
  int relayIndex = atoi(relayIndexStr.c_str());

	RoutinesController::create(
		hourToTurnOn,
		minuteToTurnOn,
		hourToTurnOff,
		minuteToTurnOff,
		relayIndex
	);

  server.sendHeader("Location", "/", true); 
  server.send(302, "text/plain", "");
}