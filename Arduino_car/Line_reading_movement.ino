//Noel Nicolas
//This code takes inputs from a line tracking module
//The module reads from 3 sensors Left/Middle/Right
//The car moves to the direction of the line

//    The direction of the car's movement
//  ENA   ENB   IN1   IN2   IN3   IN4   Description
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car reverse
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car turns left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car turns right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car stopped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car stopped
//  LOW   LOW   N/A   N/A   N/A   N/A   Car stopped

//Line Tracking Module
#define LineRight !digitalRead(10)
#define LineMiddle !digitalRead(4)
#define LineLeft !digitalRead(2)

//define L298n module IO Pin
#define ENB 5
#define ENA 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

//variables
#define myspeed 200 

void forward(){
  digitalWrite(ENA, myspeed);    //speed of right motor
  digitalWrite(ENB, myspeed);    //speed of left motor
  digitalWrite(IN1, HIGH);    //left motors forward
  digitalWrite(IN2, LOW);     //left motors reverse off
  digitalWrite(IN3, LOW);     //right motors reverse off
  digitalWrite(IN4, HIGH);    //right motors forward on
  Serial.println("Forward");  //send message to serial monitor
}

void back(){
  digitalWrite(ENA, myspeed);
  digitalWrite(ENB, myspeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}

void left(){
  digitalWrite(ENA, myspeed);
  digitalWrite(ENB, myspeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Left");
}

void right(){
  digitalWrite(ENA, myspeed);
  digitalWrite(ENB, myspeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

void stop(){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stopped");
}

//before execute loop() function, 
//setup() function will execute first and only once

void setup() {
  Serial.begin(9600);     //open serial and set the baudrate 9600 bits per second (default)[can increase if needed]
}

//Main
void loop() {
 if(LineMiddle){
  forward();
 }
  else if(LineLeft){
    left();
    while(LineLeft);
  }
  else if(LineRight){
       right();
       while(LineRight);
  }   
}
