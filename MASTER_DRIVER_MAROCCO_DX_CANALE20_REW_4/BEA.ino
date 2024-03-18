void Controlla_Bea() {
  // -- la variabile che dobbiamo processare è   stato_Bea
  // --  posizione 1     STOP     1 <> 2
  // --  posizione 2     REOPEN   1 <> 2
  // --  posizione 3     TEST     1 <> 2     VIENE GESTITO A PARTE QUINDI LO ESCLUDEREI DAL PROCESSO
  // --  posizione 4     COMANDO  1 - 2 - 3  VIENE GESTITO A PARTE QUINDI LO ESCLUDEREI DAL PROCESSO

  if (Disattiva_Bea == true){
    return;
  }

  int codice = String(stato_Bea).substring(0, 2).toInt();
  Serial.print("controlla Bea = "); Serial.println(codice);

  switch (codice) {
    
    case 11: // -- tutto funziona correttamente
    Serial.print("dentro switch = "); Serial.println(codice);
      // -- nessuna azione
    // -- se Bea_stop == true;
      non_aprire = false;
      if ( Bea_stop == true ) {
        Bea_stop = false;       // -- blocco la chiusura dopo 5 secondi
        Dai_Parti(top_max, 1);    // -- faccio finire di aprire la porta
      }
      if ( Bea_reopen == true ) {
        Bea_reopen = false;       // -- blocco la chiusura dopo 5 secondi
        Dai_Parti(top_max, 1);    // -- faccio finire di aprire la porta
      }

      break;
    case 21: // -- si è attivato lo stop in apertura
    Serial.println("dentro switch = 21"); 
      // -- possibili varianti a seconda della direzione delle porta
      Serial.print("dentro switch direzione = "); Serial.println(direzione);
      
      if ( direzione == 1 ) {              // -- se ero in apertura
        Stop(5,27);                           // -- si ferma
        conta = millis();                  // -- time out chiude
        Bea_stop = true;
        Bea_reopen = false;
      }

      break;
    case 22: // -- si è attivato il reopen ed anche lo stop
    Serial.println("dentro switch = 22"); 
      // -- pensiamoci...
      // -- possibili varianti a seconda della direzione delle porta
      if ( direzione == 0 ) {
        non_aprire = true;
      }

      Stop(5,26);
      // -- risolto apre
      // -- time out chiude
      break;
    case 12: // -- si è attivato il reopen in chiusura
     Serial.println("dentro switch = 12"); 
      // -- pensiamoci...
      // -- possibili varianti a seconda della direzione delle porta
      if ( direzione == -1  && pos > 0) {     // -- se sta chiudendo
        Stop(5,25);                   // -- si ferma
        Bea_reopen = true;        // -- e alza la bandierinaper la riapertura
      }
      if ( Entra == false ){
        return;
      }
      if ( direzione == 0 && digitalRead(6) == HIGH ){      // -- se sono chiuso   
       Serial.println("BEA ha detto entra");  
       Dai_Parti(top_max, 1);                              // -- FACCIO APRIRE in questo caso ENTRO  
      }
      break;
  }
}
