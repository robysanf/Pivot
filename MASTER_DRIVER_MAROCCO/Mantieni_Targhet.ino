void Mantieni_Targhet(float targhet) {
  if (pos_vecchio == pos) {
    Serial.println("---- Stop ----");
    Stop(1);
    return;
  }
  if ( millis() - tempo_controlla_velocita < 75 ) {
    Serial.println("troppo presto");
    return;
  }
  tempo_controlla_velocita = millis();

  int dif_targhet = V_M - targhet;
  if (dif_targhet < 0) {
    dif_targhet = dif_targhet * -1;
  }
  if ((micros() - tempo_mantieni_targhet) < 40000 && (dif_targhet < 4 )) {
    //Serial.println("---- troppo presto ----");
    return;
  }
if (V_M > (targhet * 1.01)) {
    if (V_M > (targhet * 1.02)) {
      if (V_M > (targhet * 1.03)) {
        Serial.print("   ------   ");
        tensione = tensione - 10;
        md.setM2Speed(tensione * motore * direzione * _Senso);
        return;
      }
      Serial.print("   ----   ");
      tensione = tensione - 8;
      md.setM2Speed(tensione * motore * direzione * _Senso);
      return;
    }
    Serial.print("   --   ");
    tensione = tensione - 5;
    md.setM2Speed(tensione * motore * direzione * _Senso);
    return;
  }
  if ( V_M < (targhet * 0.99)) {
    if (V_M < (targhet * 0.98)) {
      if (V_M < (targhet * 0.97)) {
        Serial.print("   ++++++  ");
        tensione = tensione + 15;
        if (tensione > 600) {
          tensione = 600;
        }
        md.setM2Speed(tensione * motore * direzione * _Senso);
        return;
      }
      Serial.print("   ++++  ");
      tensione = tensione + 10;
      if (tensione > 600) {
        tensione = 600;
      }
      md.setM2Speed(tensione * motore * direzione * _Senso);
      return;
    }
    Serial.print("   ++  ");
    tensione = tensione + 5;
    if (tensione > 600) {
      tensione = 600;
    }
    md.setM2Speed(tensione * motore * direzione * _Senso);
    return;
  }
  pos_vecchio = pos;
  tempo_mantieni_targhet = micros();
}





  






/*
  if (V_M > targhet * 1.02) { // -- sono veloce devo rallentare
    tensione = tensione - 1;
    Serial.print("--- VM = "); Serial.print(V_M);
    Serial.print("  / tensione = "); Serial.print(tensione);
    Serial.print("  / pos = "); Serial.println(pos);
    md.setM2Speed(tensione * motore * direzione * _Senso);
  }
  if (V_M < targhet * 0.98) { // -- sono lento devo accellerare
    tensione = tensione + 1;
    if (tensione > 600) {
      tensione = 600;
    }
    Serial.print("+++ VM = "); Serial.print(V_M);
    Serial.print("  / tensione = "); Serial.print(tensione);
    Serial.print("  / pos = "); Serial.println(pos);

    md.setM2Speed(tensione * motore * direzione * _Senso);
  }
 */






int fai_Media() {
  conta_corrente = conta_corrente + 1;
  if (conta_corrente > 19) {
    conta_corrente = 0;
  }
  corrente[conta_corrente] = md.getM2CurrentMilliamps();
  int tot = 0;
  for (int i = 0; i < 20; i++) {
    tot = tot + corrente[i];
  }
  return tot / 20;
}
