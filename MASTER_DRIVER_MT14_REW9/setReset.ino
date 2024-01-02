void set_reset() {
  Serial.println("Set reset ridotto");
  digitalWrite(pinDisableDriver, HIGH);
  digitalWrite(pinReleMotore, HIGH);
  md.setM2Speed(0);
  pos_vecchio = 10;
  for (int i = 50; i < 100 && pos!=0; i = i + 1) {
    
    md.setM2Speed(i * motore);
    checkPuntoZero();
    delay(10);
  }
  Serial.println("Set reset While");
  while (pos!=0) {
    checkPuntoZero();
    delay(100);
  }
  md.setM2Speed(0);
  md.setM2Speed(60 * motore * -1);
  delay(500);
  pos = 0;
  pos_vecchio = pos;
  digitalWrite(pinDisableDriver, LOW);
  digitalWrite(pinReleMotore, LOW);
}

int getDir(){
    if(latoAB==0)
       return -1;
    return latoAB;
  }
