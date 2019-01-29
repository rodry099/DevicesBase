void callback(char* topic, byte* payload, unsigned int length){


  const int capacity = JSON_OBJECT_SIZE(4);
  StaticJsonBuffer<capacity> DatosMqtt;
  char datos[80];
  unsigned int i=0;
  for (i=0;i<length;i++) {
    datos[i] = (char)payload[i];
  }
  JsonObject& obj = DatosMqtt.parseObject(datos);

      if (obj.success()) {
          //Serial.println("parseObject() succeeded");
        } else {
        //Serial.println("parseObject() FAILED");
        }
        canalRiego = obj["canal"];
        estadoRiego = obj["status"];

        String onOff(estadoRiego);
        String Stopic(topic);
        
    /***************************************
      si recibe el topic device/setup
      llama a la subrutina registerDevices
      y guarda 1 en la variable registrado
      del archivo configuracion
    ***************************************/
    if(Stopic.equals("device/setup")){
      registerDevice();
      registrado = 1;
      return;
    }

    /***************************************
      enciende o apaga canal de riego
    ****************************************/
    if (onOff.equals("on")||onOff.equals("off")){
      sectores(canalRiego,onOff);
      return;
    }
    /****************************************
        pone apagados todos los puertos
    *****************************************/
    if (onOff.equals("reset")){
      PUERTO1.write8(0b11111111);
      PUERTO2.write8(0b11111111);
      return;
    }

}
