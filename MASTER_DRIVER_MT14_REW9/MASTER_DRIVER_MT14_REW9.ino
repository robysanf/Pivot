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
  pinMode(apri_serratura, OUTPUT);
  pinMode(CHIUDI, INPUT_PULLUP);  // VALORE DEL PIN chiudi
  pinMode(APRI, INPUT_PULLUP);  // VALORE DEL PIN apri
  pinMode(A5, INPUT_PULLUP);  // VALORE DEL PIN stato serratura
  pinMode(A4, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(HC12, OUTPUT);//cambio canale hc
  digitalWrite(HC12, HIGH);
  digitalWrite(A6, HIGH);digitalWrite(A7, HIGH);

  attachInterrupt(digitalPinToInterrupt(3), avanti_3, CHANGE );
  attachInterrupt(digitalPinToInterrupt(2), avanti_2, RISING);

  WIFIMode();
  SocketsServer.listen(WEBSOCKETS_PORT);
  Serial.print(SocketsServer.available() ? "WebSockets Server Running and Ready on " : "Server Not Running on ");
  Serial.println(BOARD_NAME);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print(", Port: ");
  Serial.println(WEBSOCKETS_PORT);    // Websockets Server Port
  Storage_Load();
  md.init();
  Serial.begin(9600);
  Serial1.begin(9600);
  /* digitalWrite(4, HIGH);
    digitalWrite(A4,HIGH);
    md.setM2Speed(0);
    md.setM2Speed(60 * motore * -1);
    delay(500);
    //pos = 0;
    md.setM2Speed(0);
    delay(500);
    pos = 0;

    digitalWrite(4, LOW);
    digitalWrite(A4, LOW);
    /*/
  if (configurazione) {
    set_reset();
  }
}

void loop() {
 
  ascolta_sock() ;
  // -- verifico che non ci sia un comando da ripetere
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
  /*  if ((millis() - tempo_cane) > 6000 || String(stato_Bea).substring(2, 3).toInt()  == 0 ) {
      Serial.println(" NOoo-----224477******************* ");
      Serial.print("tempo_cane  == "); Serial.println(String(millis() - tempo_cane));
      Serial.print("stato_Bea  == "); Serial.println(String(stato_Bea).substring(2, 3).toInt());
    }*/

  delay(10);

  Check_Pin();
  // -- LEGGO IL COMANDO VIA MONITOR SERIALE ****
  serialEvent();
  if (stringComplete) {
    if (inputString == "Calcola_Consumo") {
      Serial.println("--------------- Calcola_Consumo --------------");
      Calcola_Consumo(100);
    }
    if (inputString.startsWith("Cambia_Canale")) {
      Serial.print("--------------- Cambia Canale --------------");
      Serial.println(inputString.substring(13));
      cambia_canale(inputString.substring(13));
    }
    if (inputString == "simula_ENCODER") {
      Serial.println("--------------- simula_ENCODER --------------");
      encoder = encoder * -1;
    }

    // -- COMANDI NORMALI
    if (inputString == "apri") {
      
      Serial.println("--------------- Apri top = 500 --------------");
      //top = 500;
      Dai_Parti(top_max);
    }
    if (inputString == "wifi") {
      
      Serial.println("--------------- WI FI RESET--------------");
     WiFi.end();
     WIFIMode();
    }
    if (inputString == "chiudi") {
      Serial.println("--------------- Chiudi top = 500 --------------");
      //top = -500;
      Dai_Parti(-top_max);
    }
    if (inputString == "stop") {
      Serial.println("--------------- Stop --------------");
      Stop(5);
    }
    if (inputString == "var") {
      Serial.println("--------------- Var --------------");
      Storage_Read();
    }
    inputString = "";
    stringComplete = false;
  }

  // -- FERMO AI FINECORSA ****

  if (pos >= pos_aperto && direzione == 1 ) {
    Serial.println("STOP POS");
    Stop(5);
    tutto_aperto = true;
    conta = millis();
  }
  if (pos < (abbrivio * imp) && direzione == -1) {
    Serial.println("STOP POS");
    Stop(5);
  }
  // -- DURAMTE IL MOVIMENTO CONTROLLO LA POSIZIONE, LA VELOCITA' ****
  if ( direzione != 0 ) {
    Serial.print("tempo_loop = "); Serial.println(String(micros() - tempo_loop));
    tempo_loop = micros();
    Controlla_Posizione();
    Mantieni_Targhet(Crocera);
    int consumo = fai_Media();
    if ( consumo > consumo_max_crocera) { // -- BISOGNA FARE CONSUMO IN BASE ALLA VELOCITA'
      int direzione_sblocco = direzione * -1;
      Serial.print("superato consumo-------------------------"); Serial.println(consumo);
      Stop(1);
      emergenza(direzione_sblocco);
    }
    // -- DURANTE IL MOVIMENTO STAMPO DATI DI INTERESSE ****
    //Serial.print("POS  == "); Serial.println(pos);
    //Serial.print("consumo = "); Serial.println(consumo);
    //Serial.print("VELOCITA'  == "); Serial.println(VELOCITA);
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
    Dai_Parti( -top_max);
    conta = 0;
    Bea_stop = false;
  }
  if ( millis() - conta > Riattiva_Reopen && Bea_reopen == true) {
    Serial.println("riparti reop = ");
    Dai_Parti( top_max);
    conta = 0;
    Bea_reopen = false;
  }
  //SE è TUTTO APERTO DOPO 10 SECONDI CHIUDO
  if ( millis() - conta > Chiusura_Automatica && tutto_aperto == true) {
    Serial.println("riparti tutto aperto = ");
    Dai_Parti( -top_max);
    conta = 0;
  }
  //Controlla_Bea();
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

void Controlla_Posizione() {
  if ((pos > pos_3 && direzione == -1) || (pos < pos_4 && direzione == 1) ) { // VELOCITA MASSIMA
    Crocera = Velocita_Alta;
    consumo_max_crocera = consumo_Alta_max * 1.1;
    Serial.print("cambio Crocera ALTA= "); Serial.println(Crocera);
  }
  if (/*(pos < pos_2 && direzione == -1) ||*/ (pos > pos_5 && direzione == 1) ) { // RALLENTAMENTO 1
    Crocera = Velocita_Media;
    consumo_max_crocera = consumo_Media_max * 1.15;
    Serial.print("cambio Crocera MEDIA = "); Serial.println(Crocera);
  }
  if (/*(pos < pos_1 && direzione == -1) ||*/ (pos > pos_6 && direzione == 1) ) { // RALLENTAMENTO 2
    Crocera = Velocita_Bassa;
    consumo_max_crocera = consumo_Bassa_max * 1.2;
    Serial.print("cambio Crocera BASSA= "); Serial.println(Crocera);
  }
  //Serial.print("Crocera  == "); Serial.println(Crocera);
  //Serial.print("POS  == "); Serial.println(pos);
}

void set_reset() {
  Serial.println("Set reset ridotto");
  digitalWrite(4, HIGH);
  digitalWrite(A4, HIGH);
  md.setM2Speed(0);
  pos_vecchio = pos;
  for (int i = 50; i < 100; i = i + 1) {
    md.setM2Speed(i * motore * -1);
    delay(10);
  }
  Serial.println("Set reset While");
  while (pos_vecchio != pos) {
    pos_vecchio = pos;
    delay(1000);
  }
  md.setM2Speed(0);
  md.setM2Speed(60 * motore * -1);
  delay(500);
  pos = 0;
  pos_vecchio = pos;
  digitalWrite(4, LOW);
  digitalWrite(A4, LOW);
}
