void puntozero1(){
     puntoZero1=digitalRead(pinZero1);
  }
 
 void puntozero2(){
   puntoZero2=digitalRead(pinZero2);
  }

 void latoAB(){
    latoAB=digitalRead(pinAB);
   
  }

  void checkPuntoZero(){
    if( (puntoZero1 == 0 && puntoZero2 == 1) || (puntoZero1 == 1 && puntoZero2 == 0))
    {
       md.setM2Speed(50);//trovare un valore minimo
        digitalWrite(pinReleBlocca,HIGH);
        pos=0;
      }
      if( puntoZero1 == 0 && puntoZero2 == 0)
    {
       md.setM2Speed(0);
        digitalWrite(pinReleBlocca,HIGH);
        pos=0;
      }
    }

 
