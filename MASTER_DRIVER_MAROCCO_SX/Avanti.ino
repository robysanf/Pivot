void avanti_3()  {
  if (digitalRead(3) == digitalRead(2)) {
    pos = pos + 1 * encoder;                         // -- decremento il pos
  }
  else {
    pos = pos - 1 * encoder;                         // -- incremento il pos
  }
}

void avanti_2()  {
  if (giro == cadenza) {
    giro = 0;
    long t = micros();                                     // -- fermo il tempo
     t_delta = t - T1;                                  // -- calcolo il tempo trascorso
    V_M = (imp_vel / t_delta);                             // -- calcolo la velocità
    T1 = t;                                                // -- salvo il tempo
  }
 giro++;
}

// -- SE micros()- t E' MAGGIORE DI 400000
void puntozero(){
  if( Crocera == Velocita_Bassa){
    md.setM1Speed(0);                    // -- AZZERO LA TENSIONE
    digitalWrite(4, LOW);                // -- disabilito il DRIVER
    digitalWrite(A4, LOW);
    digitalWrite(A3, HIGH);     // -- METTO IN CORTOCIRCUITO il motore
    tensione = 0;                       // -- azzero la tensione per il successivo  Stop(int Delay)
    Blocco_Anta = true;                  // -- alzo la bandierina per fare il ferma_WARD( int passo)al primo passaggio in loop o in CHECK_POS()
    Serial.print("blocco anta **********************");
  }
Serial.println("*************************************************************************");
  }
