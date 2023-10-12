
#define ONE_WIRE_BUS 3
#define Anzahl_Sensoren_DS18B20 2 // Anzahl der angeschlossenen Sensoren - Mögliche Werte: '0','1','2',... 

#include "OneWire.h"; 
#include "DallasTemperature.h"; 

#define DS18B20_Aufloesung 12
DeviceAddress DS18B20_Adressen;
 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature myDS18B20(oneWire); 
 
const float No_Val = 999.99;
float Temperatur[Anzahl_Sensoren_DS18B20];   

// Für beelogger-SMD: Aktivierung der Stromversorgung für Sensoren, Module und DS3231 
#define Power_Pin 4
 
void setup(void) {
  Serial.begin(9600);
  Serial.println("DS18B20 Test");
  Serial.println();
  digitalWrite(Power_Pin, HIGH);
  pinMode(Power_Pin, OUTPUT);
  delay(1000);
 
  Serial.print("Anzahl aktivierter Sensoren: ");
  Serial.println(Anzahl_Sensoren_DS18B20);
 
  if ((Anzahl_Sensoren_DS18B20 > 0)) {
    myDS18B20.begin();
    Serial.print("Anzahl angeschlossener Sensoren: ");
    Serial.println(myDS18B20.getDeviceCount(), DEC);
    Serial.println();
 
    for(byte i=0 ;i < myDS18B20.getDeviceCount(); i++) {
      if(myDS18B20.getAddress(DS18B20_Adressen, i)) {
        myDS18B20.setResolution(DS18B20_Adressen, DS18B20_Aufloesung);
      }
    }
  }
}
void loop(void) {
  if ((Anzahl_Sensoren_DS18B20 > 0)) {
    myDS18B20.requestTemperatures();
    for(byte i=0 ;i < Anzahl_Sensoren_DS18B20; i++) {
      if (i < myDS18B20.getDeviceCount()) {
      
        Serial.print("Sensor ");
        Serial.print(i+1);
        Serial.print(": "); 
        
        Temperatur[i] = myDS18B20.getTempCByIndex(i);
        if (Temperatur[i] == DEVICE_DISCONNECTED_C) {
            Temperatur[i] = No_Val;
          Serial.println("Fehler");
        }
        else {
          Serial.print(Temperatur[i]);
          Serial.println(" 'C");
        }
      }
    }
  }
  Serial.println();
  delay(1000);
}