//@orga=GoTronic
//@author=Sylvain G.

#include "Adafruit_DHT/src/Adafruit_DHT.h"

int relayOUT = D2;
int relayIN, magneto, h, t, light;
String str1, str2, str3;

DHT dht(6, DHT11);

void setup() {

  Serial.begin(9600);
  dht.begin();

  pinMode(relayOUT, OUTPUT);

  Spark.function("relay", relaySwitch);

  Spark.variable("h", &h, INT);
  Spark.variable("t", &t, INT);
  Spark.variable("str1", &str1, STRING);
  Spark.variable("str2", &str2, STRING);
  Spark.variable("str3", &str3, STRING);

}

void loop() {

  magneto = digitalRead(4);
  relayIN = digitalRead(2);
  int light = analogRead(A0);

  h = dht.getHumidity();
  t = dht.getTempCelcius();

  if(light < 1000){
    str1 = "Lumière éteinte";
  }else{
    str1 = "Lumière allumée";
  }

  if(relayIN == HIGH){
    str2 = "Relais ON";
  }else{
    str2 = "Relais OFF";
  }

  if(magneto == HIGH){
    str3 = "Porte ouverte";
  }else{
    str3 = "Porte fermée";
    digitalWrite(relayOUT, LOW);
  }

}

int relaySwitch(String command){
  if(magneto == HIGH){
    if(command.equalsIgnoreCase("on")){
      digitalWrite(relayOUT, HIGH);
      return 1;
    }else if(command.equalsIgnoreCase("off")){
      digitalWrite(relayOUT, LOW);
      return 1;
    }
  }else{
    digitalWrite(relayOUT, LOW);
    return 1;
  }
  return -1;
}
