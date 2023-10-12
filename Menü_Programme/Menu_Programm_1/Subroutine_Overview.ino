//Funktion für Wert Ausgabe auf Overview Display
void OverviewAusgabe ()  //() müssen vielleicht noch Übergabe Parameter
{
  //Sensoren Abfrage

  //Abfrage Lichtsensor       Variable = lux
  int lux = lightMeter.readLightLevel();

  //Abfrage Ultraschallsensor Variable = distance
  unsigned int distance = sonar.ping_cm();

  //Abfrage Temperatursensor  Variable = temp
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  
  //Humidity                  Variable = humid/prozent für Prozentanzeige
  int humid = analogRead(A0);                  //Feuchtigkeit in humid
  int prozent = map(humid,262,1023,100,0);     //Feuchtigkeit in Prozent ausgeben

  
  lcd.setCursor(0,0);   //Temperatur
  lcd.print("TMP: ");  //Temperatur ausgeben
  lcd.setCursor(5,0);
  lcd.print(temp);
  
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
  lcd.print("R1: ON ");

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
  lcd.print("R2: ON ");
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
  lcd.print("R3: ON ");
  }
  if (temp <= OFFrLuft){                                         //Grenze Lüfter OFF Variable: OFFrLuft
  digitalWrite(rLuft, LOW); //Lüfter aus
  lcd.setCursor(13,0);
  lcd.print("R3: OFF");
  }
  if (temp > OFFrLuft && temp < ONrLuft){                        //Für Bereich zwischen Grenzwerten
  digitalWrite(rLuft, LOW); //Lüfter aus
  lcd.setCursor(13,0);
  lcd.print("R3: OFF");
  }


  //Clearen der Messwerte um Überschreibungen zu verhindern bei großen Zahlen
  TimeNow = millis();
  if((TimeNow - ScreenTime) >= ClearTime)
  {
  //Hier muss irgendwas hin um die Überschreibung von Werten zu Verhindern!
  lcd.setCursor(5,0);
  lcd.print("       ");
  
  lcd.setCursor(5,1);
  lcd.print("       ");
  
  lcd.setCursor(5,2);
  lcd.print("       ");
  
  lcd.setCursor(5,3);
  lcd.print("       ");
  
  ScreenTime = TimeNow;
  }


  
} //Schlussklammer Overview Subroutine
