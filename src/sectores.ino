void sectores(int canal, String onOff){
  int estadoPuerto = 1;
  if(onOff.equals("on")) estadoPuerto = 0;
  if(onOff.equals("off")) estadoPuerto = 1;

  if(canal>=0 && canal <=7){
    Serial.println("puerto 1");
    PUERTO1.write(canal,estadoPuerto);

    if (onOff.equals("on")){
      digitalWrite(LED_BUILTIN, LOW);
    }
    if(onOff.equals("off")){
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}
