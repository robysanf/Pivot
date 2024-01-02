long init_sock=0;

void ascolta_sock() {
  
long now=millis();
if(now-init_sock<300)
    {Serial.println("now-init");Serial.print(now-init_sock);
      return;
      }
      init_sock=millis();
     WebsocketsClient  client = SocketsServer.accept();
  //client = new WebsocketsClient;
Serial.print(SocketsServer.available() ? " " : "Socket Server Not Running on ");
  if (!SocketsServer.available())
  {
    WiFi.disconnect();
    WiFi.end();
     WIFIMode();
  }  //*client = SocketsServer.accept();

    if (client.available())
    {
      WebsocketsMessage msg = client.readBlocking();
      // log
      Serial.print("Got Message: ");
      Serial.println(msg.data());
      String strwebHost = String(msg.data());
      Serial.print("strwebhost "); Serial.println(strwebHost);
      String strweb = strwebHost.substring(0, 4);
      String strweb2 = strwebHost.substring(4);
      if ( strweb == "save") {
        // (strweb2); salva su SD 
        Storage_SaveAll(strweb2);
        Storage_Load();
      }
   /*   if ( strweb == "apri") {
        Dai_Parti(top_max);
      }*/
      if ( strweb == "chiu") {
        Dai_Parti(-top_max,0);
      }
      if ( strweb == "stop") {
        Stop(5);
      }
      if ( strweb == "init") {
        Storage_Load();
      }
      if ( strweb == "pos0") {
        pos = 0;
      }
      if ( strweb == "iniz") {
        pos = 0;
        pos_vecchio = pos;
      }
      if ( strweb == "enco") {
        if (pos - pos_vecchio < 0) {
          encoder = encoder * (-1);
          pos = pos * -1;
        }
      }
      if ( strweb == "posA") {
        pos_aperto = pos;
        Serial.print("posA "); Serial.println(pos);
      }

      if ( strweb == "impu") {
        raggio = strweb2.toInt();
        imp = pos_aperto / (raggio * 3.14 / 2);
      }

      if ( strweb == "move") {
        Dai_Parti(top_max,1);
        delay(2000);
        Stop(5);
      }
      if ( strweb == "moto") {
        if (strweb2 == "-")
          motore = motore * (-1);
      }
      if ( strweb == "cons") {
        //apertura e chiusura completa a velocità 50 dai vari pos per calcolare il consumo medio ad ogni velocità delle tre previste
        int d = 0;
        if (strweb2 != "") {
          d = strweb2.toInt();
        }
        Calcola_Consumo(d);
        configurazione=1;//quando fatta "velo" spostarlo dopo velo
      }
      if ( strweb == "velo") {
        //apertura e chiusura completa a varie velocita con prova di arresto da parte dell operatore per impostare attrito per modificare percentuale di aumento comsumo
      }
     if ( strweb == "chch") {
      if (strweb2 != "") { 
            Serial.println("cambia canale");
            inVia("5"+strweb2, 0);
            delay(2000);
            cambia_canale(strweb2);
         }
      }

      //qui devono essere passati i nomi delle variabili esatti perchè poi vengono rispediti cosi all'arduino
      String risposta = "";

      risposta = "RAGGIO=" + String(raggio) + "#IMP=" + String(imp) + "#POS_APERTO=" + String(pos_aperto) + "#POS_CHIUSO=" + String(pos_chiuso)
                 + "#VELOCITA_BASSA=" + String(Velocita_Bassa) + "#VELOCITA_MEDIA=" + String(Velocita_Media) + "#VELOCITA_ALTA=" + String(Velocita_Alta)
                 + "#ENCODER=" + String(encoder) + "#MOTORE=" + String(motore) + "#CONFIGURAZIONE=" + String(configurazione) + "#pos=" + String(pos) + "#CADENZA=" + String(cadenza)
                 + "#CONSUMO_BASSA_MAX=" + String(consumo_Bassa_max) + "#CONSUMO_MEDIA_MAX=" + String(consumo_Media_max) + "#CONSUMO_ALTA_MAX=" + String(consumo_Alta_max);
      Serial.print("risposta"); Serial.println(risposta);
      client.send(risposta);
      Serial.print("oooooooooooo "); Serial.println(strwebHost);
      // close the connection
      client.close();
      Storage_SaveAll(risposta);
      Storage_Load();

    }
    //delete client;
  //}
}
/*
  void Salva_Socket(String varList) {
  char list[255];
  varList.toCharArray(list, 255);
  char * pch;
  pch = strtok (list, "#");
  if (pch == NULL) {
    return;
  }
  String s = String(pch);
  String nome_variabile = s.substring(0, s.indexOf("="));
  String valore = s.substring(s.indexOf("=") + 1);
  Serial.print("leggo"); Serial.print(nome_variabile); Serial.print(" = "); Serial.println(valore);

  while (pch != NULL)
  {
    dataSave(nome_variabile, valore);
    pch = strtok (NULL, "#");
    if (pch == NULL) {
      break;
    }
    s = String(pch);
    nome_variabile = s.substring(0, s.indexOf("="));
    valore = s.substring(s.indexOf("=") + 1);
  }
  }*/
