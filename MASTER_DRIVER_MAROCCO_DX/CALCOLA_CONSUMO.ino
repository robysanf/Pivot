void Calcola_Consumo(int targhet)  { 
  int i = 0;
  direzione = -1;
  int assorbimento_attuale = 0;
  int assorbimento_max = 0;
  int assorbimento_1 = 0;
  int assorbimento_2 = 0;
  boolean fatto = false;
  boolean fatto2 = false;
  digitalWrite(A3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(A4, HIGH);
  for (i = 50; i < top_max; i = i + 1) {
    /*if ( i%5 ==0 ){
       ricevi(7);
       Controlla_Bea();
      if( Bea_stop == true || Bea_reopen == true ){Serial.println("bea reopen ");
      return;
      }
      }*/
    md.setM1Speed(i * motore * direzione);
    tensione = i;
    if ( Targhet(Velocita_Bassa)) {
      Serial.println("raggiunto targhet ");
      Serial.print("velocita = "); Serial.println(V_M);
      break;
    }
    int consumo = fai_Media();
    if ( consumo > consumo_max ) {
      Serial.print("exit limit "); Serial.println(consumo);
      Stop(5);
      break;
    }
    delay(2);
    //Serial.print("MD_CURRENT = "); Serial.println(consumo);
    //Serial.print("Tensione accelera = "); Serial.println(i);
    if (pos < pos_2 && direzione == -1) {
      Stop(5);
      break;
    }
  }
  int tempo_11 = 0;
  while (tempo_11 < 15000) {
    if (pos < pos_2 && direzione == -1) {
      Stop(5);
      break;
    }
    delay(1);
    tempo_11 ++;
  }
  delay(3000);
  // -- ****************************************************************************************************************
  //verso = 1;   // -- apro avel bassa
  int vel[4];
  vel[1] = Velocita_Bassa;
  vel[2] = Velocita_Media;
  vel[3] = Velocita_Alta;
  for (int u = 1; u <= 3; u++) {
    if (targhet > 0 && targhet <= 3){
      u = targhet; 
    }
      digitalWrite(A3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(A4, HIGH);
    assorbimento_1 = 0;
    assorbimento_max = 0;
    direzione = 1;
    for (i = 50; i < top_max; i = i + 1) {
      md.setM1Speed(i * motore * direzione);
      tensione = i;
      if ( Targhet(vel[u])) {
        Serial.println("raggiunto targhet 2 ");
        Serial.print("velocita = "); Serial.print(V_M);
        Serial.print("    /   tensione = "); Serial.println(tensione);
        fatto = true;
        break;
      }
      int consumo = fai_Media();
      if ( consumo > consumo_max ) {
        Serial.print("exit limit "); Serial.println(consumo);
        // devo aumemtare manualmente consumo max
        Stop(5);
        break;
      }
      delay(2);
      //Serial.print("MD_CURRENT = "); Serial.println(consumo);
      //Serial.print("Tensione accelera = "); Serial.println(i);
      //Serial.print("VM = "); Serial.println(V_M);
      //Serial.print("pos = "); Serial.println(pos);
      //Serial.print("t_delta = "); Serial.println(t_delta);
      if (pos > pos_5 && direzione == 1) {
        Stop(1);
        break;
      }
    }
    int contatore = 0;
    while ( contatore < 250 || fatto == true) {
      delay(150);
      fatto = false;
      Mantieni_Targhet(vel[u]);
      assorbimento_attuale = fai_Media();
      assorbimento_max = (assorbimento_attuale >= assorbimento_max ) ? assorbimento_attuale : assorbimento_max;
      assorbimento_1 += assorbimento_attuale;
      contatore ++;
      if (pos > pos_5 && direzione == 1) {
        Serial.println("exit stop ");
        Stop(5);
        fatto2 = true;
        break;
      }
      if ( assorbimento_attuale > consumo_max ) {
        Serial.print("exit limit "); Serial.println(assorbimento_attuale);
        Stop(5);
        fatto2 = true;
        break;
      }
    }
    if (fatto2 == false) {
      Serial.println("  fuori tempo  ");
      Stop(5);
    }
    if (fatto2 == true) {
      assorbimento_1 = assorbimento_1 / contatore;
      Serial.print("consumo_" + String(u) + " = "); Serial.println(assorbimento_1);
      Serial.print("consumo_" + String(u) + "_max = "); Serial.println(assorbimento_max);
      fatto2 = false;
    }
    // -- ****************************************************************************************************************
    delay(3000);
    //verso = -1;   // -- chiudo avel bassa
    assorbimento_2 = 0;
    direzione = -1;
    digitalWrite(A3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(A4, HIGH);
    for (i = 50; i < top_max; i = i + 1) {
      md.setM1Speed(i * motore * direzione);
      tensione = i;
      if ( Targhet(vel[u])) {
        Serial.println("raggiunto targhet 3");
        fatto = true;
        break;
      }
      int consumo = fai_Media();
      if ( consumo > consumo_max ) {
        Serial.print("exit limit "); Serial.println(consumo);
        // devo aumemtare manualmente consumo max
        Stop(5);
        break;
      }
      delay(2);
      //Serial.print("MD_CURRENT = "); Serial.println(consumo);
      //Serial.print("Tensione accelera = "); Serial.println(i);
      if (pos < 0 && direzione == -1) {
        Stop(1);
        break;
      }
    }
    contatore = 0;
    while ( contatore < 250 || fatto == true) {
      delay(150);
      fatto = false;
      Mantieni_Targhet(vel[u]);
      assorbimento_attuale = fai_Media();
      assorbimento_max = (assorbimento_attuale >= assorbimento_max ) ? assorbimento_attuale : assorbimento_max;
      assorbimento_2 += assorbimento_attuale;
      contatore ++;
      if (pos < pos_2 && direzione == -1) {
        Stop(5);
        fatto2 = true;
        break;
      }
      if ( assorbimento_attuale > consumo_max ) {
        Serial.print("exit limit "); Serial.println(assorbimento_attuale);
        Stop(5);
        fatto2 = true;
        break;
      }
    }
    if (fatto2 == false) {
      Serial.println("  fuori tempo  ");
      Stop(5);
    }
    if (fatto2 == true) {
      assorbimento_2 = assorbimento_2 / contatore;
      Serial.print("consumo_vel" + String(u) + " = "); Serial.println(assorbimento_2);
      Serial.print("consumo_" + String(u) + "_max = "); Serial.println(assorbimento_max);
      delay(2000);
      fatto2 = false;
      if (u == 1) {
        consumo_Bassa = (assorbimento_2 + assorbimento_1) / 2 * 120 / 100;
        consumo_Bassa_max = assorbimento_max * 120 / 100;
        Serial.print("consumo_Bassa = "); Serial.println(consumo_Bassa);
        Serial.print("consumo_Bassa_max = "); Serial.println(consumo_Bassa_max);
      }
      if (u == 2) {
        consumo_Media = (assorbimento_2 + assorbimento_1) / 2 * 120 / 100;
        consumo_Media_max = assorbimento_max * 120 / 100;
        Serial.print("consumo_Media = "); Serial.println(consumo_Media);
        Serial.print("consumo_Media_max = "); Serial.println(consumo_Media_max);
      }
      if (u == 3) {
        consumo_Alta = (assorbimento_2 + assorbimento_1) / 2 * 120 / 100;
        consumo_Alta_max = assorbimento_max * 120 / 100;
        Serial.print("consumo_Alta = "); Serial.println(consumo_Alta);
        Serial.print("consumo_Alta_max = "); Serial.println(consumo_Alta_max);
      }
    }
    delay(3000);
     if (targhet > 0 && targhet <= 3){
      break;
    }
  }
  Serial.println("fine = Calola Consumo ");
  digitalWrite(4, LOW);
  digitalWrite(A4, LOW);
}
