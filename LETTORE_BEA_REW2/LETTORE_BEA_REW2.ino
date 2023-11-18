 
int tempo_invio = 0;
int tempo_attesa = 0;
int cadenza = 2000;
String modo = "0";
int HC12=3;
void setup() {
  pinMode(8, INPUT_PULLUP); // -- pin per lo stop
  pinMode(A4, INPUT);       // -- pin per il test
  pinMode(5, INPUT_PULLUP); // -- pin per il reopen
  pinMode(HC12, OUTPUT);//cambio canale hc
  digitalWrite(HC12, HIGH);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  int tempo_loop = micros();
  // -- raccolgo i dati dal BEA e li metto in una char
  char list[4];
  String msg = "" ;
  msg = (digitalRead(8) + 1);              // -- leggo il pin stop
  msg += (digitalRead(5) + 1);             // -- leggo il pin riapri
  if (analogRead(A4) > 515) {        // -- leggo il test
    msg = msg + "1";
  } else {
    msg = msg + "0";
  }
  msg = msg + modo;
  msg.toCharArray(list,5);          // -- fatto   list contiene i dati raccolti dal BEA
  //Serial.println(String(list)+"055");

  // -- invio i dati al GRANDE secondo la cadenza indicata

  if ((millis() - tempo_invio) > cadenza ) {
    long oldt = micros();
    Serial.println("invio");
    Serial1.write(list);
    tempo_invio = millis();
    Serial.println(String(list));
    //Serial.print(" tempo fine trasmissione =  "); Serial.println(String(micros() - oldt));
  }

  delay(25);   // -- do il tempo di inviare e ricevere
  // -- adesso leggo

  
  if (millis() - tempo_attesa > 100) {
    //Serial.print(" tempo attesa = "); Serial.println(String(millis() - tempo_attesa));
    delay(1);
    char myBuffer[4];
    if (Serial1.available()) {
      Serial.print(" striga ricevuta = ");
      long oldt = micros();
      int i = 0;
      boolean ricezione_completata = false;
      while (Serial1.available()) {   
        myBuffer[i] = Serial1.read();
        i++;
        if (i == 3 ) {
          myBuffer[i] = '\0';
          Serial1.end();        // -- cancello il buffer residuo
          Serial1.begin(9600);
          ricezione_completata = true;
          break;
        }
      
      }
      int f = String(myBuffer).substring(2,3).toInt();
      String c = String(myBuffer).substring(1,3);
      int z = String(myBuffer).substring(0,1).toInt();
      Serial.println(f);
      if ( f == 2  &&  ricezione_completata) {
        cadenza = 250;
        Serial1.write(list);
        modo = "2";
      }
      if ( f == 1 &&  ricezione_completata ) {
        cadenza = 2000;
        Serial1.write(list);
        modo = "1";
      }
      if ( f == 3 &&  ricezione_completata){
        Serial1.write(list);
        Serial.println("invio f 333");
      }
      if ( z == 5 &&  ricezione_completata){
          cambia_canale(c);
          Serial.print("cambio canale : ");Serial.println(c);
      }
      
      Serial.println(String(myBuffer));  // -- cosa ricevo dal GRANDE
      //Serial.print(" tempo fine ricezione = "); Serial.println(String(micros() - oldt));
      tempo_attesa = millis();
    }
  }
  //Serial.print(" tempo loop = "); Serial.println(String(micros() - tempo_loop));
}

void cambia_canale(String ch){
     digitalWrite(HC12, LOW);
     delay(150);
      String s="AT+C"+ch;
      char lis[255];
      s.toCharArray(lis,255);
     Serial1.write(lis);
     delay(150);
     digitalWrite(HC12, HIGH);
  }
