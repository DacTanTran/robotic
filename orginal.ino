
#include <Servo.h>
#include <Arduino.h>

// CHANNELS OF TX
#define ch1 2
#define ch2 4

int RCValue, ch1Val, ch2Val;

//L298N driver motor
const int ENA = 11;  // kết nối với chân ENA
const int IN1 = 9;  // kết nối với chân IN1
const int IN2 = 8;  // kết nối với chân IN2
const int IN3 = 7;  // kết nối với chân IN3
const int IN4 = 6;  // kết nối với chân IN4
const int ENB = 5;  // kết nối với chân ENB

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
  // Serial.println(ch1Val);
  // Serial.println(ch2Val);

  if((ch2Val>=1500) && (ch2Val<=1800)) forward();
  else if((ch2Val>=1100) && (ch2Val<=1300))back(); 
  else if((ch1Val<=1400) && (ch1Val>=1100))right();
  else if((ch1Val>=1600) && (ch1Val<=1800))left();

  // // FIXING - TIME/DATE created: 20:55 - 05/11/2023 by ooAkira
  // else if((ch1Val>=1250) && (ch1Val<=1400) && (ch2Val>=1550) && (ch2Val<=1800)) forward_right();
  // else if((ch2Val>=1550) && (ch2Val<=1800) && (ch1Val>=1500) && (ch1Val<=1800)) forward_left();
  // else if((ch2Val>=1150) && (ch2Val<=1300) && (ch1Val>=1250) && (ch1Val<=1350)) back_right();
  // else if((ch2Val>=1150) && (ch2Val<=1300) && (ch1Val>=1650) && (ch1Val<=1750)) back_left();

  else Stop();

}


void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);   
  for (speed=0; speed<=100; speed++) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }

}

void back() {   
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (speed=0; speed<=100; speed++){
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (speed=0; speed<=100; speed++){
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }
}

void right() {  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  for (speed=0; speed<=100; speed++){
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }
}



void forward_right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  for (speed=0; speed<=100; speed++){
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }
}

void forward_left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  for (speed=0; speed<=100; speed++){
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }
}

void back_right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (speed=0; speed<=100; speed++){
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }
}

void back_left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  for (speed=0; speed<=100; speed++){
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }
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
