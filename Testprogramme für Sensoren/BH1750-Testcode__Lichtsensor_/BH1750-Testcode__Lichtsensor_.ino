#include <AS_BH1750.h>


//More information at: http://www.aeq-web.com/?ref=arduinoide

#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;
int lux;
void setup(){

  Serial.begin(9600);
  lightMeter.begin();
  Serial.println("BH1750 Testsoftware");

}


void loop() {

  lux = lightMeter.readLightLevel();
  Serial.print("Licht: ");
  Serial.print(lux);
  Serial.println(" lx (Lux)");
  delay(500);

}
