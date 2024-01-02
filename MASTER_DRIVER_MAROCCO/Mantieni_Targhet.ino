void Mantieni_Targhet(float targhet) {
  if (pos_vecchio == pos) {
    Serial.println("---- Stop ----");
    Serial.print(" consumo-------------------------"); Serial.println(fai_Media());
    Stop(1);
    return;
  }
  int dif_targhet = V_M - targhet;
  if (dif_targhet < 0) {
    dif_targhet = dif_targhet * -1;
  }
  if ((micros() - tempo_mantieni_targhet) < 40000 && (dif_targhet < 4 )) {
    //Serial.println("---- troppo presto ----");
    return;
  }
  if (V_M > targhet * 1.02) { // -- sono veloce devo rallentare
    tensione = tensione - 5;
    Serial.print("--- VM = "); Serial.print(V_M);
    Serial.print("  / tensione = "); Serial.print(tensione);
    Serial.print("  / pos = "); Serial.println(pos);
    md.setM2Speed(tensione * motore * direzione);
  }
  if (V_M < targhet * 0.98) { // -- sono lento devo accellerare
    tensione = tensione + 5;
    if (tensione > 600) {
      tensione = 600;
    }
    Serial.print("+++ VM = "); Serial.print(V_M);
    Serial.print("  / tensione = "); Serial.print(tensione);
    Serial.print("  / pos = "); Serial.println(pos);

    md.setM2Speed(tensione * motore * direzione);
  }
  pos_vecchio = pos;
  tempo_mantieni_targhet = micros();
}

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
