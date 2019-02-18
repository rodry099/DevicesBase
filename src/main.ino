
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <PCF8574.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define DIRECCION_PCF8574 0x20
#define DIRECCION_PCF8574_2 0x21

void configInicial();
void arranqueNormal();
void callback(char*, byte*, unsigned int);
void reconnect();
void registerDevice();

WiFiClient espClient;
PubSubClient client(espClient);
//Variables **********************
int pinInt = 2; //pin interruptor
String id_disp = "";
String output = "";
String canal;
String willmsg; //topic direccion dispositivo
String ServerMqtt; // direccion del Brokker mqtt
String categoria; //categoria del dispositivo
String servidorNodeRed;
unsigned int registrado = 0; ///////provisional volver a poner a cero!!!!!!
int canalRiego;
const char* estadoRiego;

//Inicializacion Wifi **************
IPAddress ip(192, 168, 0, 1);
ESP8266WebServer server(80);
WiFiServer servidor(8080);
PCF8574 PUERTO1(DIRECCION_PCF8574);
PCF8574 PUERTO2(DIRECCION_PCF8574_2);

void setup() {

   Serial.begin(115200);
   bool result = SPIFFS.begin();
   Serial.println("SPIFFS opened: " + result);

     File f = SPIFFS.open("/configuracion.txt", "r");
      if(!f){
        f.close();
        configInicial(); //inicia como AP y permite configurar conexion a router
      }

    // inicia normalmente conectando a la red que se haya configurado

    arranqueNormalJson();
    servidor.begin();
    client.setServer(ServerMqtt.c_str(), 1883);
    client.setCallback(callback);
    pinMode(pinInt,OUTPUT); //pin para activar rele;
    digitalWrite(pinInt, 1);

    PUERTO1.write8(0b11111111); // pone apagados todos los puertos
    PUERTO2.write8(0b11111111);
    if(registrado == 1){
      Serial.println("Dispositivo registrado en el sistema");
    }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(registrado == 0){
    client.publish("devices", output.c_str());
    Serial.println("Not registered");
    delay(5000);
    }
}
