 //#include <queue>
//#include <QueueArray.h>
#include <Keypad.h>
#include "StatusCode.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 3

class KeypadInput
{
   private:
      //KEYPAD DEFINITIONS
      const char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
         {'1','2','3'},
         {'4','5','6'},
         {'7','8','9'},
         {'*','0','#'}
      };
      byte keypad_rowPins[4] = {3,4,5,6};
      byte keypad_colPins[3] = {0,1,2};

      Keypad keypad = Keypad( makeKeymap(keys), keypad_rowPins, keypad_colPins, KEYPAD_ROWS, KEYPAD_COLS);
      
   public:
   
      KeypadInput();
      String GetInput();
};

KeypadInput::KeypadInput(){
  
}

String KeypadInput::GetInput(){

  //Keypress buffer
  //std::queue<char> keys_buffer;
  //QueueArray <char> keys_buffer;
  String input;
   
   while(true){
      char key = keypad.getKey();
      Serial.print(key);
      if (key != NO_KEY){
         input += key;
         Serial.println(key);
         Status::ButtonAccepted(7);
         if(input.length() >= 9){
            return input;
         }
      }
   }
}
