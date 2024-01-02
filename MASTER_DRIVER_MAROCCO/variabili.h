//************   WIFI e SOCKET
IPAddress ip(192, 168, 1, 90);
//#define SECRET_SSID     "VodafoneSANFER"
//#define SECRET_PASS     "hsanfer04@hsanfer04"
#define SECRET_SSID     "EOLO_181478"
#define SECRET_PASS     "AtmRHsuLw"
#define STORAGE_BUFFER 500
int wifimode = 0;
enum nomeVar { RAGGIO, IMP, POS_APERTO, POS_CHIUSO, VELOCITA_BASSA, VELOCITA_MEDIA, VELOCITA_ALTA, MOTORE, ENCODER, CONFIGURAZIONE, POS, CADENZA, CONSUMO_BASSA_MAX, CONSUMO_MEDIA_MAX, CONSUMO_ALTA_MAX} ;
const static struct {
  nomeVar     val;
  const char *str;
} conversion [] = {
  {RAGGIO, "RAGGIO"},
  {IMP, "IMP"},
  {POS_APERTO, "POS_APERTO"},
  {POS_CHIUSO, "POS_CHIUSO"},
  {VELOCITA_BASSA, "VELOCITA_BASSA"},
  {VELOCITA_MEDIA, "VELOCITA_MEDIA"},
  {VELOCITA_ALTA, "VELOCITA_ALTA"},
  {MOTORE, "MOTORE"},
  {ENCODER, "ENCODER"},
  {CONFIGURAZIONE, "CONFIGURAZIONE"},
  {POS, "POS"},
  {CADENZA, "CADENZA"},
  {CONSUMO_BASSA_MAX, "CONSUMO_BASSA_MAX"},
  {CONSUMO_MEDIA_MAX, "CONSUMO_MEDIA_MAX"},
  {CONSUMO_ALTA_MAX, "CONSUMO_ALTA_MAX"}

};
//***************************

//******************** PIN ARDUINO
const int apri_serratura = 5;                     // VALORE DEL PIN PER COMANDARE IL DROP-BOLT
//const int STOP = 6;                       // VALORE DEL PIN PER STOP
const int APRI = A6;      // fc2                    // VALORE DEL PIN PER APRI
const int CHIUDI = A7;    // fc1                 // VALORE DEL PIN PER CHIUDI

//******************** VARIBILI STATO
int stato_APRI = 0;                       // INDICA SE IL PIN APRI E PREMUNTO
int stato_CHIUDI = 0;                     // INDICA SE IL PIN CHIUDI E PREMUNTO
int stato_STOP = 0;                       // INDICA SE IL PIN STOP E PREMUNTO
boolean U_P = true;                       // UOMO PRESENTE di default
boolean stato_serratura = false;  //
boolean tutto_aperto = false;
boolean ci_sei = false;
boolean ripeti_comando = false;
boolean Bea_stop = false;
boolean Bea_reopen = false;
int stato_Bea = 1111;
boolean non_aprire = false;
int direzione = 0;
int in_movimento = 0;

//*******************  TEMPO
long tempo_pulsante_1 = 0 ;      // PER TEMPORIZZARE I PULSANTI
long tempo_pulsante_2 = 0 ;      // PER TEMPORIZZARE I PULSANTI
long tempo_pulsante_3 = 0 ;      // PER TEMPORIZZARE I PULSANTI
long T_scemo_1 = 0 ;             // PER TEMPORIZZARE I PULSANTI
long T_scemo_2 = 0 ;             // PER TEMPORIZZARE I PULSANTI
long Tempo_C_U_P = 0 ;           // PER TEMPORIZZARE I PULSANTI
int _Pulsanti = 1010;            // PER TEMPORIZZARE I PULSANTI
long tempo_invia = 0;
long tempo_ricevi = 0;
long tempo_bip = 0;
long tempo_cane = 0;
int tempo_loop = 0;
int tempo_mantieni_targhet = 0;

//*******************  TYMER
int Riattiva_Reopen = 500;
int Chiusura_Stop = 5000;
int Chiusura_Automatica = 10000;

//*******************  VARIBILI POSIZIONE/VELOCITA
int pos_aperto = 82500;
int pos_chiuso = 100;
int pos_1 = (pos_aperto * 15) / 100;
int pos_2 = (pos_aperto * 22) / 100;
int pos_3 = (pos_aperto * 30) / 100;
int pos_4 = (pos_aperto * 70) / 100;
int pos_5 = (pos_aperto * 78) / 100;
int pos_6 = (pos_aperto * 85) / 100;
int pos_vecchio;
int pos_vecchio_loop;
volatile long pos = 300;
int abbrivio = 15; // -- mm per fermarsi

int top_max = 1200;
int Velocita_Bassa = 50;
int Velocita_Media = 80;
int Velocita_Alta = 120;
int consumo_max = 1200;
int Crocera = 0;

int consumo_Bassa = 300;
int consumo_Media = 600;
int consumo_Alta = 900;
int consumo_max_crocera = 0;
int consumo_Bassa_max = 400;
int consumo_Media_max = 750;
int consumo_Alta_max = 1200;

//*************** STRUTTURA
int raggio = 1240;
float imp = 33.12;//pos_aperto/(raggio*3,14/2);  //2.8 ibrido   6.6intecno;  1,6 CBF       // inpulsi per millimetro cambia in base al CPR del encoder
int cadenza = 1;
int encoder = 1;
int motore = 1;
int tensione = 0;
int corrente[20];
int conta_corrente = 0;
int configurazione = 1;

//************* INTERRUPT
volatile float V_M = 0.00;
volatile float imp_vel = ((1 / (imp / (cadenza * 2))) * 1000000);
volatile int giro = 0;
volatile int Time = 120000;
volatile long T1 = 0;
volatile long T3 = 0;
volatile int t_delta = 0;

//***************** CONTATORI STRING
int ripeti_comando_conteggio = 0;
String inputString = "";
String comando = "";
boolean stringComplete = false;
long conta = 0;
int _Senso = 0;
int tempo_controlla_velocita = 0;
volatile boolean Blocco_Anta = false;
int inerzia = 5;
