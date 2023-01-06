// Menü zum Einstellen der Grenzwerte mit Hilfe des EEPROM

void UpperLimitHumid ()
{ 
  while (UpperHumid == true )  
    {
    if (HochSta == HIGH && (millis() - alteZeit) > entprellZeit)  // Limit hoch
    {
      lcd.setCursor (16,1);
      lcd.print ("    ");
      x = (x + 1);
      ONrWasser = x;
      lcd.setCursor (16,1);
      lcd.print (ONrWasser);
    }
    if (RunterSta == HIGH && (millis() - alteZeit) > entprellZeit) // Limit runter
    {
      lcd.setCursor (16,1);
      lcd.print ("    ");
      x = (x - 1);
      ONrWasser = x;
      lcd.setCursor (16,2);
      lcd.print (ONrWasser);
    }
    if (x > 100)  //Grenzwerte
    {
      x = 100;
    }
    if (x < 0)
    {
      x = 0;
    }
    if (OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    // EEPROM Ausgabe und Beenden des Einstellmenü
    {
                                  
      UpperHumid = false;
      Humid = true;
    }
    
    } // Klammer while
} // Klammer Void
