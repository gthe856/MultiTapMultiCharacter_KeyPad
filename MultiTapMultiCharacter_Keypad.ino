#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char keys[ROWS][COLS] = {
                          {'1','2','3'},
                          {'4','5','6'},
                          {'7','8','9'},
                          {'*','0','#'}
                          };
char characterMap[ROWS*COLS][4] = {{'A','B','C','1'}, // '1'
                                  {'D','E','F','2'}, // '2'
                                  {'G','H','I','3'}, // '3'
                                  {'J','K','L','4'}, // '4'
                                  {'M','N','O','5'}, // '5'
                                  {'P','Q','R','6'}, // '6'
                                  {'S','T','U','7'}, // '7'
                                  {'V','W','Y','8'},// '8'
                                  {'Z',' ',' ','9'}, // '9'
                                  {'*','+',' ',' '}, // '*'
                                  {' ','0',' ',' '},// '0'
                                  {'#','$',' ',' '}/* '#'*/};

byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {6, 5, 4}; 

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int keyCount; char prevChar; long startTime;boolean stateCapital = false;// Used to increase the char if multipressed
String inputMsg="";

void setup() {
    Serial.begin(115200);
    startTime = millis();
    keyCount = 0;
}

void loop() {
  char customKey = kpd.getKey();
  // Get the Key input
    
  if (customKey){
    // If matrix key pressed is a character
    char inputChar = keyPressed(customKey); 
      if (millis() - startTime < 500){
          // Do nothing as time out hasn't been reached
      }
      else{
          if (millis() - startTime < 2500){
            // Reset the input msg string after a 2.5 second timeout
            inputMsg = "";
          }
          else{
            inputMsg = inputMsg + inputChar;  
          } 
          Serial.println(inputMsg);    
      }   
    }  
}   

char keyPressed(char inputChar){
  int locCharacterMap; // Location of the character in the keyMap
  if (inputChar == prevChar && millis() - startTime < 500){
    // Change the character based on how quick in succession the key press was
    if (keyCount >=4){
      // Reset when at equal or greater than 4
     keyCount = 0;
    }
    else{
      keyCount++;  
    }
        
  }
  else{
    keyCount = 0;  
  }
  prevChar = inputChar;
  if (inputChar == '1'){
    locCharacterMap =0;
  }
  else if (inputChar == '2'){
    locCharacterMap =1;
  }
  else if (inputChar == '3'){
    locCharacterMap =2;
  }
  else if (inputChar == '4'){
    locCharacterMap =3;
  }
  else if (inputChar == '5'){
    locCharacterMap =4;
  }
  else if (inputChar == '6'){
    locCharacterMap =5;
  }
  else if (inputChar == '7'){
    locCharacterMap =6;
  }
  else if (inputChar == '8'){
    locCharacterMap =7;
  } 
  else if (inputChar == '9'){
    locCharacterMap =8;
  }
  else if (inputChar == '*'){
    locCharacterMap =9;
  }
  else if (inputChar == '0'){
    locCharacterMap =10;
  }
  else if (inputChar == '#'){
    locCharacterMap =11;
  }
  // Reset the time out startTime
  startTime = millis();
  
  if (characterMap[locCharacterMap][keyCount] == '$'){
    // If this is selected it sets the char to upper or lower case
    stateCapital = !stateCapital;
  }
  if (stateCapital){
    if(characterMap[locCharacterMap][keyCount]>='A' && characterMap[locCharacterMap][keyCount]<='Z'){
      return toLowerCase(characterMap[locCharacterMap][keyCount]);
    }
    else if((characterMap[locCharacterMap][keyCount]>='a' && characterMap[locCharacterMap][keyCount]<='z')){
      return toUpperCase(characterMap[locCharacterMap][keyCount]);
    }
    else{
      return characterMap[locCharacterMap][keyCount];  
    }
  }
    else{
      return characterMap[locCharacterMap][keyCount];  
    }
}
