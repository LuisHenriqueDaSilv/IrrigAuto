#include "WifiManager.h"
#include <ESPmDNS.h>

int WifiManager::APIndicatorLedPort = 18;
int WifiManager::STAIndicatorLedPort = 5;
int WifiManager::changeWifiModeButtonPort = 15;
String WifiManager::defaultPassword = "123456789";
String WifiManager::defaultSSID = "Automada";
String WifiManager::defaultAlias = "automada";

void WifiManager::begin(){
  pinMode(STAIndicatorLedPort, OUTPUT);
  pinMode(APIndicatorLedPort, OUTPUT);
  pinMode(changeWifiModeButtonPort, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(changeWifiModeButtonPort), handleChangeWifiModeInterruption, CHANGE);

  std::array<String, 3> infos =  getWifiInfos();
  

  if(infos[2].equals("STA")){
    WiFi.begin(infos[0], infos[1]);
    digitalWrite(STAIndicatorLedPort, HIGH);
    digitalWrite(APIndicatorLedPort, LOW);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Conectando");
    }
  } else {
    digitalWrite(APIndicatorLedPort, HIGH);
    digitalWrite(STAIndicatorLedPort, LOW);
    WiFi.softAP(infos[0], infos[1]);
  }

  if (!MDNS.begin(defaultAlias)){
    Serial.println("Erro ao configurar mDNS");
    return;
  }

}

void WifiManager::saveWifiInfos(String ssid, String password, String mode){
  preferences.begin("wifi", false);
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.putString("mode", mode);
  preferences.end();
  esp_restart();
}

std::array<String, 3> WifiManager::getWifiInfos(){
  preferences.begin("wifi", true);
  String storedSSID = preferences.getString("ssid", "");
  String storedPassword = preferences.getString("password", "");
  String storedMode = preferences.getString("mode", "");
  preferences.end();

  if(storedSSID.isEmpty()){storedSSID = defaultSSID;}
  if(storedPassword.isEmpty()){storedSSID = defaultPassword;}
  if(storedMode.isEmpty()){storedMode = "AP";}
  return { storedSSID, storedPassword, storedMode };
}

void WifiManager::initWifiResetProcess(){
  digitalWrite(APIndicatorLedPort, HIGH);
  digitalWrite(STAIndicatorLedPort, HIGH);
}

void WifiManager::resetWifi(){
  digitalWrite(APIndicatorLedPort, LOW);
  digitalWrite(STAIndicatorLedPort, LOW);
  saveWifiInfos("Automada", "123456789", "AP");
}

std::list<String> WifiManager::scanWifi(){
  int numberOfWifis = WiFi.scanNetworks();
  std::list<String> SSIDs;
  for(int i = 0; i < numberOfWifis; i++){
    SSIDs.push_back(WiFi.SSID(i));
  }
  return SSIDs;
}
