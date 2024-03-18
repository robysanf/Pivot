void Check_Pin(){    //return;                    // -- COSTRUISCO LA STRINGA DA SWITCIARE
  int Pulsanti = 0;
  if (digitalRead(APRI) == LOW){Pulsanti = 2000;} else {Pulsanti = 1000;} 
  Pulsanti += 10;// -- if ( (digitalRead(CHIUDI) == LOW){Pulsanti += 20;} else {Pulsanti += 10;}
  if (stato_APRI == 1){ Pulsanti += 100;} 
  if (stato_CHIUDI == 1){Pulsanti += 1;} 
  if (Pulsanti == _Pulsanti){return;}
  _Pulsanti = Pulsanti;
   Serial.print("\n dentro Pulsanti = ");Serial.println(Pulsanti);
  

    switch (Pulsanti) {
      
      case 2010:             // -- APPENA PREMUTO APRI
         if (direzione != 0){Stop(5,5); return;}                                         // -- SE SONO IN MOVIMENTO > FERMO         
        delay(50);
        if(digitalRead(APRI)!=LOW){ return;}                                           // -- ALTRIMENTI ASPETTO 300      
        T_scemo_2 = millis();                                                          // -- > GUARDO IL TEMPO
           if ((T_scemo_2 - T_scemo_1) > 100 ){                                        // -- ANTI SCEMO, SE IL TEMPO CHE PASSA DALL'ULTIMA VOLTA CHE HO RILASCIATO UN PULSANTE  E' SUPERIORE A 500..
            bandiera_pulsanti = true;
            Dai_Parti(top_max, 1);                                                 // -- APRO NORMALMENTE                                                                 
            break;
           }
         stato_APRI = 1;                                                               // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
        break;
//------------------------------------------------------------------------------------------------------------    
       case 2110 :           // -- PREMUTO STABILMENTE APRI
                                                                                       // -- NON FACCIO NIENTE
          break;


//------------------------------------------------------------------------------------------------------------    
       case 1021 :           // -- PREMUTO STABILMENTE CHIUDI
                                                                                       // -- NON FACCIO NIENTE
          break;


//------------------------------------------------------------------------------------------------------------        
      case 1110 :            // -- APPENA RILASCIATO APRI
                                           
          stato_APRI = 0;                                                               // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
          T_scemo_1 = millis();
           
         break;
//------------------------------------------------------------------------------------------------------------         
      case 1020 :            // -- APPENA PREMUTO CHIUDI
          if (direzione != 0 ){Stop(5,4);  stato_CHIUDI = 1; return; } // -- SE SONO IN MOVIMENTO > FERMO
          if(pos < pos_chiuso)  {stato_CHIUDI = 1;return;}  
          //delay(50); if(digitalRead(CHIUDI)!=LOW){ return;}                             // -- ALTRIMENTI ASPETTO 300              
          T_scemo_2 = millis();                                                         // -- > GUARDO IL TEMPO
          if ((T_scemo_2 - T_scemo_1) > 100 ){                                          // -- ANTI SCEMO, SE IL TEMPO CHE PASSA DALL'ULTIMA VOLTA CHE HO RILASCIATO UN PULSANTE  E' SUPERIORE A 500..
             Dai_Parti(-top_max, 0);                                                  // -- > CHIUDE
             stato_CHIUDI = 1;                                                          // -- > IMPOSTA IL PULSANTE SU PREMUTO
          }
         break;
 //------------------------------------------------------------------------------------------------------------         
       case 1011 :          // -- APPENA RILASCIATO CHIUDI
         stato_CHIUDI = 0;                                                              // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
         T_scemo_1 = millis();
         break;                  
  

//------------------------------------------------------------------------------------------------------------        
      case 2120 :           // -- premuto Apri E APPENA premuto Chiudi 
          Stop(5,3);                                                                // -- DEVO FERMARE IL MOVIMENTO 
          stato_CHIUDI = 1;                                                             // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
        break;
//------------------------------------------------------------------------------------------------------------       
      case 2021 :           // -- premuto Chiudi E APPENA premuto Apri 
          Stop(5,2);                                                                 // -- DEVO FERMARE IL MOVIMENTO 
          stato_APRI = 1;                                                               // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
         break;
//------------------------------------------------------------------------------------------------------------         
       case 2020 :          // -- APPENA premuto Apri e Chiudi     
          Stop(5,1);                                                                 // -- DEVO FERMARE IL MOVIMENTO
          stato_APRI = 1;                                                               // -- > IMPOSTA IL PULSANTE SU PREMUTO
          stato_CHIUDI = 1;                                                             // -- > IMPOSTA IL PULSANTE SU PREMUTO  
         break;
//------------------------------------------------------------------------------------------------------------         
       case 2121 :          // -- premuto stabilmente Apri e Chiudi                     
          
         break;           
  } 
}
