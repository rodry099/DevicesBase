void reconnect() {
  willmsg = id_disp + "/status";
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = id_disp; //id_disp
    if (client.connect(clientId.c_str(),willmsg.c_str(),1,0,"offline")) {
      Serial.println("connected");
      // Once connected, publish an announcement...

      //const char* datosDipositivo = output.c_str();
      client.publish(willmsg.c_str(), "online");

      // ... and resubscribe

      client.subscribe("device/setup");
      if(registrado == 1){
      String topicS = servidorNodeRed + "/" + categoria + "/" + id_disp + "/switch";
      client.subscribe(topicS.c_str());
      Serial.println(topicS);
      String topicF = servidorNodeRed + "/" + categoria + "/" + id_disp + "/feedback";
      Serial.println(topicF);
      client.subscribe(topicF.c_str());
    }

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
