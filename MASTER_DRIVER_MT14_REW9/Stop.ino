void Stop(int Delay) {
  for (int i = tensione; i > 0; i = i - 1) {
    if (i < 0) i = 0;
    md.setM2Speed(i * motore * direzione * vers);
    delay(Delay);
  }
  //top = 0;
  Serial.println("STOP*******************");
  md.setM2Speed(0);
  tensione = 0;
  in_movimento = 0;
  direzione = 0;
  // delay(1000);  sostituito e messo dopo la chiamata
  for (int ic = 0; ic < 20; ic++) {
    corrente[ic] = 0;
  }
  // --  V_M = 0.00; sostituito con   if( (micros() - T1) < (1/(15*imp))*1000000*(cadenza*2))  nel loop
  digitalWrite(pinDisableDriver, LOW);
  digitalWrite(pinReleMotore,LOW);
  if(pos < pos_chiuso* vers)  {
  inVia("111", 1); // ******************************************************** occhio *************************************
  }
}

 
