void Dai_Parti(int top, int senso) {// se voglio aprire in fuori 1  in dentro -1 chiudere 0
  if (bandierina_fault == true ) {
    delay(1000);
    Serial.println("--- FAULT parti--");
    return;
  }
  if ( fuoco == true ){
     Serial.println("fuoco ");
    return;
  }
  /*
  if ( Entra == false && bandiera_pulsanti == false){
     Serial.println("Entra");
    return;
  }
  */
  if ( bandierina_emergenza == true && non_aprire == true){
     Serial.println("bandierina_emergenza & non_aprire ");
    return;
  }
  if ( bandierina_emergenza == true && String(stato_Bea).substring(0, 2).toInt() == 12){
     Serial.println("bandierina_emergenza e 12 ");
    return;
  }
  if ( non_aprire == true ) {
     Serial.println("non_aprire ");
    return;
  } 
  if ( bandierina_emergenza == true){
    bandierina_emergenza_risolta = true;
     Serial.println("bandierina_emergenza ");
  }
  
  Serial.println("parti");
  inVia("222", 1);//******************************************************** occhio *************************************
  //digitalWrite(A3, LOW);
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  /*if ( abs(pos) < 100) {
    //md.setM1Speed(100 * motore * 1);
    digitalWrite(apri_serratura, HIGH);
    delay(500);
    //digitalWrite(apri_serratura, LOW);
    //delay(700);
    // - se ho il pin  stato_serratura digitalRead(A5) == ?
    int tempo_serratura = millis();

    }*/
  // da quiiiiiiiiiiiiiiiiii
  float delta = Crocera;
  int i = 0;
  direzione = 1;
  if (top < 0) {  // se volio aprire uso un top positivo
    direzione = -1; // direzione e top vanno insieme
    top = top * -1;
  }
  if (senso == 0) {
    if (pos > 0 ) {
      senso = 1;
    } else {
      senso = -1;
    }
  }
  _Senso = senso;
  Serial.println("parametri:");
  Serial.print("  >> direzione = "); Serial.println(direzione);
  Serial.print("  >> senso = "); Serial.println(senso);
  Controlla_Posizione(1);
  delta = Crocera;
  in_movimento = 1;
  for (i = 70; i < top; i = i + 2) {
    /*if ( i % 5 == 0 ) {
      ricevi(7);
      Controlla_Bea();
      if ( Bea_stop == true || Bea_reopen == true ) {
        Serial.println("bea reopen ");
        Stop(5, 110);
        return;
      }
    }*/
    md.setM2Speed(i * motore * direzione * senso);
    tensione = i;
    if ( Targhet(Crocera)) {
      Serial.println("raggiunto targhet ");
      break;
    }
    int consumo = fai_Media();
    if (direzione == -1) {
      consumo_max = consumo_max * 1.6;
    }
    if ( consumo > consumo_max ) {
      Serial.print("exit limit "); Serial.println(consumo);
      emergenza(2);
      Stop(5, 11);
      break;
    }
    if (V_M > delta * 0.65 && V_M < delta * 0.8) {
      delay(2 * inerzia);
    }
    if (V_M > delta * 0.8) {
      delay(6 * inerzia);
    }
    if ((abs(pos) >= pos_aperto && direzione == 1) || (abs(pos) < 0 && direzione == -1)) {
      Stop(1, 10);
      break;
    }
  }
  if (direzione == -1) {
    tutto_aperto = false;
  }
  //digitalWrite(apri_serratura, LOW);
}

//fine
