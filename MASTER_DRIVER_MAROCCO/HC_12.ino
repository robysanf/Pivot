void  inVia(String msg, int ripetizioni ) {
  tempo_invia = micros();
  char list[4];
  msg.toCharArray(list, 4);
  Serial.print("Invio : "); Serial.println(msg);  // -- STAMPO COSA VOGLIO INVIARE
  Serial1.write(list);                            // -- INVIO IL MESSAGGIO
  if ( ripetizioni > 0){                          // -- alzo una bandierina che vado a verificare nel loop
    ripeti_comando = true;
    comando = msg;
  }
  Serial.print("tempo_invia : "); Serial.println( micros() - tempo_invia);
}

void  ricevi(int chi) {
  //Serial.print(" inizio ricevi "); Serial.println(chi);
  //Serial.print(" tempo_ricevi  = "); Serial.println(String(millis() - tempo_ricevi));
  if ( millis() - tempo_ricevi > 120) {
    tempo_ricevi = millis();
    char myBuffer[5];
    if ( Serial1.available()) {
      tempo_cane = millis(); 
      long oldt = micros();  // -- tempo per la ricezione
      ci_sei = true;
      Serial.print(" POS = ");Serial.println(pos);
      Serial.print(" striga ricevuta = ");
      int i = 0;
      boolean ricezione_completata = false;
      while (Serial1.available()) { 
        myBuffer[i] = Serial1.read();
        i++;
        if (i == 4) {
          myBuffer[i] = '\0';
          Serial1.end();
          Serial1.begin(9600);
          ricezione_completata = true;
          break;
        }
      }
      if (ricezione_completata) {
        stato_Bea = String(myBuffer).substring(0,4).toInt();   // -- QUESTO E' LA VARIABILE CHE DOBBIAMO PROCESSARE IN "CHE_FACCIO" *************************
        Serial.println("ffstato_Beaere = "); Serial.println(stato_Bea);
        ricezione_completata = false;  
      }
      Serial.println(myBuffer);
      Serial.print(" tempo fine ricezione = "); Serial.println(String(micros() - oldt));
      Serial.print(" bea stop = "); Serial.println(Bea_stop);
      Serial.print(" bea reop = "); Serial.println(Bea_reopen);
      Serial.print(" conta = "); Serial.println(conta);
    }
  }
}

void cambia_canale(String ch){
     digitalWrite(HC12, LOW);
     delay(150);
      String s="AT+C"+ch;
      char lis[255];
      s.toCharArray(lis,255);
     Serial1.write(lis);
     delay(150);
     digitalWrite(HC12, HIGH);
  }
