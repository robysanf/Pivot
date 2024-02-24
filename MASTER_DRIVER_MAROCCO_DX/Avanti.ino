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
    pos = 0;
    md.setM2Speed(0);                    // -- AZZERO LA TENSIONE
    digitalWrite(4, LOW);                // -- disabilito il DRIVER
    digitalWrite(5, LOW);
    //digitalWrite(A3, HIGH);     // -- METTO IN CORTOCIRCUITO il motore
    digitalWrite(6, HIGH);     // -- BLOCCO CON MAGNETE
    tensione = 0;                       // -- azzero la tensione per il successivo  Stop(int Delay)
    Blocco_Anta = true;                  // -- alzo la bandierina per fare il ferma_WARD( int passo)al primo passaggio in loop o in CHECK_POS()
    Serial.print("blocco anta **********************");
  }
Serial.println("*************************************************************************");
  }



void sensore_interno()  {//HLK-LD2410_99BC 90:20:0F:AA:99:BC
  Serial.println("sensore_interno ATTIVATO");
  if (in_movimento != 1 && Entra == false)  Esci = true;
}

void sensore_esterno()  {//HLK-LD2410_5A00 71:8A:D3:77:5A:00
  Serial.println("sensore_esterno ATTIVATO");
  if (in_movimento != 1 && Esci == false )  Entra = true;
}
