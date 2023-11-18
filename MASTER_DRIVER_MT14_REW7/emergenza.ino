void emergenza(int direzione_sblocco) {
  digitalWrite(4, HIGH);
  int pos_terghet = pos + (150 * imp * direzione_sblocco);
  for (int i = 50; i < top_max; i = i + 1) {
    md.setM2Speed(i * motore * direzione_sblocco);
    tensione = i;
    if ( Targhet(Velocita_Media)) {
      break;
    }
    if ( pos > pos_aperto || pos < 0 ) {
      Stop(1);
      return;
    }
    delay(2);
  }
  int conta_t = 0;
  while ( conta_t < 3000) {
    if ( pos > pos_aperto || pos < 0) {
      Stop(1);
      return;
    }
    if ( pos > pos_terghet && direzione_sblocco == 1) {
      Stop(1);
      //Serial.println("liberato da emergenza in chiusura ");
      return;
    }
    if ( pos < pos_terghet && direzione_sblocco == -1) {
      Stop(1);
      //Serial.println("liberato da emergenza in apertura ");
      return;
    }
  }
}



//todo
