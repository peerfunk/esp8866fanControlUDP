  
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define PORT 23
#define UDP_TX_PACKET_MAX_SIZE 16

struct packet{
  int fannumber;
  int number;
};



class WifiConnection{
  private:  
     char* ssid     = "";
     char* password = ""; 
     unsigned int localPort = PORT;
  public:
     bool debug = false;
     IPAddress ip;
     WiFiUDP Udp;
     byte dataBuffer[UDP_TX_PACKET_MAX_SIZE];
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
          this->Udp.begin(localPort);
      }
};
WifiConnection* conn ;
void setup() {
  Serial.begin(115200);
  conn  = new WifiConnection();
  
  for(int i=0; i< 10; i++){
    if (Serial.read()>0){
      Serial.println("Debug Mode ON");
      conn->debug = true;  
    }
    
    delay(500);
  }
  while (conn->debug && !Serial) {
    ;
  }
  conn->MakeConnection();
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  int packetSize = conn->Udp.parsePacket();
   if(packetSize){
    if(conn->debug){
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      printIp(conn->Udp.remoteIP());
      Serial.print(", port ");
      Serial.println(conn->Udp.remotePort());
    }
    conn->Udp.read(conn->dataBuffer,UDP_TX_PACKET_MAX_SIZE);
    packet tmp;
    memcpy(&tmp, conn->dataBuffer,sizeof(tmp));
    changeSpeed(tmp.fannumber, tmp.number);
 }
} 
void printIp(IPAddress ip){
    for (int i =0; i < 4; i++){
      Serial.print(ip[i], DEC);
      if (i < 3)
        Serial.print(".");
    }
}
void changeSpeed(int fanNumber, int fanSpeed){
  if(conn->debug){
    Serial.print("Fan ");
    Serial.print(fanNumber);
    Serial.print(": ");
    Serial.print(fanSpeed);
    Serial.println(";");
  }
  analogWrite(fanNumber,fanSpeed);   
}
