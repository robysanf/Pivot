void emergenza(int direzione_sblocco) {
  Serial.println("emergenza ----- ");
  //digitalWrite(A3, LOW);
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  int pos_terghet = abs(pos) + (150 * imp * direzione_sblocco );
  for (int i = 50; i < top_max; i = i + 1) {
    md.setM2Speed(i * motore * direzione_sblocco);
    tensione = i;
    if ( Targhet(Velocita_Media)) {
      break;
    }
    if ( abs(pos) > pos_aperto ) {
      Stop(1);
      return;
    }
    delay(2);
  }
  int conta_t = 0;
  while ( conta_t < 4000) {
    if ( abs(pos) > pos_aperto) {
      Stop(1);
      return;
    }
    if ( abs(pos) > pos_terghet && direzione_sblocco == 1) {
      Serial.println("liberato da emergenza in chiusura ");
      break;
    }
    if ( abs(pos) < pos_terghet && direzione_sblocco == -1) {
      Serial.println("liberato da emergenza in apertura ");
      break;
    }
    delay(1);
    conta_t++;
    Serial.println(conta_t);
  }
  Stop(1);
}
//todo
