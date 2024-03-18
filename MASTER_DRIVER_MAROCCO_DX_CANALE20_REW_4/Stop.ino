void Stop(int Delay,int chi) {
  Serial.print(" stop Crocera =  ");Serial.println(Crocera);
  Serial.print(" stop chiamato da =  ");Serial.println(chi);
  int instant_pos;
  for (int i = tensione; i > 50; i = i - 1) {
    if (i < 0 || i < 50) i = 0;
    md.setM2Speed(i * motore * direzione * _Senso);
    delay(2 + freno + Delay);
    if (V_M < 20 ) {
      instant_pos = pos;
      Serial.print("Anta Ferma i = ");Serial.println(i);
      Serial.print("pos = ");Serial.println(instant_pos);
      md.setM2Speed(0);
      break;
    }
    /*
      Serial.print("pos  in ferma ");
      Serial.print(i);
      Serial.print(" =  ");
      Serial.println(pos);
    */

    if ( Blocco_Anta  ) {
      instant_pos = pos;
      Serial.print("STOP Blocco_Anta attivo >> ");
      Serial.println(instant_pos);
      Blocco_Anta = false;
      break;
    }
  }
  //top = 0;
  Serial.println("STOP*******************");
  md.setM2Speed(0);
  tensione = 0;
  in_movimento = 0;
  direzione = 0;
  _Senso = 0;
  Crocera = 0;
  if (bandierina_Bea == true){
    Disattiva_Bea = false;
  }
  bandiera_pulsanti = false;
  for (int ic = 0; ic < 20; ic++) {
    corrente[ic] = 0;
  }
  // --  V_M = 0.00; sostituito con   if( (micros() - T1) < (1/(15*imp))*1000000*(cadenza*2))  nel loop
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  if (abs(pos) < pos_chiuso)  {
    inVia("111", 1); // ******************************************************** occhio *************************************
  }
}
