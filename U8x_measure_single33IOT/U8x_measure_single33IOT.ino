//Hexadezimale-Codes from Usermanual
byte autobdr[] = {0x55};//Auto Baud Rate
byte rdstatus[] = {0xAA, 0x80, 0x00, 0x00, 0x80};//Read Module Latest Status
byte rdhwn[] = {0xAA, 0x80, 0x00, 0x0A, 0x8A};//Read Hardware Version Number
byte rdswn[] = {0xAA, 0x80, 0x00, 0x0C, 0x8C};//Read Software Version Number
byte rdsn [] = {0xAA, 0x80, 0x00, 0x0E, 0x8E};//Read Module Serial Number
byte rdiv[] = {0xAA, 0x80, 0x00, 0x06, 0x86};//Read Input Voltage
byte rdmres[] = {0xAA, 0x80, 0x00, 0x22, 0xA2}; // Read Measure Result (usermanual S13 result)
byte lon[] = {0xAA, 0x00, 0x01, 0xBE, 0x00, 0x01, 0x00, 0x01, 0xC1};// Laser on
byte loff[] = {0xAA, 0x00, 0x01, 0xBE, 0x00, 0x01, 0x00, 0x00, 0xC0};//Laser off
byte shotauto[] = {0xAA, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x00, 0x21};//Start 1-shot Auto Distance Measure
byte shotslow[] = {0xAA, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x01, 0x22};// Start 1-shot Slow Distance Measure
byte shotfast[] = {0xAA, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x02, 0x23};//Start 1-shot Fast Distance Measure
byte cntinusauto[] = {0xAA, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x04, 0x25}; //Start Continuous Auto Distance Measure auto
byte cntinusslow[] = {0xAA, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x05, 0x26};// Start Continuous Slow Distance Measure slow
byte cntinusfast[] = {0xAA, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x06, 0x27};// Start Continuous Fast Distance Measure fast
byte stopmes[] = {0x58};//Stop continuous Mesure

byte incomingByte [13] = {};
int x = 0;
int count = 0;
int val = 0;
int val1 = 0;
int val2 = 0;
int val3 = 0;
void setup() {
  Serial1.begin(19200, SERIAL_8N1); 
  Serial.begin(19200);
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  delay(200);
  Serial1.write(autobdr, sizeof(autobdr));
  delay(100);
  Serial1.write(rdstatus, sizeof(rdstatus));
  delay(100);
  Serial1.write(rdiv, sizeof(rdiv));
  delay(100);
  Serial1.write(lon, sizeof(lon));
}

void loop() {
  Serial1.write(shotfast, sizeof(shotfast));
  delay(100);
  
  while (Serial1.available() > 0){
   
   Serial.println(Serial1.read(),HEX);
  /*  Serial1.readBytes(incomingByte, 13);
    val = incomingByte[6];
    Serial.println(String(incomingByte));
    val = val << 8;
    val1 = incomingByte[7];
    val1 = val1 << 8;
    val = val+ val1;
    val2 = incomingByte[8];
    val2 = val2 << 8;
    val = val+ val2 + incomingByte[9];
    Serial.println(val, DEC);*/
  }
  //Serial.println("");
  //delay(200);
}
