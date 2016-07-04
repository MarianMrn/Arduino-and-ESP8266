#include <stdlib.h>

#define SSID "Name"
#define PASS "Pass"
#define IP "184.106.153.149" // thingspeak.com
String GET = "GET /update?key=6DSSCRGKSZOYAKM5&field1=";


void setup()
{
  Serial.begin(9600);
  Serial.println("AT");
  delay(5000);
  if(Serial.find("OK")){
    connectWiFi();
  }
}
float val = 0;
void loop(){
  float potentiometer = analogRead(A2);
  float diff = abs (potentiometer - val)
  char buffer[10];
  String value = dtostrf(potentiometer, 4, 1, buffer);
  
  if (diff > 100 ) {
     val = potentiometer;
     updateTemp(value);
  }   
}

void updateData(String value){
  String cmd = "AT+CIPSTART=\"TCP\",\""; //prepare get string
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  if(Serial.find("Error")){
    return;
  }
  cmd = GET;
  cmd += value;
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
    if(Serial.find("OK")) {
        Serial.print(cmd);
  }
    else {
        Serial.println("AT+CIPCLOSE");
  }
}

 
boolean connectWiFi(){
  Serial.println("AT+CWMODE=1");
  delay(2000);
  //Connect to wifi with pass and ssid
  String cmd="AT+CWJAP=\""; // accespoint
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  delay(5000);
    if(Serial.find("OK")) {
        return true;
  }
    else {
        return false;
  }
}
