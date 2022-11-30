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
//Definitionen für die Menüfunktion

  //Taster
const int Hoch = 3;
const int Ok = 4;
const int Runter = 5;

  //Auslese Variablen für Taster
int UP = 0;
int SELECT = 0;
int DOWN = 0;

 

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

  //Zum Start einmal Display clearen
  lcd.clear();

//------------------------------------------------------------------
//Der Menüablauf
startmenu();              //Startmenu anzeigen
  if (SELECT == HIGH)
  {
    displayclear();
    hauptmenu();
  }
  
}

//------------------------------------------------------------------
void loop() {
  
  //Taster Prüfen durchgängig
  UP = digitalRead(T1);     //Zustand von T1 wird in UP gespeichert
  SELECT = digitalRead(T2); //Zusatnd von T2 wird in SELECT gespeichert
  DOWN = digitalRead(T3);   //Zustand von T3 wird in DOWN gespeichert
  
 


}

//------------------------------------------------------------------
//Startmenü
void startmenu(){
  lcd.setCursor (0,0);
  lcd.print ("Arduino-Horticulture");
  lcd.setCursor (0,2);
  lcd.print (".......> Menu.......");
  lcd.setCursor (0,3);
  lcd.print ("BY HEINRICH AND NILS");
    }
void hauptmenu(){
  lcd.setCursor (0,0);
  lcd.print ("> OVERVIEW..........");
  lcd.setCursor (0,1);
  lcd.print ("> SETTINGS..........");
  lcd.setCursor (0,2);
  lcd.print ("> RELAY TEST........");
  lcd.setCursor (0,3);
  lcd.print ("> BACK..............");
}
 
 

 
