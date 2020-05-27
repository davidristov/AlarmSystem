#include <NewTone.h>
#include <NewPing.h>
#include <Keypad.h>

#define buzzer 13
#define trigPin 12
#define echoPin 11
#define G 8
#define B 9
#define C 10
#define max_distance 300

const byte numRows= 4; 
const byte numCols= 4; 
boolean activated = false;
int duration, distance;
boolean enabled = false;
String tmp = "";
String password = "11111";
boolean ring = false;
NewPing sonar(trigPin, echoPin, max_distance);

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
      Serial.print(keyPressed);
    }
    
    if(tmp == password){
      digitalWrite(G, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      enabled = true;
      activated = true;
      Serial.print(enabled);
      tmp = "";
      delay(3000);
    }
    
    if(tmp.length() > 4){
      tmp = "";
    } 
  } 
  
   // clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  distance = sonar.ping_cm();

  Serial.println(distance);
  
  if(distance <= 300 && distance >=10){
    ring = true;
  }
  
  if(ring == true){
  //tone(buzzer, 500); 
  NewTone(buzzer, 500, 0);
  }
  
  char keyPressed = myKeypad.getKey();
  
  if(keyPressed != NO_KEY){
    tmp += keyPressed;
    Serial.print(keyPressed);
  }
  
  if(tmp == password){
    tmp = "";
    enabled = false;
    //noTone(buzzer);
    noNewTone(buzzer);
    ring = false;
  }
}
