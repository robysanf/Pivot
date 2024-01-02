void Dai_Parti(int top, int senso) {// se voglio aprire in fuori 1  in dentro -1 chiudere 0
  Serial.println("bea dddddddddddddddddddd ");
  if (non_aprire == true) {
    return;
  } Serial.println("bea aaaaaaaaaaaaaaaaaaaaaa ");
  //inVia("222", 1);******************************************************** occhio *************************************
  digitalWrite(A3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(A4, HIGH);
  /*if ( abs(pos) < 100) {
    //md.setM2Speed(100 * motore * 1);
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

  Controlla_Posizione();
  in_movimento = 1;
  for (i = 70; i < top; i = i + 2) {
    /*  if ( i%5 ==0 ){
        ricevi(7);
        Controlla_Bea();
       if( Bea_stop == true || Bea_reopen == true ){Serial.println("bea reopen ");
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
    if ( consumo > consumo_max ) {
      Serial.print("exit limit "); Serial.println(consumo);
      // emergenza ? oppure sto fermo?
      Stop(5);
      break;
    }
    if (V_M > delta * 0.5 && V_M < delta * 0.7) {
      delay(3 * inerzia);
    }
    if (V_M > delta * 0.7) {
      delay(10 * inerzia);
    }
    Serial.print("MD_CURRENT = "); Serial.println(md.getM2CurrentMilliamps());
    Serial.print("Tensione accelera = "); Serial.println(i);
    if ((abs(pos) >= pos_aperto && direzione == 1) || (abs(pos) < 0 && direzione == -1)) {
      Stop(1);
      break;
    }
  }
  if (direzione == -1) {
    tutto_aperto = false;
  }
  digitalWrite(apri_serratura, LOW);
}

//fine
