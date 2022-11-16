//DS18B20 Temperatursensor Arduino Sketch
//Website: IoTspace.dev
//
//
#include <OneWire.h>                        //OneWire Bibliothek einbinden
#include <DallasTemperature.h>              //DallasTemperatureBibliothek einbinden

#define ONE_WIRE_BUS 2                      //Data ist an Pin 2 des Arduinos angeschlossen

OneWire oneWire(ONE_WIRE_BUS);              //Start des OneWire Bus
DallasTemperature sensors(&oneWire);        //Dallas Temperature referenzieren


void setup()
{ 
 Serial.begin(9600);                        // Start der seriellen Konsole 
 Serial.println("DS18B20 Demo"); 
 sensors.begin();                           // Sensor Start
} 

void loop() { 
 sensors.requestTemperatures();             // Temperaturen Anfragen 
 Serial.print("Temperatur: "); 
 Serial.print(sensors.getTempCByIndex(0));  // "byIndex(0)" spricht den ersten Sensor an  
 delay(1000);                               // eine Sekunde warten bis zur nächsten Messung
} 
