#include <SoftwareSerial.h> 
#include "DHT.h" 
#include <LiquidCrystal.h> 
#include <ArduinoJson.h>
#include "MQ135.h" 
SoftwareSerial ArduinoMega(6,7); 
//komunikacije
#define dhtpin 5
#define dhttip DHT11 
MQ135 analogniulaz(A1); 
LiquidCrystal displej(8,9,10,11,12,13);
DHT dht(dhtpin,dhttip);
void setup() {

Serial.begin(115200);
ArduinoMega.begin(115200);

dht.begin();

displej.begin(16,2);
displej.clear();
}

StaticJsonBuffer<1000> jsonBuffer;JsonObject& root=jsonBuffer.createObject();
void loop() {

float otpor=analogniulaz.getResistance();
float co=analogniulaz.getCO(otpor);
float co2=analogniulaz.getCO2(otpor);
float nh4=analogniulaz.getNH4(otpor);
//mjerenje temperature i vlažnosti
int t=dht.readTemperature();
int h=dht.readHumidity();
int f=dht.readTemperature(true);

if (isnan(t) ||isnan(f) || isnan(h)) {
Serial.println("Nema ocitavanja sa dht11 senzora!!!");
return;
}

root ["temp"]=t;
root ["tempf"]=f;
root ["vlaz"]=h;
root ["co"]=co;
root ["co2"]=co2;
root ["nh4"]=nh4;

Serial.println("-----------------------");
Serial.print("Temperatura (°C): ");
Serial.print(t);
Serial.println(" °C");
Serial.print("Temperatura (F): ");
Serial.print(f);Serial.println(" F");
Serial.print("Vlaznost (%): ");
Serial.print(h);
Serial.println(" %");
Serial.print("CO level (ppm): ");
Serial.print(co,2);
Serial.println(" ppm");
Serial.print("CO2 level (ppm): ");
Serial.print(co2,2);
Serial.println(" ppm");
Serial.print("NH4 level (ppm): ");
Serial.print(nh4,2);
Serial.println(" ppm");
Serial.println("-----------------------");
delay(1000);
root.printTo(ArduinoMega); 

displej.clear();
displej.setCursor(0,0);
displej.print("Temp: ");
displej.print(t);
displej.print("\337C ");
displej.print("| ");
displej.print(f);
displej.print("F");
displej.setCursor(0,1);
displej.print("Vlaz: ");
displej.print(h);
displej.print("%");
delay(2000);
displej.clear();displej.setCursor(0,0);
displej.print("CO : ");
displej.print(co);
displej.print("ppm");
displej.setCursor(0,1);
displej.print("CO2: ");
displej.print(co2);
displej.print("ppm");
delay(2000);
displej.clear();
displej.setCursor(0,0);
displej.print("NH4: ");
displej.print(nh4);
displej.print("ppm");
}
