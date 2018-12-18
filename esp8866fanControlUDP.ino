  
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define MAX_SRV_CLIENTS 1
#define PORT 23
#define UDP_TX_PACKET_MAX_SIZE 16
//WiFiServer server(23);
// WiFiClient serverClients[MAX_SRV_CLIENTS];



struct packet{
  int fannumber;
  int number;
};
WiFiUDP Udp;
class WifiConnection{
private:  
 char* ssid     = "";
 char* password = ""; 
 unsigned int localPort = 8081;

public:   
 IPAddress ip;
 //WiFiServer server(PORT);
 WifiConnection(char* essid,char* pw){
      ssid = essid;
      password = pw;
  }
 WifiConnection(){ }
 void setConnection(char* essid,char* pw){
      ssid = essid;
      password = pw;
 }
 void MakeConnection(){
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      Serial.print("Connecting to ( '");
      Serial.print(ssid);
      Serial.print("' , '");
      Serial.print(password);
      Serial.println("' )");
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected");  
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
   //  this.Udp.begin(localPort);
  }
   
  
};
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
int del=5;
int inByte = 0;
int oldByte =0;
 
void setup() {
  Serial.begin(115200);
  WifiConnection* a = new WifiConnection();
  a->MakeConnection();
  
  //server.begin();
  //server.setNoDelay(true);
 Serial1.print(WiFi.localIP());
  Udp.begin(2626);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  int packetSize = Udp.parsePacket();
   if(packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    byte data2[UDP_TX_PACKET_MAX_SIZE];
    Udp.read(data2,UDP_TX_PACKET_MAX_SIZE);
    packet tmp;
    memcpy(&tmp, data2,sizeof(tmp));
    changeSpeed(tmp.fannumber, tmp.number);
       
 }
  
} 

void changeSpeed(int fanNumber, int fanSpeed){
   
    Serial.print("Fan ");
    Serial.print(fanNumber);
    Serial.print(":");
    Serial.print("");
    Serial.print(fanSpeed);
    Serial.println(";");
    analogWrite(fanNumber,fanSpeed); 
    
}
