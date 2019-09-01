void setupTcp(){
  serverTcp.begin();
}

void handleTcpPronto(){
  WiFiClient tcpClient = serverTcp.available();
  
  if (tcpClient) {
    if(tcpClient.connected())
    {
      Serial.println("Client Connected");
    }
    
    while(tcpClient.connected()){      
      while(tcpClient.available()>0){
        // read data from the connected client
        String pronto = tcpClient.readStringUntil('\r');
        boolean didSend = handlePronto(pronto);
        if (didSend) {
          //tcpClient.write("1\r");
        } else {
          //tcpClient.write("Error!\r\n");
        }
      }
      //Send Data to connected client
      while(Serial.available()>0)
      {
        tcpClient.write(Serial.read());
      }
    }
    tcpClient.stop();
    Serial.println("Client disconnected");    
  }
}
