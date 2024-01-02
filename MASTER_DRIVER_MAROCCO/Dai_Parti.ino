void Dai_Parti(int top, int v) {
  vers=v;
  if (v==0 && pos > 0)
  { 
    vers=1;
  } 
  if(v==0 && pos <0)
   { 
    vers=-1;
   }
  Serial.println("bea dddddddddddddddddddd ");
  if (non_aprire == true) {
    return;
  } Serial.println("bea aaaaaaaaaaaaaaaaaaaaaa ");
  inVia("222", 1);//******************************************************** occhio *************************************
  digitalWrite(pinDisableDriver, HIGH);
  digitalWrite(pinReleMotore,HIGH);
  
  int i = 0;
  direzione = 1 ;
  if (top < 0) {////*************************************??????????????????????? verificare
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
    md.setM2Speed(i * motore * direzione * vers);
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
    delay(5);
    Serial.print("MD_CURRENT = "); Serial.println(md.getM2CurrentMilliamps());
    Serial.print("Tensione accelera = "); Serial.println(i);
    if ((abs(pos) >= pos_aperto && direzione == 1 * vers) || (abs(pos) < pos_chiuso && direzione == -1 * vers)) {
    Serial.print("Tension = "); Serial.println(i);
      Stop(1);
      break;
    }
  }
  if (direzione == -1 * vers) {
    tutto_aperto = false;
  }
  //digitalWrite(apri_serratura, LOW);
}
