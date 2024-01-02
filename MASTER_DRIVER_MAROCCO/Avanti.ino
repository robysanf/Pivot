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
