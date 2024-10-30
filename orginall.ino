#include <Servo.h>
#include <Arduino.h>

// CHANNELS OF TX
#define ch1 2
#define ch2 4

int ch1Val, ch2Val, Speed=225;

//L298N driver motor
const int ENA = 5;  // kết nối với chân ENA
const int IN1 = 6;  // kết nối với chân IN1
const int IN2 = 7;  // kết nối với chân IN2
const int IN3 = 8;  // kết nối với chân IN3
const int IN4 = 9;  // kết nối với chân IN4
const int ENB = 10;  // kết nối với chân ENB

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);

  Serial.begin(9600);
}


void loop() {
  ch1Val = pulseIn(ch1, HIGH);
  ch2Val = pulseIn(ch2, HIGH);
  // // CHECK PPM FROM TX
  Serial.println(ch1Val);
  //Serial.println(ch2Val);

  if((ch2Val>=1600) && (ch2Val<=1800)) forward();
  else if((ch2Val>=1300) && (ch2Val<=1500))back(); 
  else if((ch1Val<=1500) && (ch1Val>=1300))right();
  else if((ch1Val>=1600) && (ch1Val<=1800))left();
  else Stop();

}


void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);   

    analogWrite(ENA, Speed);
    analogWrite(ENB, Speed);

}

void back() {   
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

    analogWrite(ENA, Speed);
    analogWrite(ENB, Speed);
 
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

    analogWrite(ENA, Speed);
    analogWrite(ENB, Speed);
}

void right() {  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// void servo_up() {
//   for (pos=0; pos<=45; pos++) { 
//       servoSG90.write(pos);
//       delay(15);
//   }
// }

// void servo_down() {
//   for (pos=45; pos>=0; pos--) {
//       servoSG90.write(pos);
//       delay(15);
//   }
// }
