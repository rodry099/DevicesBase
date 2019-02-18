void registerDevice(String servidorNodeRed){

  //guarda nueva configuracion en archivo configuracion.txt
  // primero abre el fichero y lo convierte en un objeto Json

  File setup = SPIFFS.open("/configuracion.txt", "r");
     if(!setup){
       Serial.println("No existe el archivo");
       setup.close();
       return;
     }
       StaticJsonBuffer<512> jsonBuffer;
       JsonObject &root = jsonBuffer.parseObject(setup);
       setup.close();

//elimina y abre el archivo configuracion.txt para escritura

  SPIFFS.remove("/configuracion.txt"); //borra archivo. sino se añadirian los datos
  setup = SPIFFS.open("/configuracion.txt", "w");
  if(!setup){
    Serial.print("error al abrir archivo setup");
  }
  root["servidorNodeRed"] = servidorNodeRed.c_str();
  root["registrado"] = 1;
  root.prettyPrintTo(setup);
  setup.close();
}
