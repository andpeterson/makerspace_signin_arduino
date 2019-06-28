#include "KeypadCode.h"
#include "WiFiCode.h"
#include "StatusCode.h"

KeypadInput KeyPad;

//NINAW10 database("HideYoKidsHideYoWifi", "Hu'sPassword?");
NINAW10 database("BC");

//void ConnectToServer();
//void ConnectToNetwork();
//void PingServer();
//void GETServer(const String&);
void ListenServer();

Status stat(12,13,14,15);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
    
  }
  Serial.println("Start");
  stat.Connecting();
  database.Connect();
  database.PingServer();
  if(ListenToServer(database) != "pong"){
    Serial.print("FAILED"); 
    stat.FailedToConnectToServer();
    //ERROR CHECK IF SERVER NOT FOUND
   while(true);
  }
  Serial.print("PASSED");
}

void loop() {
  // put your main code here, to run repeatedly:
  stat.WaitingInput();
  String ssid = KeyPad.GetInput();
  stat.SendingToServer();
  Serial.println(ssid);
  database.GETServer_SignIn(ssid);
  if(ListenToServer(database) == "Success"){
    stat.SignedIn();
    Serial.print("Success");
  }
  else{
    stat.FailedToSignIn();
  }
  
}
/*
void ChangeStatusLED(int red, int blue, int green){
  
}
*/

String ListenToServer(NINAW10 server){
  String msg;
  while(true){
    msg = server.ListenServer();
    if(msg != ""){
      break;
    }
  }
  Serial.println("Message: " + msg);
  return msg;
}
