#include "tank-bot.h"

int DELTA_SPEED = 20;
int MAX_SPEED = 255;
#define MAX_DISTANCE 200
 
int TRACE_INTERVAL = 1000;

int motor1ControlPin1 = 8; // pin 2 on L293D
int motor1ControlPin2 = 9; // pin 7 on L293D
int motor1enablePin = 10; // pin 1 on L293D
int motor2ControlPin1 = 13; // pin 15 on L293D
int motor2ControlPin2 = 12; // pin 10 on L293D
int motor2EnablePin = 11; // pin 9 on L293D
int motor1Speed = 0;
int motor2Speed = 0;
int loopCounter = 0;

int triggerPin = 7;
int echoPin = 6;

Motor motor1;
Motor motor2;

void setup() {
    Serial.begin(9600);
    Serial.println("Running Setup");
//    motor1 = {8, 9, 10, 0};
//    motor2 = {13, 12, 11, 0};
    // set all the other pins you're using as outputs:
//    pinMode(motor1.controlPin1, OUTPUT);
//    pinMode(motor1.controlPin2, OUTPUT);
//    pinMode(motor1.enablePin, OUTPUT);
//    
//    pinMode(motor2.controlPin1, OUTPUT);
//    pinMode(motor2.controlPin2, OUTPUT);
//    pinMode(motor2.enablePin, OUTPUT);

    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
  char c='z';
  if(Serial.available()) {
    c=Serial.read();
  }
  //setSpeedForInput(c);
  loopCounter++;
  if (loopCounter % TRACE_INTERVAL == 0) {
   //Serial.print(motor1.motorSpeed);
    //Serial.print(" ");
    //Serial.println(motor2.motorSpeed);
  }
  if (loopCounter % 1000) {
    measureDistance();  
  }
  
}

void setSpeedForInput(char c)
{
    if(isdigit(c)) {
    c=c-'0';
    if(c==0){
      //Serial.println("Received 0");
      stopMotor(&motor1);
      stopMotor(&motor2);
    }else if(c==1){
      //Serial.println("Received 1");
      moveForward(&motor1);
      moveForward(&motor2);
    }else if(c==2){
      //Serial.println("Received 2");
      moveBackwards(&motor1);
      moveBackwards(&motor2);
    } else if(c==3){
      //Serial.println("Received 3");
      moveBackwards(&motor1);
      moveForward(&motor2);
    } else if(c==4) {
      //Serial.println("Received 4");
      moveForward(&motor1); 
      moveBackwards(&motor2);
    }
  }
}

long measureDistance()
{  
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
        Serial.print("duration:");
    Serial.println(duration);
  long distance = (duration/2) / 29.1;
      Serial.print("Distance:");
    Serial.println(distance); 
  return duration;
  
}

void setMotorSpeed(Motor* motor) {
  if(motor->motorSpeed >= 0) {
    digitalWrite(motor->controlPin1, LOW);
    digitalWrite(motor->controlPin2, HIGH);
  } else {
    digitalWrite(motor->controlPin1, HIGH);
    digitalWrite(motor->controlPin2, LOW);
  }
  Serial.print("Analgu write:");
  Serial.println(motor->motorSpeed);
  motor->motorSpeed = constrain(motor->motorSpeed, -1 * MAX_SPEED, 255);
  analogWrite(motor->enablePin, constrain(abs(motor->motorSpeed), 0, MAX_SPEED));
}

void stopMotor(Motor* motor) {
  motor->motorSpeed = 0;
  setMotorSpeed(motor);
}

void moveForward(Motor* motor) {
  motor->motorSpeed = MAX_SPEED;
  setMotorSpeed(motor);
}

void moveBackwards(Motor* motor) {
  motor->motorSpeed = -MAX_SPEED;
  setMotorSpeed(motor);
}

