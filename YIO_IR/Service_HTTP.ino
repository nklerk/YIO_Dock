

void handleHttpRoot() {
 serverHttp.send(200, "text/html", "<body><h1>Wifi-IR, send Pronto HEX formater infrared signals!</h1><form onsubmit=\"window.open('/pronto?code=' + document.getElementById('pronto').value, '_new')\"> Pronto HEX:<br> <input type=\"text\" name=\"code\" id=\"pronto\"><br> <input type=\"submit\" value=\"Send\"> </form> <p> Find IR codes at: <a href=\"http://irdb.tk/find/\">irdb.tk</a> </p></body>");
}


void handleHttpPronto(){
  for (uint8_t i=0; i<serverHttp.args(); i++){
    if(serverHttp.argName(i) == "code") 
    {
      boolean didSend = handlePronto(serverHttp.arg(i));
      if (didSend) {
        serverHttp.send(200, "text/html", "OK");
      } else {
        serverHttp.send(200, "text/html", "ERROR");
      }
    }
  }
}

void handleHttpRecord(){
  recordIrStart();
  
}

void returnRecordIrResponse(String responseJson){
  Serial.print("Response JSON: ");
  Serial.println(responseJson);
  serverHttp.send(200, "application/json", responseJson);
}

void returnRecordIrFailed(){
  Serial.print("Recorded IRcode: Failed!");
  serverHttp.send(400, "application/json", "{\"Error\":\"Failed to record IR code\"}");
}


void setupHttp(){
  serverHttp.on("/", handleHttpRoot);
  serverHttp.on("/pronto", handleHttpPronto);
  serverHttp.on("/record", handleHttpRecord);
  serverHttp.onNotFound(handleHttpRoot);
  serverHttp.begin();
  Serial.println("Http Server started");
}
