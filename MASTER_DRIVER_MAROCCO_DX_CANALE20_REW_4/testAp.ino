void testAp(){
   
  for(int i=0;i<5;i++){
  WiFi.end();
  Serial.println("ReStart AP_SimpleWebServer on ");
   if (WiFi.status() == WL_NO_MODULE)                      // check for the WiFi module:
  {
    Serial.println("Communication with WiFi module failed!");
    
    continue;
  }
 
  Serial.print("Try "); Serial.print(String(i)) ;Serial.print(" Time to ReCreating access point named: ");Serial.println(ssid);
  WiFi.config(ip); 
  delay(500);
   
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING)
  {
    Serial.println("Creating access point failed");
   delay(500);
   continue;
  }else
  {break;}
  }//for
}
