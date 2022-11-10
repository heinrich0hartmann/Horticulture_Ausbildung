// Bibliotecas
 #include <Wire.h>
 #include <BH1750.h>
 #include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd (0x27,20,4);

 // definiçao de objeto
 BH1750 sensor;
 
void setup() 
{
  // velocidade de comunicação serial
  Serial.begin(9600);
  Wire.begin();
  sensor.begin();
  Serial.println(" Monitoramento de luminosidade sensor BH1750 ");
  lcd.begin(16,2);
  lcd.setBacklight(HIGH);
  lcd.setCursor(2,0);
  lcd.print("LUXIMETRO");
}

void loop() 
{
  // variavel para leitura da luminosidade
  unsigned lux = sensor.readLightLevel();
  lcd.setCursor(2,1);
  lcd.print("LUX: ");
  lcd.setCursor(6,1);
  lcd.print(lux);  
  Serial.print(" Luminosidade: ");
  Serial.print(lux);
  Serial.println(" Lux ");
  delay(300);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SENSOR - BH1750");
}
