#include <WiFi.h>
#include <list>
#include <Preferences.h>
#include <esp_system.h>
#include "interruptionHandlers.h"

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H
	extern Preferences preferences;
	class WifiManager {
		public: 
			static int STAIndicatorLedPort;
			static int APIndicatorLedPort;
			static int changeWifiModeButtonPort;
			static String defaultPassword;
			static String defaultSSID;
			static String defaultAlias;

			static void begin();
			static void saveWifiInfos(String ssid, String password, String mode);
			static std::array<String, 3> getWifiInfos();
			static void initWifiResetProcess();
			static void resetWifi();
			static std::list<String> scanWifi();
	};
#endif 