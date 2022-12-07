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
int Overview = false;  //Das Parameter Übersichts Menü
int Settings = false;  //Das Parameter Übersichtsmenü
int Temp = false;
int Light = false;
int Humid = false;
int Relais = false;     //Das Relais Menü
int Wasser = false;
int Lampe = false;
int Luft = false;
int i = 1;              //Laufvariable für die Menüauswahl

  //LCD Ausgabevariablen für direkte Positionierung
char a[20];             //Erste Zeile
char b[20];             //Zweite Zeile
char c[20];             //Dritte Zeile
char d[20];             //Vierte Zeile

  //Taster Entprellung
unsigned long alteZeit = 0;
unsigned long entprellZeit = 250;



 

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
}
//------------------------------------------------------------------
//Subroutinen

//Funktion für Wert Ausgabe auf Overview Display
int OverviewAusgabe ()  //() müssen vielleicht noch Übergabe Parameter
{
  lcd.setCursor(0,0);   //Temperatur
  lcd.print("TMP: " + String(sensors.getTempCByIndex(0)));  //Temperatur ausgeben
  
  lcd.setCursor(0,1);   //Lichtintensität
  lcd.print("LGT: ");
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

  //Für die Relais
  if (prozent <= ONrWasser){                                     //Grenze Wasser ON Variable: ONrWasser
  digitalWrite(rWasser, HIGH);   //Wasser ein
  
  lcd.setCursor(13,2);
  lcd.print("R1: ON");

  lcd.setCursor(13,3);
  lcd.print("> Back");
  }
  if (prozent >= OFFrWasser){                                    //Grenze Wasser OFF Variable: OFFrWasser
  digitalWrite(rWasser, LOW);  //Wasser aus

  lcd.setCursor(13,2);
  lcd.print("R1: OFF");
  }

  //Licht
  if (lux <= ONrLicht){                                          //Grenze Licht ON Variable: ONrLicht
  digitalWrite(rLicht, HIGH);   //Lampe ein
  lcd.setCursor(13,1);
  lcd.print("R2: ON");
  }
  else{
  digitalWrite(rLicht, LOW);  //Licht aus
  lcd.setCursor(13,1);
  lcd.print("R2: OFF"); 
  }

  //Belüftung
  if (temp >= ONrLuft){                                          //Grenze Lüfter ON Variable: ONrLuft
  digitalWrite(rLuft, HIGH);   //Lüfter ein 
  lcd.setCursor(13,0);
  lcd.print("R3: ON");
  }
  if (temp <= OFFrLuft){                                         //Grenze Lüfter OFF Variable: OFFrLuft
  digitalWrite(rLuft, LOW); //Lüfter aus
  lcd.setCursor(13,0);
  lcd.print("R3: OFF");
  }

} //Schlussklammer Overview Subroutine


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
//Sensoren Abfrage

  //Abfrage Lichtsensor       Variable = lux
  int lux = lightMeter.readLightLevel();

  //Abfrage Ultraschallsensor Variable = distance
  unsigned int distance = sonar.ping_cm();

  //Abfrage Temperatursensor  Variable = temp
  sensors.requestTemperatures();
  signed int temp = sensors.getTempCByIndex(0);
  
  //Humidity                  Variable = humid/prozent für Prozentanzeige
  int humid = analogRead(A0);                  //Feuchtigkeit in humid
  int prozent = map(humid,262,1023,100,0);     //Feuchtigkeit in Prozent ausgeben



//------------------------------------------------------------------
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
    Overview = true;
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
  
 }
 
} //Klammer While Schleife



} //Loop Klammer

 

 
 

 
