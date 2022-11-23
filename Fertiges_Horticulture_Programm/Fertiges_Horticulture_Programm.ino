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

  //Display
LiquidCrystal_I2C lcd(0x27,20,4); //LCD Display definieren

  //Relais
const int rWasser = 8;  //Relais 1
const int rLicht = 9;   //Relais 2
const int rLuft = 10;   //Relais 3
long myTimer = 0;
long myTimeout = 10000;

void setup (){

  Serial.begin(9600);
  Wire.begin();             //I2C beginnt
  lightMeter.begin();       //Lichtsensor beginnt
  sensors.begin();          //Temperatursensor beginnt
  lcd.init();               //LCD starten
  lcd.backlight();          //LCD Hintergrundbeleuchtung starten
  
  //Feuchtigkeitssensor
  pinMode (7, INPUT);       //D7 als digitaler Input
  pinMode (A0, INPUT);      //A0 als analoger Input

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
  sensors.requestTemperatures();
  signed int temp = sensors.getTempCByIndex(0);
  
  //Humidity                  Variable = humid / prozent für Prozentanzeige
  int humid = analogRead(A0);                  //Feuchtigkeit in humid
  int prozent = map(humid,262,1023,100,0);    //Feuchtigkeit in Prozent ausgeben

//Ausgabegeräte
//______________________________________________________________
  
  //LCD Display
  lcd.setCursor(0,0);   //Temperatur
  lcd.print("TMP: " + String(sensors.getTempCByIndex(0)));  //Temperatur ausgeben
  
  lcd.setCursor(0,1);   //Lichtintensität
  lcd.print("LUX: ");
  lcd.setCursor(5,1);
  lcd.print(lux);       //Variable lux ausgeben

  lcd.setCursor(0,2);   //Humitity
  lcd.print("HUM: ");
  lcd.setCursor(5,2);
  lcd.print(prozent);   //Humidity in Prozent ausgeben


  lcd.setCursor(0,3);   //Wasserstand
  lcd.print("H2O: ");
  lcd.setCursor(5,3);
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
  Serial.print(prozent);
  Serial.println("%");

  Serial.print("Wasserstand: ");
  Serial.print(distance);
  Serial.println("cm");

  Serial.println("--------------------------------");
//_________________________________________________________________
//Relais Funktionen

//Bewässerung
if (prozent <= 50){
  digitalWrite(rWasser, HIGH);   //Wasser ein
  
  lcd.setCursor(12,2);
  lcd.print("R1: ON");
}
else {
  digitalWrite(rWasser, LOW);  //Wasser aus

  lcd.setCursor(12,2);
  lcd.print("R1: OFF");
}

//Licht
if (lux <= 500){
  digitalWrite(rLicht, HIGH);   //Lampe ein

  lcd.setCursor(12,1);
  lcd.print("R2: ON");
}
else {
  digitalWrite(rLicht, LOW);  //Licht aus

  lcd.setCursor(12,1);
  lcd.print("R2: OFF");
}
//Belüftung
if (millis() > myTimeout + myTimer && temp >=25){
  digitalWrite(rLuft, HIGH);   //Lüfter ein 
  lcd.setCursor(12,0);
  lcd.print("R3: ON");
}
else {
  digitalWrite(rLuft, LOW); //Lüfter blibt an
  lcd.setCursor(12,0);
  lcd.print("R3: OFF");
}
/* Belüftung
if (temp >= 25){
  digitalWrite(rLuft, HIGH);   //Lüfter ein 
  lcd.setCursor(12,0);
  lcd.print("R3: ON");
}

else{
  digitalWrite(rLuft, LOW); //Lüfter blibt an
  lcd.setCursor(12,0);
  lcd.print("R3: OFF");
}
*/
//Pause für Sichtbarkeit
delay(2500);
lcd.clear();


  
  
  
  
  
  
  
  
  
  
}
