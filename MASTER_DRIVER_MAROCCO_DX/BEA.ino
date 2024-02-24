void Controlla_Bea() {
  // -- la variabile che dobbiamo processare è   stato_Bea
  // --  posizione 1     STOP     1 <> 2
  // --  posizione 2     REOPEN   1 <> 2
  // --  posizione 3     TEST     1 <> 2     VIENE GESTITO A PARTE QUINDI LO ESCLUDEREI DAL PROCESSO
  // --  posizione 4     COMANDO  1 - 2 - 3  VIENE GESTITO A PARTE QUINDI LO ESCLUDEREI DAL PROCESSO

  if (Disattiva_Bea == true)
    return;

  int codice = String(stato_Bea).substring(0, 2).toInt();
  //Serial.print("controlla Bea = "); Serial.println(codice);

  switch (codice) {
    case 11: // -- tutto funziona correttamente
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
      // -- possibili varianti a seconda della direzione delle porta
      if ( direzione == 1 ) {              // -- se ero in apertura
        Stop(5);                           // -- si ferma
        conta = millis();                  // -- time out chiude
        Bea_stop = true;
        Bea_reopen = false;
      }

      break;
    case 22: // -- si è attivato il reopen ed anche lo stop
      // -- pensiamoci...
      // -- possibili varianti a seconda della direzione delle porta
      if ( direzione == 0 ) {
        non_aprire = true;
      }

      Stop(5);
      // -- risolto apre
      // -- time out chiude
      break;
    case 12: // -- si è attivato il reopen in chiusura
      // -- pensiamoci...
      // -- possibili varianti a seconda della direzione delle porta
      if ( direzione == -1 ) {     // -- se sta chiudendo
        Stop(5);                   // -- si ferma
        Bea_reopen = true;        // -- e alza la bandierinaper la riapertura
      }
      break;
  }
}
void Controlla_Bea_2() {
  // -- la variabile che dobbiamo processare è   stato_Bea
  // --  posizione 1     STOP     1 <> 2
  // --  posizione 2     REOPEN   1 <> 2
  // --  posizione 3     TEST     1 <> 2     VIENE GESTITO A PARTE QUINDI LO ESCLUDEREI DAL PROCESSO
  // --  posizione 4     COMANDO  1 - 2 - 3  VIENE GESTITO A PARTE QUINDI LO ESCLUDEREI DAL PROCESSO

  if (Disattiva_Bea == true)
    return;

  int codice = String(stato_Bea).substring(0, 2).toInt();
  //Serial.print("controlla Bea = "); Serial.println(codice);

  switch (codice) {
    case 11: // -- tutto funziona correttamente
         // -- tutto il da farsi
    break;
    case 21: // -- si è attivato lo STOP
         // -- tutto il da farsi
    break;
    case 12: // -- si è attivato il REOPEN
         // -- tutto il da farsi
    break;
    case 22: // -- si è attivato il REOPEN e lo STOP
         // -- tutto il da farsi
    break;
  }
}
