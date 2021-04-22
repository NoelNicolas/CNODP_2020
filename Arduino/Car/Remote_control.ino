/*Noel Nicolas
 * This code uses a remote control to steer the car
 * IR receiver is weak, must stay LOS (behind car) to control car
 */

/*
 * Button          Key Value
 * OK              16712445, 3622325019
 * Up arrow        16736925, 5316027
 * Down arrow      16754775, 2747854299
 * Left arrow      16720605, 1386468383
 * Right arrow     16761405, 55353695
 * 1               16738455
 * 2               16750695
 * 3               16756815
 * 4               16724175
 * 5               16718055
 * 6               16743045
 * 7               16716015
 * 8               16726215
 * 9               16734885
 * 0               16730805
 * *               16728765
 * #               16732845
 */
/*    The direction of the car's movement
ENA   ENB   IN1   IN2   IN3   IN4   Description
HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car forward
HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car reverse
HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car turns left
HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car turns right
HIGH  HIGH  LOW   LOW   LOW   LOW   Car stopped
HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car stopped
LOW   LOW   N/A   N/A   N/A   N/A   Car stopped
*/

#include <IRremote.h>

//Directional and buttons defined
#define FORWARD 16736925
#define BACK    16754775
#define LEFT    16720605
#define RIGHT   16761405
#define STOP    16712445

#define RECV_PIN 12
#define ENB 5
#define ENA 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

//variables
#define myspeed 200
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long first_value;
unsigned long second_value;

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

//"Initiate these pins"
void setup() {
  irrecv.enableIRIn();
  Serial.begin(9600);     //open serial and set the baudrate 9600 bits per second (default)[can increase if needed]
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
  if(irrecv.decode(&results)){
    second_value = millis(); //millis() is a function that reurns a number representing milliseconds since reset
    first_value = results.value;
    Serial.println(first_value);
    irrecv.resume();
    switch(first_value){
      //indentation doesn't matter, just wanted to make it look pretty
      case FORWARD: forward(); break;
      case BACK:    back();    break;
      case LEFT:    left();    break;
      case RIGHT:   right();   break;
      default:                 break;
    }
  }
  else{
    if(millis() - second_value > 500){
      stop();
      second_value = millis();
    }
  }
}
