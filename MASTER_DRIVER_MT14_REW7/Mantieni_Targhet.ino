void Mantieni_Targhet(float targhet) {
  if (pos_vecchio == pos) {
    Serial.println("---- Stop ----");
    return;
  }
  if (V_M > targhet * 1.02) { // -- sono veloce devo rallentare
    tensione = tensione - 1;
    Serial.print("--- VM = "); Serial.print(V_M);
    Serial.print("  / tensione = "); Serial.print(tensione);
    Serial.print("  / pos = "); Serial.println(pos);
    md.setM2Speed(tensione * motore * direzione);
  }
  if (V_M < targhet * 0.98) { // -- sono lento devo accellerare
    tensione = tensione + 1;
    if (tensione > 600) {
      tensione = 600;
    }
    Serial.print("++++ VM = "); Serial.print(V_M);
    Serial.print("  / tensione = "); Serial.print(tensione);
    Serial.print("  / pos = "); Serial.println(pos);

    md.setM2Speed(tensione * motore * direzione);
  }
  pos_vecchio = pos;
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
