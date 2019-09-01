void setupWifi(){ 
  WiFiManager wifiManager;
  sprintf(hostString, "Wifi-IR_%06X", ESP.getChipId());
  WiFi.hostname(hostString);
  
  //wifiManager.resetSettings(); // Remove stored WiFi Settings.
  
  wifiManager.setAPCallback(configModeCallback);
  if(!wifiManager.autoConnect(hostString)) {
    Serial.println("failed to connect and hit timeout");
    ESP.reset();
    delay(1000);
  } 
  
  Serial.print(F("Connected to wifi. Using IP: "));
  Serial.println(WiFi.localIP());

}
