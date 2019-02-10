void arranqueNormalJson(){

  byte octetos[4];
  unsigned int indice = 0;
  String temp = "";
 //***********************************************************
//carga archivo configuracion y lo convierte en un objeto Json
//************************************************************

File setup = SPIFFS.open("/configuracion.txt", "r");
   if(!setup){
     Serial.println("No existe el archivo");
     setup.close();
     return;
   }
     StaticJsonBuffer<512> jsonBuffer;
     JsonObject &root = jsonBuffer.parseObject(setup);
     const char* ssid = root["ssid"];
     const char* password = root["password"];
     const char* ip = root["ip"];
     const char* id = root["id"];
     const char* canales = root["canales"];
     const char* servidorMqtt = root["servidor"];
     int reg = root["registrado"];
     setup.close();
     id_disp = String((const char*)root["id"]);
     ServerMqtt = String((const char*)root["servidor"]);
     categoria = String((const char*)root["categoria"]);
     Topic = String((const char*)root["topic"]);
     Serial.println(Topic);
     registrado = reg; //guarda en variable global registrado el valor de reg 0= no registrado 1= registrado
                      // valor inicial igual a no registrado en el sistema
  //**************************************************
  // convierte const char* en un array de 4 elementos
 //***************************************************

 for(int cont = 0; cont < 4; cont++){
     while(ip[indice]!='.'){
        temp += ip[indice];
        indice++;
        if(indice>=strlen(ip)) break;

     }
     octetos[cont] = temp.toInt();
     temp = "";
     indice++;
   }
  //**********************************************
 //           conectando a red WiFi
 //***********************************************

 //conecta a router

 WiFi.mode(WIFI_STA);
 IPAddress ip_f(octetos[0],octetos[1],octetos[2],octetos[3]);
 IPAddress subnet(255,255,255,0);
 IPAddress gateway(octetos[0],octetos[1],octetos[2],1);
 WiFi.config(ip_f,gateway,subnet);
 WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

            Serial.println("");
            Serial.println("WiFi conectada");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            //***********************************************************
           //carga archivo configuracion y lo convierte en un objeto Json
           //************************************************************

                root.remove("ssid");
                root.remove("password");
                root.remove("ip");
                root.remove("servidor");
                output = "";
                root.printTo(output);
                Serial.println("datos" + output);

}
