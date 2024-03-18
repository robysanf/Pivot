void settaggio() {
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  int consumo = fai_Media();
  float delta = 50.0;
  set_reset = false;
  Crocera = 50.0;
  // devo vedere se sono dentro o fuori dalle calamite
  Serial.print("digitalRead(A5) = "); Serial.println(digitalRead(A5));
  delay(1500);
  if (digitalRead(A5) == HIGH) { 
    
    // vuol dire che sono fuori dalle calamite
    // quindi mi muovo verso, in questo caso cioè l'anta di destra, fuori a bassa velocità 50mm/s

    for ( int i = 70; i < 1200; i = i + 2) {
      md.setM2Speed(i * motore  * 1);
      tensione = i;
      if ( Targhet(50)) {
        Serial.println("raggiunto targhet set");
        break;
      }
      consumo = fai_Media();
      if ( consumo > consumo_max ) {
        Serial.print("exit limit settagio"); Serial.println(consumo);
        // emergenza ? oppure sto fermo?
        Stop(5, 51);
        bandierina_fault = true;
        break;
      }
      if (V_M > delta * 0.65 && V_M < delta * 0.8) {
        delay(2 * inerzia);
      }
      if (V_M > delta * 0.8) {
        delay(6 * inerzia);
      }
      //Serial.print("MD_CURRENT = "); Serial.println(md.getM2CurrentMilliamps());
      //Serial.print("Tensione accelera = "); Serial.println(i);
      if (digitalRead(A5) == LOW) {
        Serial.print("digitalRead(A5) 2 = "); Serial.println(digitalRead(A5));
        Stop(5, 52);
        break;
      }
    }
    while (digitalRead(A5) == HIGH) {
      if ( consumo > consumo_max ) {
        Serial.print("exit limit settagio 2"); Serial.println(consumo);
        Stop(5, 53);
        bandierina_fault = true;
        break;
      }
      delay(50);
    }
    Stop(25, 54);
    delay(1500);
  }
  if (digitalRead(A5) == LOW) {
    Serial.println("ENTRO QUI ");
    set_reset = true;
    digitalWrite(6, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    for ( int i = 70; i < 1200; i = i + 2) {
      Serial.println("ENTRO QUI 2 ");
      md.setM2Speed(i * motore  * -1);
      tensione = i;
      if ( Targhet(50)) {
        Serial.println("raggiunto targhet set 2");
        break;
      }
      consumo = fai_Media();
      if ( consumo > consumo_max ) {
        Serial.print("exit limit settaggio 3"); Serial.println(consumo);
        Stop(5, 55);
        bandierina_fault = true;
        return;
      }
      if (V_M > delta * 0.65 && V_M < delta * 0.8) {
        delay(2 * inerzia);
      }
      if (V_M > delta * 0.8) {
        delay(6 * inerzia);
      }
      //Serial.print("MD_CURRENT = "); Serial.println(md.getM2CurrentMilliamps());
      //Serial.print("Tensione accelera = "); Serial.println(i);
      /*if (digitalRead(A5) == LOW) {
        Stop(5, 56);
        break;
        }*/
    }
    int conta_tempo = 0;
    while (va_bene == false && conta_tempo < 2000 ) {
      Serial.println("inloppato = "); Serial.println(conta_tempo);
      if ( consumo > consumo_max ) {
        Serial.print("exit limit settaggio 4"); Serial.println(consumo);
        Stop(25, 57);
        bandierina_fault = true;
        return;
      }
      conta_tempo ++ ;
      delay(30);
    }
    if ( conta_tempo >= 2000) {
      bandierina_fault = true;
      return;
    }
    delay(8000);
    Stop(25, 60);
    set_reset = false;
    va_bene = false;
    delay(2000);
    Dai_Parti( -top_max, 0);


  }

}
