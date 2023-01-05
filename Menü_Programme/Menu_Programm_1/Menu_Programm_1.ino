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

  //Taster Pin Belegung
const int Hoch = 3;
const int Ok = 4;
const int Runter = 5;

  //Taster Status (Funktion+Sta)
int HochSta = 0;
int OkSta = 0;
int RunterSta = 0;

  //Menüvariablen
int Cover = true;       //Der Start Bildschirm quasie
int Haupt = false;      //Hauptmenü
int Overview = false;   //Das Parameter Übersichts Menü
int Settings = false;   //Das Parameter Übersichtsmenü
int Temp = false;       //Temperature Grenzen Menü
int TempUpper = false;
int TempLOWER = false
int Light = false;      //Light Grenzen Menü
int LightLOWER = false;
int Humid = false;      //Humidity Grenzen Menü
int HumidUPPER = false;
int HumidLOWER = false;
int Relais = false;     //Das Relais Menü
int Wasser = false;     //Relais Wasser
int Lampe = false;      //Relais Licht
int Luft = false;       //Relais Luft
int i = 1;              //Laufvariable für die Menüauswahl

int 
int Lower = false;

  //LCD Ausgabevariablen für direkte Positionierung
char a[20];             //Erste Zeile
char b[20];             //Zweite Zeile
char c[20];             //Dritte Zeile
char d[20];             //Vierte Zeile

  //Taster Entprellung
unsigned long alteZeit = 0;
unsigned long entprellZeit = 250;

  //Variablen Zur Relais Schalt Einstellung
int ONrWasser = 50;
int OFFrWasser = 70;
int ONrLicht = 500;
int ONrLuft = 25;
int OFFrLuft = 15;

  //Display Clear Time
unsigned long ScreenTime = 0;
unsigned long TimeNow = 0;
int ClearTime = 5000;

//------------------------------------------------------------------

void setup() 
{
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

  //Für Menü
  lcd.begin(20,4);
  lcd.clear();
  pinMode(Hoch, INPUT);
  pinMode(Ok, INPUT);
  pinMode(Runter, INPUT);

  //Für Display Clear mit Millis
  ScreenTime = millis();
}
//------------------------------------------------------------------
//Subroutinen

//Funktion für Wert Ausgabe auf Overview Display
void Subroutine_Overview();       //In neuem Tab

//Funktion für die LCD Ausgabe
void lcd_Ausgabe (char*a, char*b, char*c, char*d)
{
  lcd.setCursor(0,0);
  lcd.print(a);
  lcd.setCursor(0,1);
  lcd.print(b);
  lcd.setCursor(0,2);
  lcd.print(c);
  lcd.setCursor(0,3);
  lcd.print(d);
}

//Funktion für die Menünavigation
int MenuAuswahl (int i)
{
  HochSta = digitalRead(Hoch);
  RunterSta = digitalRead(Runter);

  //Für Hoch navigieren
  if(HochSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    alteZeit = millis();
    i--;
  }
  
  //Für Runter navigieren
  if(RunterSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    alteZeit = millis();
    i++;
  }
  //Für Ok Taste
  OkSta = digitalRead(Ok);
  return i;
}


//------------------------------------------------------------------
void loop() 
{

//Menü: Cover
while(Cover == true)
{
  i = MenuAuswahl(i);       //i verhält sich nach der Menü Auswahl Funktion wird also je nach Taste größer oder kleiner
  //Menügröße
  if(i == 0) i = 1;
  if(i == 2) i = 1;

  if(i == 1)
  {
    lcd_Ausgabe ("Arduino-Horticulture","                   ","       > MENU       ","                    ");    //Ausgabe des Cover Bildschirms
  }
  //Sprung ins Hauptmenü
  if(i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    lcd.clear();      //Könnte man noch anpassen zu ein Array aufrufen das aus Leerzeichen besteht
    alteZeit = millis();
    Cover = false;
    Haupt = true;
  }
}

//-----------------------------------------------------------------
//Menü: Haupt
while(Haupt == true)
{
 i = MenuAuswahl(i);
 //Menügröße
 if(i == 0) i = 1;
 if(i == 5) i = 4;

 //Display Anzeige des Hauptmenüs
 if(i == 1)
 {
  lcd_Ausgabe ("> OVERVIEW          ","  SETTINGS          ","  RELAY-TEST        ","  BACK              ");
 }
 if(i == 2)
 {
  lcd_Ausgabe ("  OVERVIEW          ","> SETTINGS          ","  RELAY-TEST        ","  BACK              ");
 }
 if(i == 3)
 {
  lcd_Ausgabe ("  OVERVIEW          ","  SETTINGS          ","> RELAY-TEST        ","  BACK              ");
 }
 if(i == 4)
 {
  lcd_Ausgabe ("  OVERVIEW          ","  SETTINGS          ","  RELAY-TEST        ","> BACK              ");
 }

 //In die jeweiligen Menüs springen
 
 if(i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Overview" Menü
  {
    lcd.clear();
    alteZeit = millis();
    Haupt = false;
    Overview = true;
    i=1;
  }
 if(i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Settings" Menü
  {
    lcd.clear();
    alteZeit = millis();
    Haupt = false;
    Settings = true;
    i=1;
  }
 if(i == 3 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Relais" Menü
  {
    lcd.clear();
    alteZeit = millis();
    Haupt = false;
    Relais = true;
    i=1;
  }
 if(i == 4 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung zurück ins "Cover" Menü
  {
    lcd.clear();
    alteZeit = millis();
    Haupt = false;
    Cover = true;
    i=1;
  }
}

//------------------------------------------------------------------
//Menü: Overview
while(Overview == true)
{
 i = MenuAuswahl(i);
 //Menügröße
 if(i == 0) i = 1;
 if(i == 3) i = 2;

 //Display Anzeige des Overview Menüs
 if(i == 1)
 {
  OverviewAusgabe ();       //Subroutine OverviewAusgabe wird ausgegeben
 }
 
 if (i == 2)
 {
  lcd_Ausgabe ("                    ","                    ","                    ","             >BACK  ");
 }
 
 //Sprung ins Hauptmenü
 if(i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
 {
  lcd.clear();
  alteZeit = millis();
  Overview = false;
  Haupt = true;
  i = 1;
 }
 
} //Klammer While Overview

//------------------------------------------------------------------
//Menü: Settings
while(Settings == true)
{
  i = MenuAuswahl(i);
  //Menügröße
  if(i == 0) i = 1;
  if(i == 5) i = 4;

  //Display Anzeige des Settings Menü
  if(i == 1)
  {
    lcd_Ausgabe ("> HUMIDITY          ","  LIGHTING          ","  VENTILATION       ","  BACK              ");
  }
  if(i == 2)
  {
    lcd_Ausgabe ("  HUMIDITY          ","> LIGHTING          ","  VENTILATION       ","  BACK              ");
  }
  if(i == 3)
  {
    lcd_Ausgabe ("  HUMIDITY          ","  LIGHTING          ","> VENTILATION       ","  BACK              ");
  }
  if(i == 4)
  {
    lcd_Ausgabe ("  HUMIDITY          ","  LIGHTING          ","  VENTILATION       ","> BACK              ");
  }

  //In die jeweiligen Menüs springen
  if(i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Humid" Menü
    {
    lcd.clear();
    alteZeit = millis();
    Settings = false;
    Humid = true;
    i=1;
    }

  if(i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Light" Menü
    {
    lcd.clear();
    alteZeit = millis();
    Settings = false;
    Light = true;
    i=1;
    }

  if(i == 3 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Temp" Menü
    {
    lcd.clear();
    alteZeit = millis();
    Settings = false;
    Temp = true;
    i=1;
    }

  if(i == 4 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Haupt" Menü
    {
    lcd.clear();
    alteZeit = millis();
    Settings = false;
    Haupt = true;
    i=1;
    }
 
} //Klammer While Settings

//------------------------------------------------------------------
//Menü: Humid
while(Humid == true)
{
  i = MenuAuswahl (i);
  //Menügrößen
  if (i==0) i=1;
  if (i==4) i=3;
  
  // Displayanzeige des Humidity Menüs
  if (i==1){
    lcd_Ausgabe ("Settings Humidity:","> UPPER LIMIT:      ","  LOWER LIMIT:      ","  BACK              ");
  }
  if (i==2){
    lcd_Ausgabe ("Settings Humidity:","  UPPER LIMIT:      ","> LOWER LIMIT:      ","  BACK              ");
  }
  if (i==3){
    lcd_Ausgabe ("Settings Humidity:","  UPPER LIMIT:      ","  LOWER LIMIT:      ","> BACK              ");
  }
   
   // In die jeweiligen Menüs springen
  if (i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit) // In Menü: HumidUPPER zum Einstellen
  {
    lcd.clear();
    alteZeit = millis();
    Humid = false;
    HumidUPPER = true;
    i=1;
  }
  if (i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit) // In Menü: HumidLOWER zum Einstellen
  {
    lcd.clear();
    alteZeit = millis();
    Humid = false;
    HumidLOWER = true;
    i = 1;
  }
  if (i == 3 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit) // Back to Menu: Settings
  {
    lcd.clear();
    alteZeit = millis();
    Humid = false;
    Settings = true;
    i=1;
  }
} // Klammer While Humid
//------------------------------------------------------------------
//Menü: HumidUPPER
while (HumidUPPER == true)
{
  
  
}

//------------------------------------------------------------------
//Menü: Light
while(Light == true)
{
  i = MenuAuswahl(i);
  //Menügrößen
  if (i==0) i=1;
  if (i==4) i=3;
  
  // Displayanzeige des Lighting Menüs
  if (i==1){
    lcd_Ausgabe ("Settings Light:","> UPPER LIMIT:      ","  LOWER LIMIT:      ","  BACK              ");
  }
  if (i==2){
    lcd_Ausgabe ("Settings Light:","  UPPER LIMIT:      ","> LOWER LIMIT:      ","  BACK              ");
  }
  if (i==3){
    lcd_Ausgabe ("Settings Light:","  UPPER LIMIT:      ","  LOWER LIMIT:      ","> BACK              ");
  }
   
   // In die jeweiligen Menüs springen
  if (i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit) // Upper
  {
    lcd.clear();
    alteZeit = millis();
    Light = false;
    Upper = true;
    i=1;
  }
  if (i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit) // Lower
  {
    lcd.clear();
    alteZeit = millis();   
    Light = false;
    Lower = true;
    i = 1;
  }
  if (i == 3 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit) //Back
  {
    lcd.clear();
    alteZeit = millis();
    Light = false;
    Settings = true;
    i=1;
  }
} //Klammer While Light

//------------------------------------------------------------------
//Menü: Temp
while(Temp == true)
{
  i = MenuAuswahl(i);
  //Menügrößen
  if (i==0) i=1;
  if (i==4) i=3;
  
  // Displayanzeige des Temp Menüs
  if (i==1){
    lcd_Ausgabe ("Settings Temperatur:","> UPPER LIMIT:      ","  LOWER LIMIT:      ","  BACK              ");
  }
  if (i==2){
    lcd_Ausgabe ("Settings Temperatur:","  UPPER LIMIT:      ","> LOWER LIMIT:      ","  BACK              ");
  }
  if (i==3){
    lcd_Ausgabe ("Settings Temperatur:","  UPPER LIMIT:      ","  LOWER LIMIT:      ","> BACK              ");
  }
   
   // In die jeweiligen Menüs springen
  if (i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit) // Upper
  {
    lcd.clear();
    alteZeit = millis();
    Temp = false;
    Upper = true;
    i=1;
  }
  if (i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit) // Lower
  {
    lcd.clear();
    alteZeit = millis();
    Temp = false;
    Lower = true;
    i = 1;
  }
  if (i == 3 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit) // Back
  {
    lcd.clear();
    alteZeit = millis();
    Temp = false;
    Settings = true;
    i=1;
  }
} //Klammer While Temp
  
//------------------------------------------------------------------
//Menü: Upper
  
//------------------------------------------------------------------
//Menü: Lower

//------------------------------------------------------------------
//Menü: Relais
while(Relais == true)
{
  i = MenuAuswahl(i);
  //Menügröße
  if(i == 0) i = 1;
  if(i == 5) i = 4;

  //Display Anzeige des Relais Menüs
  if(i == 1)
  {
    lcd_Ausgabe("> R1 WATER-PUMP     ","  R2 LIGHTNING-LED  ","  R3 VENTILATION    ","  BACK              ");
  }
  if(i == 2)
  {
    lcd_Ausgabe("  R1 WATER-PUMP     ","> R2 LIGHTNING-LED  ","  R3 VENTILATION    ","  BACK              ");
  }
  if(i == 3)
  {
    lcd_Ausgabe("  R1 WATER-PUMP     ","  R2 LIGHTNING-LED  ","> R3 VENTILATION    ","  BACK              ");
  }
  if(i == 4)
  {
    lcd_Ausgabe("  R1 WATER-PUMP     ","  R2 LIGHTNING-LED  ","  R3 VENTILATION    ","> BACK              ");
  }

  //In die jeweiligen Menüs springen
  if(i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Wasser" Menü
    {
     lcd.clear();
     alteZeit = millis();
     Relais = false;
     Wasser = true;
     i=1;
    }
  if(i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Lampe" Menü
    {
     lcd.clear();
     alteZeit = millis();
     Relais = false;
     Lampe = true;
     i=1;
    }
  if(i == 3 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Luft" Menü
    {
     lcd.clear();
     alteZeit = millis();
     Relais = false;
     Luft = true;
     i=1;
    }
  if(i == 4 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    //Sprung ins "Humid" Menü
    {
     lcd.clear();
     alteZeit = millis();
     Relais = false;
     Haupt = true;
     i=1;
    }

} //Kalmmer while Relais

//------------------------------------------------------------------
//Untermenüs Für Relais Test.....
while(Wasser == true)
{
  i= MenuAuswahl(i);
  //Menügröße
  if(i == 0) i = 1;
  if(i == 4) i = 3;

  //Display Anzeige des Wasser Menüs
  if(i == 1)
  {
    lcd_Ausgabe("Water-Pump:","> ON","  OFF","  Back");
  }
  if(i == 2)
  {
    lcd_Ausgabe("Water-Pump:","  ON","> OFF","  Back");
  }
  if(i == 3)
  {
    lcd_Ausgabe("Water-Pump:","  ON","  OFF","> Back");
  }

  //Einschlatung der Relais
  if(i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    digitalWrite(rWasser, HIGH);
    alteZeit = millis();
  }
  if(i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    digitalWrite(rWasser, LOW);
    alteZeit = millis();
  }
  if(i == 3 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    lcd.clear();
    alteZeit = millis();
    Wasser = false;
    Relais = true;
    i=1;
  }
} //Klammer while Wasser

while(Lampe == true)
{
  i= MenuAuswahl(i);
  //Menügröße
  if(i == 0) i = 1;
  if(i == 4) i = 3;

  //Display Anzeige des Lampe Menüs
  if(i == 1)
  {
    lcd_Ausgabe("Lamp:","> ON","  OFF","  Back");
  }
  if(i == 2)
  {
    lcd_Ausgabe("Lamp:","  ON","> OFF","  Back");
  }
  if(i == 3)
  {
    lcd_Ausgabe("Lamp:","  ON","  OFF","> Back");
  }

  //Einschlatung der Relais
  if(i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    digitalWrite(rLicht, HIGH);
    alteZeit = millis();
  }
  if(i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    digitalWrite(rLicht, LOW);
    alteZeit = millis();
  }
  if(i == 3 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    lcd.clear();
    alteZeit = millis();
    Lampe = false;
    Relais = true;
    i=1;
  }
} //Klammer while Lampe

while(Luft == true)
{
  i= MenuAuswahl(i);
  //Menügröße
  if(i == 0) i = 1;
  if(i == 4) i = 3;

  //Display Anzeige des Luft Menüs
  if(i == 1)
  {
    lcd_Ausgabe("Ventilator:","> ON","  OFF","  Back");
  }
  if(i == 2)
  {
    lcd_Ausgabe("Ventilator:","  ON","> OFF","  Back");
  }
  if(i == 3)
  {
    lcd_Ausgabe("Ventilator:","  ON","  OFF","> Back");
  }

  //Einschlatung der Relais
  if(i == 1 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    digitalWrite(rLuft, HIGH);
    alteZeit = millis();
  }
  if(i == 2 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    digitalWrite(rLuft, LOW);
    alteZeit = millis();
  }
  if(i == 3 && OkSta == HIGH && (millis() - alteZeit) > entprellZeit)
  {
    lcd.clear();
    alteZeit = millis();
    Luft = false;
    Relais = true;
    i=1;
  }
} //Klammer while Luft


} //Loop Klammer

 

 
 

 
