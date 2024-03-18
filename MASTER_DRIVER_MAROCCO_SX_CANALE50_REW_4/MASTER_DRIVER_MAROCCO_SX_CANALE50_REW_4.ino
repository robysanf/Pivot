// -- CANALE HC12 ch050

#include "defines.h"
#include "variabili.h"
#include <WiFiNINA_Generic.h>

#include <WebSockets2_Generic.h>
using namespace websockets2_generic;
#include "DualMC33926MotorShield.h"

DualMC33926MotorShield md;
WebsocketsServer SocketsServer;
WebsocketsClient* client = NULL;
char ssid[] = SECRET_SSID;              // your network SSID (name)
char pass[] = SECRET_PASS;              // your network password (use for WPA, or use as key for WEP), length must be 8+
int status = WL_IDLE_STATUS;
void setup() {
  //pinMode(apri_serratura, OUTPUT);
  //pinMode(CHIUDI, INPUT_PULLUP);  // VALORE DEL PIN chiudi
  pinMode(APRI, INPUT_PULLUP);  // VALORE DEL PIN apri A6
  pinMode(5, OUTPUT);  // relè taglia fili
  pinMode(6, OUTPUT);  // relè ElettroMagnete
  pinMode(A2, INPUT_PULLUP);  // modalita notte
  pinMode(A4, INPUT_PULLUP);  // allarme fuoco
  pinMode(A3, INPUT_PULLUP);  // EX CAMBIATO dentro fuori
  pinMode(A7, INPUT_PULLUP);  //  pin punto 0    METTERE CONDENSATORE
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);  //  DENTRO FUORI (ex sensore_interno)   METTERE CONDENSATORE
  pinMode(13, INPUT_PULLUP);  //  sensore_esterno    METTERE CONDENSATORE
  attachInterrupt(digitalPinToInterrupt(3), avanti_3, CHANGE );
  attachInterrupt(digitalPinToInterrupt(2), avanti_2, RISING);
  attachInterrupt(digitalPinToInterrupt(A7), puntozero, FALLING);
  //attachInterrupt(digitalPinToInterrupt(13), sensore_esterno, RISING );
  //attachInterrupt(digitalPinToInterrupt(A5), sensore_interno, RISING );


  WIFIMode();
  SocketsServer.listen(WEBSOCKETS_PORT);
  Serial.print(SocketsServer.available() ? "WebSockets Server Running and Ready on " : "Server Not Running on ");
  Serial.println(BOARD_NAME);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print(", Port: ");
  Serial.println(WEBSOCKETS_PORT);    // Websockets Server Port

  md.init();
  Serial.begin(9600);
  Serial1.begin(9600);
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  md.setM2Speed(0);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  // nel caso di una interruzione della corrente al riavvio controllo se c'è un incendio
  while( digitalRead(A4) ==  LOW ){
    Serial.println("---allarme incendio in corso---");
    delay(1000);
  }
  Serial.println("--------------- SETTAGGIO --------------");
  Disattiva_Bea = true;
  settaggio();
  bandierina_Bea = true;

  //md.setM2Speed(0);
  //Storage_Load();
  //digitalWrite(4, LOW);
  //digitalWrite(5, LOW);
}
void loop_2() {
  if (pos_vecchio_loop != pos ) {
    Serial.print(" SENSORE interno_esterno =  "); Serial.println(digitalRead(A5));
    if (digitalRead(A5) ==  LOW) {
      Serial.println(" SENSORE interno_esterno ================================================================ 0 ");
    }
    Serial.print(" pos =  "); Serial.println(pos);
  }
  pos_vecchio_loop = pos;
  delay(50);
  serialEvent();
  if (stringComplete) {
    if (inputString == "SETTAGGIO") {
      Serial.println("--------------- SETTAGGIO --------------");
      Disattiva_Bea = true;
      settaggio();
      bandierina_Bea = true;
    }
    inputString = "";
    stringComplete = false;
  }

}
void loop() {

  if (bandierina_fault == true ) {
    delay(1000);
    Serial.println("--------------- FAULT --------------");
    return;
  }
  ascolta_sock() ;
  // -- verifico che non ci sia un comando da ripetere
  ///*
  if ( ripeti_comando ) {
    if ( comando.substring(2, 3).toInt() != String(stato_Bea).substring(3, 4).toInt()) { // -- se il comando e la risposta non coincidono
      inVia(comando, 1);                                                                 // -- allora ripeto l'invio
      delay(100);
      ripeti_comando_conteggio ++;
    } else {
      ripeti_comando = false;                                                            // -- altrimemti tolgo la bandiera
      ripeti_comando_conteggio = 0;
    }
    if ( ripeti_comando_conteggio > 10 ) {
      // -- qualcosa non va
      Serial.println(" NOoo-----*********  224477 **********---------------- ");
    }
  }
  // -- leggo lo stato dal BEA
  delay(10);
  ricevi(7);
  // -- controllo che almeno ogni 6 secondi il Bea manda un segnale
  if ((millis() - tempo_cane) > 6000 || String(stato_Bea).substring(2, 3).toInt()  == 0 ) {
    //Serial.println(" NOoo-----224477******************* ");
    //Serial.print("tempo_cane  == "); Serial.println(String(millis() - tempo_cane));
    //Serial.print("stato_Bea  == "); Serial.println(String(stato_Bea).substring(2, 3).toInt());
  }
  //*/
  delay(10);


  // -- CONTROLLO IL FUOCO

  if (digitalRead(A4) == LOW) {
    if (fuoco == false) {
      Stop(5, 34);
      digitalWrite(6, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }
    fuoco = true;
    bandierina_fuoco = true;
    return;
  } else {
    fuoco = false;
  }
  if ( bandierina_fuoco == true && fuoco == false ) {
    if (abs(pos) > 20000 && abs(pos) < pos_aperto) {
      Dai_Parti( -top_max, 0);
    }
    if (abs(pos) < 20000 ) {
      Dai_Parti( top_max, 1);
    }
    if (abs(pos) > pos_aperto ) {
      bandierina_fuoco = false;
      return;
    }
    bandierina_fuoco = false;
  }
  // -- controllo i pulsanti
  Check_Pin();

  if (digitalRead(A2) == LOW) { // SE IL PULSANTE A2 E' PREMUTO (modalità notte) ALLORA NON SI ENTRA
    Entra = false;
  } else {
    Entra = true;
  }





  // -- LEGGO IL COMANDO VIA MONITOR SERIALE ****
  serialEvent();
  if (stringComplete) {
    if (inputString == "Calcola_Consumo") {
      Serial.println("--------------- Calcola_Consumo --------------");
      Calcola_Consumo(100);
    }
    if (inputString == "simula_ENCODER") {
      Serial.println("--------------- simula_ENCODER --------------");
      encoder = encoder * -1;
    }

    // -- COMANDI NORMALI
    if (inputString == "esci") {
      Serial.println("--------------- esci top = 500 --------------");
      //top = 500;
      Dai_Parti(top_max, 1);
    }
    if (inputString == "entra") {
      Serial.println("--------------- entra top = 500 --------------");
      //top = 500;
      Dai_Parti(top_max, -1);
    }
    if (inputString == "stop") {
      Serial.println("--------------- stop --------------");
      Stop(5, 33);
    }
    if (inputString == "var") {
      Serial.println("--------------- var --------------");
      Storage_Read();
    }
    if (inputString == "SETTAGGIO") {
      Serial.println("--------------- SETTAGGIO --------------");
      Disattiva_Bea = true;
      settaggio();
      Disattiva_Bea = false;
    }
    inputString = "";
    stringComplete = false;
  }

  // -- FERMO AI FINECORSA ****

  if (abs(pos) >= pos_aperto && direzione == 1 ) {
    Serial.println("STOP POS tutto aperto");
    Stop(5, 32);
    tutto_aperto = true;
    conta = millis();
  }
  if (abs(pos) < (abbrivio * imp) && direzione == -1) {
    Serial.println("STOP POS abbrivio");
    Stop(15, 31);
  }
  // imposto a tutto aperto == true se porto manualmente a tutta apertura
  if (abs(pos) >= pos_aperto && direzione == 0 && tutto_aperto == false) {
    Serial.println("STOP POS tutto aperto");
    Stop(5, 32);
    tutto_aperto = true;
    conta = millis();
  }
  // -- DURAMTE IL MOVIMENTO CONTROLLO LA POSIZIONE, LA VELOCITA' ****
  if ( direzione != 0 ) {
    //Controlla_Bea();
    // -- *********** Serial.print("tempo_loop = "); Serial.println(String(micros()-tempo_loop));
    tempo_loop = micros();
    Controlla_Posizione(0);
    Mantieni_Targhet(Crocera);
    int consumo = fai_Media();
    if ( consumo > consumo_max_crocera) { // -- BISOGNA FARE CONSUMO IN BASE ALLA VELOCITA'
      int direzione_sblocco = direzione * -1 * _Senso;
      Serial.print("superato consumo-----------------consumo = "); Serial.println(consumo);
      Stop(1, 30);
      delay(1000);
      emergenza(1);
    }

    // -- DURANTE IL MOVIMENTO STAMPO DATI DI INTERESSE ****
    //Serial.print("POS  == "); Serial.println(pos);
    Serial.print("consumo = "); Serial.println(consumo);
    Serial.print("VELOCITA'  == "); Serial.println(V_M);
    Serial.print("tensione = "); Serial.println(tensione );
  }
  delay(10);
  if (direzione == 0) {
    if ( ( (micros() - T1) > (1 / (15 * imp)) * 1000000 * (cadenza * 2)) && V_M != 0) { // -- se sono fermo e son passat1 (1/(15*imp))*1000000*(cadenza*2)) microsecondi allora consi
      V_M = 0;
      Serial.print("V_M 00 = "); Serial.println(V_M);
    }
    // -- SE DA FERMO MUOVO L'ANTA STAMPO IL POS ****
    if (pos_vecchio_loop != pos ) {
      Serial.print("pos = "); Serial.println(pos);
      Serial.print("V_M = "); Serial.println(V_M);
      Serial.print("consumo = "); Serial.println(md.getM2CurrentMilliamps());
    }
  }
  pos_vecchio_loop = pos;
  /*Serial.print("cont loop = ");Serial.println(millis()-conta);
    Serial.print("beastop = ");Serial.println(Bea_stop);
    Serial.print("beareop = ");Serial.println(Bea_reopen);
    Serial.print("tutto ap = ");Serial.println(tutto_aperto); */
  if ( millis() - conta > Chiusura_Stop && Bea_stop == true) {
    Serial.println("riparti stop= ");
    Dai_Parti( -top_max, 0);
    Serial.print("direzione in chiusura = "); Serial.println(direzione);
    conta = 0;
    Bea_stop = false;
  }
  if ( millis() - conta > Riattiva_Reopen && Bea_reopen == true) {
    Serial.println("riparti reop = ");
    Dai_Parti( top_max, 1);
    conta = 0;
    Bea_reopen = false;
  }
  //SE è TUTTO APERTO DOPO 10 SECONDI CHIUDO
  if ( millis() - conta > Chiusura_Automatica && tutto_aperto == true) {
    Serial.println("riparti tutto aperto = ");
    Dai_Parti( -top_max, 0);
    conta = 0;
  }
  Controlla_Bea();
  if ( bandierina_emergenza == true  &&  millis() - tempo_emergenza > 5000) {
    Dai_Parti( -top_max, 0);
    if ( bandierina_emergenza_risolta == true) {
      bandierina_emergenza = false;
      bandierina_emergenza_risolta = false;
      return;
    }
    tempo_emergenza = millis();
  }

}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
      return;
    }
    inputString += inChar;
  }
}

void Controlla_Posizione(boolean in_partenza) {
  //Serial.print("entro Crocera = "); Serial.println(Crocera);
  if ( abs(pos) >= pos_aperto && direzione == 1) {
    if ( ( pos > 0 && _Senso == 1 ) || ( pos < 0 && _Senso == -1 )) {
      Crocera = 0;
      Serial.println("sono già tutto aperto");
      return;
    }
  }
  if (((abs(pos) > pos_3 && direzione == -1) || (abs(pos) < pos_4 && direzione == 1) || (abs(pos) > pos_3 && direzione == 1 && in_partenza )) && Crocera != Velocita_Alta ) { // VELOCITA MASSIMA
    Crocera = Velocita_Alta;
    consumo_max_crocera = consumo_Alta_max * 1.1;
    Serial.print("cambio Crocera = "); Serial.println(Crocera);
  }
  if (((abs(pos) < pos_2 && direzione == -1) || (abs(pos) > pos_5 && direzione == 1)) &&  (Crocera > Velocita_Media || Crocera == 0 ) && (pos * _Senso * direzione) < 0) { // RALLENTAMENTO 1  && ((pos * _Senso) < 0 && _Senso == -1 )
    Crocera = Velocita_Media;
    consumo_max_crocera = consumo_Media_max * 1.15;
    Serial.print("cambio Crocera = "); Serial.println(Crocera);
  }
  if (((abs(pos) < pos_1 && direzione == -1) || (abs(pos) > pos_6 && direzione == 1)) && (Crocera > Velocita_Bassa || Crocera == 0) && (pos * _Senso * direzione) < 0) { // RALLENTAMENTO 2  && ((pos * _Senso) < 0 && _Senso == -1 )
    Crocera = Velocita_Bassa;
    consumo_max_crocera = consumo_Bassa_max * 1.2;
    Serial.print("cambio Crocera = "); Serial.println(Crocera);
  }
  //Serial.print("Crocera  == "); Serial.println(Crocera);
  //Serial.print("POS  == "); Serial.println(pos);
}
void loop_(){
  Serial.print(" A0 =  "); Serial.println(digitalRead(A0));
  Serial.print(" A1 =  "); Serial.println(digitalRead(A1));
  Serial.print(" A2 =  "); Serial.println(digitalRead(A2));
  Serial.print(" A3 =  "); Serial.println(digitalRead(A3));
  Serial.print(" A4 =  "); Serial.println(digitalRead(A4));
  Serial.print(" A5 =  "); Serial.println(digitalRead(A5));
  Serial.print(" A6 =  "); Serial.println(digitalRead(A6));
  Serial.print(" A7 =  "); Serial.println(digitalRead(A7));
  Serial.print(" D2 =  "); Serial.println(digitalRead(2));
  Serial.print(" D3 =  "); Serial.println(digitalRead(3));
  Serial.print(" D4 =  "); Serial.println(digitalRead(4));
  Serial.print(" D5 =  "); Serial.println(digitalRead(5));
  Serial.print(" D6 =  "); Serial.println(digitalRead(6));
  Serial.print(" D7 =  "); Serial.println(digitalRead(7));
  Serial.print(" D8 =  "); Serial.println(digitalRead(8));
  Serial.print(" D9 =  "); Serial.println(digitalRead(9));
  Serial.print(" D10 =  "); Serial.println(digitalRead(10));
  Serial.print(" D11 =  "); Serial.println(digitalRead(11));
  Serial.print(" D12 =  "); Serial.println(digitalRead(12));
  Serial.print(" D13 =  "); Serial.println(digitalRead(13));
  Serial.println("------------------------------------------------------------");
  delay(3000);
}
