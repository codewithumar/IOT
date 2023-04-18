#include <Servo.h>

Servo myservo;

#define servo_data 12


const int Sfront = 90;
const int Sright = 0;
const int Sleft = 180;

#define enA 5
#define enB 6

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

#define UST 4
#define USE 7

long duration;
int distance;
int Ldistance =0;
int Rdistance =0;

int threshold = 30;

int vspeed = 140;
int tspeed = 255;
int tdelay = 20;

void setup() {

  myservo.attach(servo_data);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(UST,OUTPUT);
  pinMode(USE,INPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);

  digitalWrite(UST, HIGH);

  myservo.write(90);
  
  Serial.begin(9600);

  delay(2000);

}

void loop() {

 distance = distanceCalculation();
  // Prints the distance
Serial.print("Distance: ");
Serial.println(distance);

  if(distance > threshold){
     forward();
  }else{
     stopCar();
     myservo.write(0);
     delay(500);
     Rdistance = distanceCalculation();

     myservo.write(180);
     delay(500);
     Ldistance = distanceCalculation();
     
     myservo.write(90);
     
     if(Rdistance < Ldistance){
      left();
      delay(400);
     }else{
      right();
      delay(400);
     }
     
  }
delay(30);
}

void forward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
    
  analogWrite(enA,vspeed);
  analogWrite(enB,vspeed);
  
  delay(tdelay);
}

void backward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
    
  analogWrite(enA,vspeed);
  analogWrite(enB,vspeed);
  
  delay(tdelay);
}

void right(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
    
  analogWrite(enA,tspeed);
  analogWrite(enB,tspeed);

  delay(tdelay);
}

void left(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  analogWrite(enA,tspeed);
  analogWrite(enB,tspeed);
  
  delay(tdelay);
}
void stopCar(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  analogWrite(enA,0);
  analogWrite(enB,0);
}

int distanceCalculation(){
  //clear trig
digitalWrite(UST, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(UST, HIGH);
delayMicroseconds(10);

digitalWrite(UST, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(USE, HIGH);

// Calculating the distance
distance = duration * 0.034 / 2;

return distance;
}

//int LRcheck(){
//  
//  Rdistance= pulseIn
//  
//}
