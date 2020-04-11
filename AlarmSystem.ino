#include <Keypad.h>
#define buzzer 13
#define trigPin 12
#define echoPin 11
#define G 8
#define B 9
#define C 10

const byte numRows= 4; 
const byte numCols= 4; 
boolean activated = false;
int duration, distance;
boolean enabled = false;
String tmp = "";
String password = "22222";
boolean ring = false;

char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {7,6,5,4}; 
byte colPins[numCols]= {3,2,1,0}; 
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup(){
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  Serial.begin(9600);
}

void loop(){

  while(enabled == false){
    digitalWrite(G, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    char keyPressed = myKeypad.getKey();
    
    if(keyPressed != NO_KEY){
      tmp += keyPressed;
    }
    
    if(tmp == password){
      digitalWrite(G, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      enabled = true;
      activated = true;
      Serial.print(enabled);
      tmp = "";
    }
    
    if(tmp.length() > 4){
      tmp = "";
    } 
  } 
  
   // cleartrigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

   // read movement
  duration = pulseIn(echoPin, HIGH);

   // calculate distance in cm
  distance = (duration/2) / 29.1;
  
  if(distance <= 100 && distance >=0){
    ring = true;
  }
  
  if(ring == true){
   tone(buzzer, 1000); 
  }
  
  char keyPressed = myKeypad.getKey();
  
  if(keyPressed != NO_KEY){
    tmp += keyPressed;
  }
  
  if(tmp == password){
    tmp = "";
    enabled = false;
    noTone(buzzer);
    ring = false;
  }
}
