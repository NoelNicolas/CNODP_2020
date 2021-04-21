//Noel Nicolas
//This code takes inputs from an ultrasonic sensor module
//The module is on a servo that rotates 0-180 deg
//The module uses sonar to detect objects from 0-180 deg when the servo moves
//The car moves using sensor data

//    The direction of the car's movement
//  ENA   ENB   IN1   IN2   IN3   IN4   Description
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car reverse
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car turns left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car turns right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car stopped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car stopped
//  LOW   LOW   N/A   N/A   N/A   N/A   Car stopped

#include <Servo.h> //servo for echo location
Servo servo; //servo object

int Echo = A4;
int Trig = A5;

//define L298n module IO Pin
#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6

//variables
#define myspeed 100 //found value through trial and error, higher values had more bumps on the wall
int rightEcho = 0, leftEcho = 0, middleEcho = 0;

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

int getDistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  return (int)pulseIn(Echo, HIGH) / 58;
}

//before execute loop() function, 
//setup() function will execute first and only once
//"Initiate these pins"
void setup() {
  servo.attach(3); //servo is on pin 3
  Serial.begin(9600);     //open serial and set the baudrate 9600 bits per second (default)[can increase if needed]
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);   
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
}

//Main
void loop() {
   servo.write(90); //default position
   delay(500); //delay 500 ms
   middleEcho = getDistance();

   if(middleEcho <=45){ //found value through many bumps on the walls
    stop();
    delay(500);
    servo.write(10); //Looks right
    delay(500);
    rightEcho = getDistance();

    delay(500);
    servo.write(90);
    delay(500);
    servo.write(180); //looks left
    delay(500);
    leftEcho = getDistance();

    delay(500);
    servo.write(90); //returns to middle position
    delay(500);
    if(rightEcho > leftEcho){
      right();
      delay(360);
    }
    else if (rightEcho < leftEcho){
      left();
      delay(360);
    }
    else if((rightEcho <=45) || (leftEcho <=45)){
      back();
      delay(180);
    }
    else {
      forward();
    }
   }
   else{
    forward();
   }
   
   
}
