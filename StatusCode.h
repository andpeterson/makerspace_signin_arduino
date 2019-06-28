#ifndef STATUSCODE
#define STATUSCODE

class Status{
  public:
    Status(int, int, int, int);
    void FailedToConnectToWiFi();    //Red
    void FailedToConnectToServer();  //Orange
    void FailedToSignIn();           //Red

    void Connecting();               //Blue
    void WaitingInput();             //Green
    void SendingToServer();          //Blue
    void SignedIn();                 //Green
    static void ButtonAccepted(int);

  private:
    int redPin;
    int greenPin;
    int bluePin;
    int buzzerPin;
    void SetLED(int, int, int);
};

Status::Status(int r, int g, int b, int buzzer){
  redPin = r;
  greenPin = g;
  bluePin = b;
  buzzerPin = buzzer;
}

void Status::SetLED(int r, int g, int b){
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void Status::FailedToConnectToWiFi(){
  SetLED(255,0,0); //RED
}

void Status::FailedToConnectToServer(){
  SetLED(255,127,0); //RED
}

void Status::FailedToSignIn(){
  SetLED(255,0,0); //RED
}

void Status::Connecting(){
  SetLED(0,0,255); //Blue
}

void Status::WaitingInput(){
  SetLED(0,255,127); //Green Blue
}

void Status::SendingToServer(){
  SetLED(0,0,255); //Blue
  pinMode(7, OUTPUT);
  digitalWrite(7, 1);
  delay(50);
  digitalWrite(7,0);
  delay(50);
  digitalWrite(7, 1);
  delay(50);
  digitalWrite(7,0);
  delay(50);
  digitalWrite(7, 1);
  delay(200);
  digitalWrite(7,0);
}

void Status::SignedIn(){
  SetLED(0,255,0); //Green
}

void Status::ButtonAccepted(int pin){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 1);
  delay(50);
  digitalWrite(pin,0);
}

#endif
