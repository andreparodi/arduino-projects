/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v 
 GND to arduino GND
 Echo to Arduino pin 7 
 Trig to Arduino pin 8
 
 This sketch originates from Virtualmix: http://goo.gl/kJ8Gl
 Has been modified by Winkle ink here: http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
 And modified further by ScottC here: http://arduinobasics.blogspot.com.au/2012/11/arduinobasics-hc-sr04-ultrasonic-sensor.html
 on 10 Nov 2012.
 */


#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LightPin 12
#define BuzzPin 10

int ledTriggerDistance = 10; 

long duration, distance; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LightPin, OUTPUT);
 pinMode(BuzzPin, OUTPUT);
}

void loop() {
  /* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
 if (distance >= maximumRange || distance <= minimumRange){
  Serial.println("-1");
 }
 else {
  Serial.println(distance);
 }

 if(distance < 10) {
  digitalWrite(LightPin, HIGH);
 } else {
  digitalWrite(LightPin, LOW);
 }
   
 if(distance < 90) {
  tone(BuzzPin, distance*10, 1000);
 }
 
 //Delay 50ms before next reading.
 delay(50);
}
