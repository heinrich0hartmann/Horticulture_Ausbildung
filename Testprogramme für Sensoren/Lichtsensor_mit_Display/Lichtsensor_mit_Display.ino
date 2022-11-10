// Bibliotecas
 #include <Wire.h>
 #include <BH1750.h>
 #include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd (0x27,20,4);

 // definiçao de objeto
 BH1750 sensor;
 
void setup() 
{
  //Serielle Übertragung an den Arduino
  Serial.begin(9600);
  Wire.begin();
  sensor.begin();                                           //Sensorstart
  Serial.println("Lichtintensität gemessen von: BH1750 ");  //Gibt in Konsole Text aus 1 malig
  lcd.begin(20,4);
  lcd.setBacklight(HIGH);
}

void loop() 
{
  unsigned lux = sensor.readLightLevel(); //Auslesen des Sensors
  //Anzeige aud Display
  lcd.setCursor(11,0);                    
  lcd.print(lux);
  lcd.setCursor(17,0);
  lcd.print("LUX");  

  //Anzeige in Konsole
  Serial.print(" Lichtintensität: ");
  Serial.print(lux);
  Serial.println(" Lux ");
  delay(1000);
  
  lcd.clear();                            //Display löschen
  
  lcd.setCursor(0,0);
  lcd.print("Helligkeit:");
}
