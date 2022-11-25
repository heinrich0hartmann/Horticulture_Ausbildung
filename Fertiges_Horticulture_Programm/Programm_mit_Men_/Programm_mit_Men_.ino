// Dieses ist der Code für das Horticulture Programm mit Auswahlmenü

//------------------------------------------------------------------
//Bibliotheken
#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NewPing.h>
#include <AS_BH1750.h>

//------------------------------------------------------------------
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

//------------------------------------------------------------------

void setup() {
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

//------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:

}
