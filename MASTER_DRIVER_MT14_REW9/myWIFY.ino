void  WIFIMode() {
  delay(2000);
  if (WiFi.status() == WL_NO_MODULE)                      // check for the WiFi module:
  {
    Serial.println("Communication with WiFi module failed!");
    testAp();
   }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");
  }
  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
  String mode = "";
  WiFi.config(ip);
  if (wifimode == 0) {
    mode = "Access point";
    Serial.print("Creating access point named: "); Serial.println(ssid);
    status = WiFi.beginAP(ssid, pass);
    if (status != WL_AP_LISTENING)
    {
      Serial.println("Creating access point failed");
      testAp();
      //while (true);
    }
  }
  else {
    mode = "Client";
    int conteggio = 0;
    while (status != WL_CONNECTED || conteggio > 10)                                            // attempt to connect to Wifi network:
    {
      Serial.print("setup Attempting to connect to SSID: "); Serial.println(ssid);
      status = WiFi.begin(ssid, pass);                                        // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      delay(500);                                                             // wait 5 seconds for connectio
      conteggio ++;
       Serial.print("Status wile: "); Serial.println(status);
    }
  }
  Serial.print("Status : "); Serial.println(status);
  if(status != WL_AP_LISTENING && status != WL_CONNECTED)
  {
    Serial.print("NOT WIFI in mode : "); Serial.println(mode);
  } 
  else
   { 
    Serial.print("Set to : "); Serial.println(mode);
   }
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}
