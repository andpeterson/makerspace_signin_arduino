
/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using the WiFi module.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */


#include <SPI.h>
#include <WiFiNINA.h>

#define SECRET_SSID "BC"
#define SECRET_PASS ""

//#include "arduino_secrets.h" 
IPAddress server(10,12,134,167);
//IPAddress server(192,168,0,134);
//IPAddress server(172,217,14,228);

class NINAW10
{
   private:
      //NETWORK SIGN IN INFO
      char *ssid; //network ssid
      char *pass; // network password
      int keyIndex = 0; //network key Index number (needed only for WEP)
      
      int status = WL_IDLE_STATUS;
      
      //IPAddress server(10,12,52,196);
      
      int server_PORT = 3000;
      
      // Initialize the Ethernet client library
      // with the IP address and port of the server
      // that you want to connect to (port 80 is default for HTTP):
      WiFiClient client;
      
      String IpAddress2String(IPAddress const& ipAddress);
   public:
      bool ready = 0;
      String response = "";
      NINAW10(char *, char *);
      NINAW10(char *);

      String ParseResponse();
      void ConnectToServer();
      void Connect();
      void PingServer();
      void GETServer_SignIn(const String&);
      String ListenServer();

      static void PrintWifiStatus();
};

NINAW10::NINAW10(char *_ssid, char *_pass){
   //store network ssid and password to connect
   ssid = _ssid;
   pass = _pass;
   //Check to see if WiFi module is responding
}

NINAW10::NINAW10(char *_ssid){
   //store network ssid and password to connect
   ssid = _ssid;
   pass = NULL;
   //Check to see if WiFi module is responding
}

void NINAW10::Connect(){
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    //if password exists then netowrk has authentication if not there is no autentication
    if(pass != NULL){
         // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
         status = WiFi.begin(ssid, pass);
      }
      else {
         status = WiFi.begin(ssid);
      }

    // wait 10 seconds for connection:
    delay(10000);
  }
   
   if (WiFi.status() == WL_NO_MODULE) {
      //Serial.println("Communication with WiFi module failed!");
      return;
   }
   Serial.println("Connected to wifi");
   //printWifiStatus();
}

void NINAW10::PingServer(){
   Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, server_PORT)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /ping HTTP/1.1");
    client.println("Host: " + IpAddress2String(server));
    client.println("Connection: close");
    client.println();
  }
}

void NINAW10::GETServer_SignIn(const String& ssid){
   Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, server_PORT)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /signin?simple=true&ssid=" + ssid + " HTTP/1.1");
    client.println("Host: " + IpAddress2String(server));
    client.println("Connection: close");
    client.println();
    ListenServer();
  }
}

String NINAW10::ListenServer(){
   while (client.available()) {
    char c = client.read();
    response += c;
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
    return ParseResponse();
  }
  return "";
}

String NINAW10::ParseResponse(){
  response.remove(0, 198);
  return response;
}

String NINAW10::IpAddress2String(IPAddress const& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3]); 
}

/*static void NINAW10::printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}*/
