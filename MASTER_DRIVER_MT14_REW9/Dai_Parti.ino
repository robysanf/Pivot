void Dai_Parti(int top) {
  Serial.println("bea dddddddddddddddddddd ");
  if (non_aprire == true) {
    return;
  } Serial.println("bea aaaaaaaaaaaaaaaaaaaaaa ");
  inVia("222", 1);//******************************************************** occhio *************************************
  digitalWrite(4, HIGH);
  digitalWrite(A4,HIGH);
  if ( pos < 100) {
    //md.setM2Speed(100 * motore * 1);
    digitalWrite(apri_serratura, HIGH);
    delay(500);
    //digitalWrite(apri_serratura, LOW);
    //delay(700);
    // - se ho il pin  stato_serratura digitalRead(A5) == ?
    int tempo_serratura = millis();
    /* while(digitalRead(A5) == HIGH || (millis() - tempo_serratura) > 2000){Serial.println("while ");
       return;
      }*/
  }
  int i = 0;
  direzione = 1;
  if (top < 0) {
    direzione = -1;
    top = top * -1;
  }
  Controlla_Posizione();
  in_movimento = 1;
  for (i = 50; i < top; i = i + 1) {
    /*  if ( i%5 ==0 ){
        ricevi(7);
        Controlla_Bea();
       if( Bea_stop == true || Bea_reopen == true ){Serial.println("bea reopen ");
       return;
       }
      }*/
    md.setM2Speed(i * motore * direzione);
    tensione = i;
    if ( Targhet(Crocera)) {
      Serial.println("raggiunto targhet ");
      break;
    }
    int consumo = fai_Media();
    if ( consumo > consumo_max_crocera ) {
      Serial.print("exit limit "); Serial.println(consumo);
      // emergenza ? oppure sto fermo?
      Stop(5);
      break;
    }
    delay(3);
    Serial.print("MD_CURRENT = "); Serial.println(md.getM2CurrentMilliamps());
    Serial.print("Tensione accelera = "); Serial.println(i);
    if ((pos >= pos_aperto && direzione == 1) || (pos < 0 && direzione == -1)) {
      Stop(1);
      break;
    }
  }
  if (direzione == -1) {
    tutto_aperto = false;
  }
  digitalWrite(apri_serratura, LOW);
}
