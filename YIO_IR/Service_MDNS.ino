void setupMdns(){
  // Advertise service using MDNS
  if (!MDNS.begin(hostString)) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
  MDNS.addService("wifi-ir-telnet", "tcp", 23);
  MDNS.addService("wifi-ir-http", "tcp", 80);
  Serial.print("Hostname: ");
  Serial.println(hostString);
  Serial.print("mDNS name: ");
  Serial.print(hostString);
  Serial.println(".local");
}
