void emergenza(int chi) {
  Serial.print("emergenza ----- = ");Serial.println(chi);
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  bandierina_emergenza = true;
  tempo_emergenza = millis(); 
}
