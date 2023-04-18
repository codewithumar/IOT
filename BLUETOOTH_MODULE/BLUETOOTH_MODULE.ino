#include <Servo.h>
Servo myservo;

const int Sfront = 90;
const int Sright = 0;
const int Sleft = 180;

int duration = 0;
int distance = 0;
int Ldistance = 0;
int Rdistance = 0;

int threshold = 30;

int vspeed = 140;
int tspeed = 255;
int tdelay = 20;

int IRvalueR = 0;
int IRvalueL = 0;
char t;

#define servo_data 12

#define enA 5
#define enB 6

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

#define UST 4
#define USE 7

#define IRr 2
#define IRl 3

void setup() {
  
  pinMode(IRr,INPUT);
  pinMode(IRl,INPUT);
  
  myservo.attach(servo_data);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(UST,OUTPUT);
  pinMode(USE,INPUT);

  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
  
  digitalWrite(UST, HIGH);

  myservo.write(90);

  Serial.begin(9600);
  delay(2000);
  
}
 int x =0;
void loop() {
  
  if(Serial.available()){
    t = Serial.read();
    Serial.println(t);
  }

  if(t == '7'){
    obstacle();
  }else if(t == '8'){
//    line_following();
  }else if(t == '9' || t == '1' || t == '2' || t == '3' || t == '4'){
    Remote();
  }else{
    stopCar();
  }
  delay(20);
}
void line_following(){
  IRvalueR = digitalRead(IRr);
  IRvalueL = digitalRead(IRl);

  Serial.print("right: ");
  Serial.println(IRvalueR);
  Serial.print("left: ");
  Serial.println(IRvalueL);

    if(IRvalueR == LOW && IRvalueL == LOW)
  {
    forward();
  }

  
  if(IRvalueR == LOW && IRvalueL == HIGH)
  {

      left();

  }
  
  if(IRvalueR == HIGH && IRvalueL == LOW)
  {

    right();
   
  }

  if(IRvalueR == HIGH && IRvalueL == HIGH)
  {
    stopCar();
  }

}
void Remote(){
  if(t == '1'){            //move forward(all motors rotate in forward direction)
    forward();
  }
   
  else if(t == '2'){      //move reverse (all motors rotate in reverse direction)
    backward();
  }
   
  else if(t == '3'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
    right();
  }
   
  else if(t == '4'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
   left();
  }
   
  else if(t == '5'){      //STOP (all motors stop)
    stopCar();
  }
}
void obstacle(){
  distance = distanceCalculation();
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
void Reverse(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(enA,vspeed);
  analogWrite(enB,vspeed);
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
