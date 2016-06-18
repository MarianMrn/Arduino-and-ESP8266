#include <stdlib.h>
#include <OneWire.h> 
#define ONE_WIRE_BUS 8
OneWire oneWire(ONE_WIRE_BUS);

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

void loop(){
  float potentiometer = analogRead(A2);
  char buffer[10];
  String value = dtostrf(potentiometer, 4, 1, buffer);
  updateData(value);
  delay(6000);
}

void updateData(String value){
  String cmd = "AT+CIPSTART=\"TCP\",\""; //prepare get string
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  delay(2000);
  if(Serial.find("Error")){
    return;
  }
  cmd = GET;
  cmd += value;
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
    if(Serial.find(">")) {
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
