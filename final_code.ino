#include <ESP8266WiFi.h>

String apiWritekey = "LPM9CIZQ0H6G4WT9"; 
const char* ssid = "OnePlus 6T";
const char* password = "bilwa1234" ;

const char* server = "api.thingspeak.com";
float resolution=3.3/1023;
const int s0 = D4;
const int s1 = D5;
const int s2 = D6;
const int s3 = D7;
const int out = D8;  
int red = 0; 
int green = 0;
int blue = 0; 
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
}

void loop() {
  float temp = ((analogRead(A0) * resolution) * 100);
  color(); 
  Serial.print("R Intensity:");
    Serial.print(red, DEC);
   Serial.print(" G Intensity: "); 
   Serial.print(green, DEC); 
   Serial.print(" B Intensity : ");
    Serial.print(blue, DEC);  
    if (red > blue && red > green && red < 255){     
      Serial.println(" - (Red Color)");     
    }  
   else if (blue > red && blue > green)  
   {     Serial.println(" - (Blue Color)");     }  
   else if (green > red && green > blue) 
   {     Serial.println(" - (Green Color)");     }   
 else{  Serial.println();    } 
 delay(300); 

  if (client.connect(server,80)) {
    String tsData = apiWritekey;
    tsData +="&field1=";
    tsData += String(red);
    tsData +="&field2=";
    tsData += String(green);
    tsData +="&field3=";
    tsData += String(blue);
    tsData += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
    Serial.print("Temperature: ");
    Serial.print(temp);
    if(temp>30 || temp<15)
    { 
      Serial.println("Plant is not healthy");
    }
    else{
      Serial.println("Plant is healthy");
    }
    Serial.print("Red:");
    Serial.print(red);
    Serial.print("Green:");
    Serial.print(green);
    Serial.print("Blue:");
    Serial.print(blue);
    Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();

  Serial.println("Waiting to upload next reading...");
  Serial.println();
  delay(15000);
}
void color() 
{  
 digitalWrite(s2, LOW);
 digitalWrite(s3, LOW);    
//count OUT, pRed, RED
 red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
 //red=map(red,25,72,0,255);  
 digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE   
 blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
 //blue=map(blue,30,90,0,255); 
 digitalWrite(s2, HIGH);    //count OUT, pGreen, GREEN   
 green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
 //green=map(green,25,70,0,255); 
 }
