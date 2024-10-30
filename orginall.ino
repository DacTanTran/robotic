#include <Servo.h>
#include <Arduino.h>

// CHANNELS OF TX
#define ch1 2
#define ch2 4
#define ch6 11

int ch1Val, ch2Val, ch6Val, Speed=225;

#define m1 8  //Right Motor MA1
#define m2 9  //Right Motor MA2
#define m3 6  //Left Motor MB1
#define m4 7  //Left Motor MB2
#define e1 10  //Right Motor e1ble Pin EA
#define e2 5 //Left Motor e1ble Pin EB

//**********5 Channel IR Sensor Connection**********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3 
#define ir5 A4
//*************************************************//

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);

  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch6, INPUT);

  Serial.begin(9600);
}

void loop() {
  ch6Val = pulseIn(ch6, HIGH);
  if (ch6Val <= 1500){ // ON
    doline();
  } else {
    ch1Val = pulseIn(ch1, HIGH);
    ch2Val = pulseIn(ch2, HIGH);
    // // CHECK PPM FROM TX
    //Serial.println(ch1Val);
    Serial.println(ch2Val);

    if((ch2Val>=1600) && (ch2Val<=1800)) forward();
    else if((ch2Val>=1300) && (ch2Val<=1500))back(); 
    else if((ch1Val<=1500) && (ch1Val>=1300))right();
    else if((ch1Val>=1600) && (ch1Val<=1800))left();
    else Stop();
  }
}

void doline(){
  //Reading Sensor Values
  int s1 = digitalRead(ir1);  //Left Most Sensor
  int s2 = digitalRead(ir2);  //Left Sensor
  int s3 = digitalRead(ir3);  //Middle Sensor
  int s4 = digitalRead(ir4);  //Right Sensor
  int s5 = digitalRead(ir5);  //Right Most Sensor
  int speeddoline=150;
  //if only middle sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going forward with full speed 
    analogWrite(e1, speeddoline); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, speeddoline); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }
  
  //if only left sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, speeddoline); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, speeddoline); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }
  
  //if only left most sensor detects black line
  if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, speeddoline); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, speeddoline); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
  }

  //if only right sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
  {
    //going left with full speed 
    analogWrite(e1, speeddoline); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, speeddoline); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if only right most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    //going left with full speed 
    analogWrite(e1, speeddoline); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, speeddoline); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if middle and right sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    //going left with full speed 
    analogWrite(e1, speeddoline); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, speeddoline); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if middle and left sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, speeddoline); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, speeddoline); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  //if middle, left and left most sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, speeddoline); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, speeddoline); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  //if middle, right and right most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //going left with full speed 
    analogWrite(e1, speeddoline); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, speeddoline); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if all sensors are on a black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //stop
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }
}

void forward() {
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
  

  analogWrite(e1, Speed);
  analogWrite(e2, Speed);

}

void back() {   
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH); 

  analogWrite(e1, Speed);
  analogWrite(e2, Speed);
 
}

void left() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);

  analogWrite(e1, Speed);
  analogWrite(e2, Speed);
}

void right() {  
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);

  analogWrite(e1, Speed);
  analogWrite(e2, Speed);
}

void Stop() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);

  analogWrite(e1, 0);
  analogWrite(e2, 0);
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
