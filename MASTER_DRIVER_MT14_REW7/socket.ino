void Storage_Save(String key, String value) {
  WiFiStorageFile file = WiFiStorage.open("/fs/config");

  file.write(value.c_str(), value.length());

  file.close();

}

void Storage_SaveAll(String value) {
  WiFiStorageFile file = WiFiStorage.open("/fs/config");
  if(file)
     file.erase();
  file.write(value.c_str(), value.length());

  file.close();

}

String Storage_Read() {
  WiFiStorageFile file = WiFiStorage.open("/fs/config");
  String s = "";
  uint8_t buf[STORAGE_BUFFER];
  if (file)
  {
    file.seek(0);
    file.read(buf, STORAGE_BUFFER);
    s = String((char*) buf);
  }

  char* list=(char*) buf;
  Serial.println("leggo:");
  Serial.println(list);
  /*char * pch;
  String var_to_return;
  char toret[40] = "";
  pch = strtok (list, "\n");
  int cont = 0;
  while (pch != NULL)
  {
    if (cont == pos_num)
    {
      strcat(toret, nuovo_valore);
    }
    else {
      strcat(toret, pch);
    }
    strcat(toret, ",");
    cont++;

    pch = strtok (NULL, ",");
  }
*/
  file.close();
  return s;
}

int Storage_reset() {

  WiFiStorageFile file = WiFiStorage.open("/fs/config");
  if (file)
  {
    file.erase();
  }
  else {
    return -1;
  }
  return 0;
}

String Storage_Load() {
  WiFiStorageFile file = WiFiStorage.open("/fs/config");
  String s = "";
  uint8_t buf[STORAGE_BUFFER];
  if (file)
  {
    file.seek(0);
    file.read(buf, STORAGE_BUFFER);
    s = String((char*) buf);
  }
 file.close();
  char* list=(char*) buf;
  Serial.println("leggo load:");
  Serial.println(list);
  char * pch;
  pch = strtok (list, "#");
  
  while (pch != NULL)
  {
   String s=String(pch);
   //Serial.print("string s: ");Serial.println(s);
   spaccaChiaveValore(s);
   pch = strtok (NULL, "#");
   // Serial.print("in while: ");Serial.println(pch);
  }
   imp_vel = ((1 / (imp / (cadenza*2))) * 1000000);
   pos_1 = (pos_aperto*10)/100;
   pos_2 = (pos_aperto*20)/100;
   pos_3 = (pos_aperto*30)/100;
   pos_4 = (pos_aperto*70)/100;
   pos_5 = (pos_aperto*80)/100;
   pos_6 = (pos_aperto*90)/100;

  return s;
}


void spaccaChiaveValore(String str_line) {
Serial.print(" str_line: ");Serial.println(str_line);
 int pos=str_line.indexOf("=");
    if (pos>0)
    {
      char var_str[50];
      str_line.substring(0,pos).toCharArray(var_str, 50);
      String valore=str_line.substring(pos+1);
       Serial.print("var_str ");
      Serial.println(var_str);
      int j;
     for (j = 0;  j < sizeof (conversion) / sizeof (conversion[0]);  ++j)
        {//Serial.println("for:");
         //Serial.println(var_str);Serial.println(conversion[j].str);
          if (!strcmp (var_str, conversion[j].str))
          {
            switch (conversion[j].val)
            {//******  le varibili qui devono essere le stesse dell enum nelle varibili.h
              case RAGGIO:               raggio = String(valore).toFloat(); Serial.print("set raggio:");Serial.println(raggio); break;       
              case IMP:                  imp = String(valore).toFloat(); break;
              case POS_APERTO:           pos_aperto = String(valore).toInt(); break;
              case POS_CHIUSO:           pos_chiuso = String(valore).toInt(); break;
              case VELOCITA_BASSA:       Velocita_Bassa = String(valore).toFloat(); ; break;                   
              case VELOCITA_MEDIA:       Velocita_Media = String(valore).toFloat(); break;
              case VELOCITA_ALTA:        Velocita_Alta = String(valore).toFloat(); break;                              
              case MOTORE:               motore = String(valore).toInt(); break;
              case ENCODER:              encoder = String(valore).toInt(); break;
              case CONFIGURAZIONE:       configurazione = String(valore).toInt(); break;
              case POS   :               pos = String(valore).toInt(); break;
              case CADENZA   :           cadenza = String(valore).toInt(); break;
              default: break;
            }
            break;
            }
        }   
    }
 
}
