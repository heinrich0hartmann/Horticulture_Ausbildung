//Bibliotheken einfügen

#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NewPing.h>
#include <AS_BH1750.h>

//Definitionen

  //Lichtsensor
BH1750 lightMeter;

  //Ultraschallsensor
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

  //Temperatursensor
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

  //Feuchtigkeitssensor
const int humid = 7;  //Variable für Pin von Humiditysensor

  //Display
LiquidCrystal_I2C lcd(0x27,20,4); //LCD Display definieren

  //Relais
const int rWasser = 8;  //Relais 1
const int rLicht = 9;   //Relais 2
const int rLuft = 10;   //Relais 3


void setup (){

  Serial.begin(9600);
  Wire.begin();             //I2C beginnt
  lightMeter.begin();       //Lichtsensor beginnt
  sensors.begin();          //Temperatursensor beginnt
  lcd.init();               //LCD starten
  lcd.backlight();          //LCD Hintergrundbeleuchtung starten
  pinMode(humid, INPUT);    //PIN 7 als Input für humid festgelegt

  //Relais
  pinMode(rWasser, OUTPUT); //Relais Als OUTPUTS festlegen
  pinMode(rLicht, OUTPUT);
  pinMode(rLuft, OUTPUT);
  
}

void loop() {
//Sensoren
  //Abfrage Lichtsensor       Variable = lux
  int lux = lightMeter.readLightLevel();

  //Abfrage Ultraschallsensor Variable = distance
  unsigned int distance = sonar.ping_cm();

  //Abfrage Temperatursensor  Variable = temp
  signed int temp = sensors.getTempCByIndex(0);

  //Humidity                  Variable = humid
  
//Ausgabegeräte
//______________________________________________________________
  
  //LCD Display
  lcd.setCursor(0,0);   //Temperatur
  lcd.print("Temp: ");  
  lcd.setCursor(0,6);
  lcd.print(temp);      //Variable temp ausgeben
  
  lcd.setCursor(1,0);   //Lichtintensität
  lcd.print("LUX: ");
  lcd.setCursor(1,5);
  lcd.print(lux);       //Variable lux ausgeben

  lcd.setCursor(2,0);   //Humitity
  lcd.print("HUM: ");
  lcd.setCursor(2,5);
  if (humid == 1){
    lcd.print("dry");
  }
  else {
    lcd.print("wet");
  }
  // lcd.print(humid);     //Variable humid ausgeben

  lcd.setCursor(3,0);   //Wasserstand
  lcd.print("H2O: ");
  lcd.setCursor(3,5);
  lcd.print(distance);  //Variable distance ausgeben
//________________________________________________________________

  //Serieller Screen
  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.println("C°");

  Serial.print("Lichtintensität: ");
  Serial.print(lux);
  Serial.println("Lux");

  Serial.print("Humidity: ");
  if (humid == 1){
    Serial.println("dry");
  }
  else {
    Serial.println("wet");
  }

  Serial.print("Wasserstand: ");
  Serial.print(distance);
  Serial.println("cm");
//_________________________________________________________________
//Relais Funktionen

//Bewässerung
if (humid == 1){
  digitalWrite(rWasser, LOW);   //Wasser ein
}
else {
  digitalWrite(rWasser, HIGH);  //Wasser aus
}

//Licht
if (lux <= 500){
  digitalWrite(rLicht, LOW);   //Lampe ein
}
else {
  digitalWrite(rLicht, HIGH);  //Licht aus
}

//Belüftung
if (temp >= 25){
  digitalWrite(rLuft, LOW);   //Lüfter ein
}
else {
  digitalWrite(rLuft, HIGH);  //Lüfter aus
}



  
  
  
  
  
  
  
  
  
  
}
