#include "WifiManager.h"

int WifiManager::APIndicatorLedPort = 18;
int WifiManager::STAIndicatorLedPort = 5;
int WifiManager::changeWifiModeButtonPort = 15;
String WifiManager::defaultPassword = "123456789";
String WifiManager::defaultSSID = "Automada";

void WifiManager::begin(){
  pinMode(STAIndicatorLedPort, OUTPUT);
  pinMode(APIndicatorLedPort, OUTPUT);
  pinMode(changeWifiModeButtonPort, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(changeWifiModeButtonPort), handleChangeWifiModeButton, CHANGE);

  IPAddress local_ip(192,168,1,121);
  IPAddress gateway(192,168,1,1);
  IPAddress subnet(255,255,255,0);
  std::array<String, 3> infos =  getWifiInfos();

  if(infos[2] == "STA"){
    WiFi.begin(infos[0], infos[1]);
    WiFi.config(local_ip, gateway, subnet);
    digitalWrite(STAIndicatorLedPort, HIGH);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Conectando");
    }
  } else {
    digitalWrite(APIndicatorLedPort, HIGH);
    WiFi.softAP(infos[0], infos[1]);
    WiFi.softAPConfig(local_ip, gateway, subnet);
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
  if(storedSSID.isEmpty()){
    storedSSID = defaultSSID;
  }
  if(storedPassword.isEmpty()){
    storedSSID = defaultPassword;
  }
  if(storedMode.isEmpty()){
    storedMode = "AP";
  }
  preferences.end();
  return {storedSSID, storedPassword, storedMode};
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
