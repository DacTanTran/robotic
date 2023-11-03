
#include <Servo.h>
Servo servoSG90;
int st_pos = 0; // khoi tao gia tri goc ban dau cua servo
int end_pos = 45; // gia tri cuoi cua servo

//L298N driver motor

const int ENA = 11;  // kết nối với chân ENA
const int IN1 = 9;  // kết nối với chân IN1
const int IN2 = 8;  // kết nối với chân IN2
const int IN3 = 7;  // kết nối với chân IN3
const int IN4 = 6;  // kết nối với chân IN4
const int ENB = 5;  // kết nối với chân ENB

// Khai báo đối tượng Bluetooth
#include <SoftwareSerial.h>
SoftwareSerial BTserial(13, 12); // RX | TX

char command;
int speed = 0;


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  BTserial.begin(9600);
  servoSG90.attach(4); // Khởi tạo chân kết nối với Servo SG90
  
}


void loop() {

  if (BTserial.available() > 0) {
    command = BTserial.read();
    Stop(); // Khởi tạo với tất cả các động cơ đã tắt
    // Serial.println(command);
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
        case 'u':
        servo_down();
         break;
      case 'U':
        servo_up();
      break;

     
    }
  }
}


void forward() {
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  for (speed = 0; speed < 255; speed++) {
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
  for (speed = 0; speed < 255; speed++) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }
}

void left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  for (speed = 0; speed <= 150; speed++) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1);
  }
}

void right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (speed = 0; speed <= 150; speed++) {
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
void servo_up() {
  for(int angle = st_pos ; angle = end_pos ; angle++)
  {
  servoSG90.write(angle);
  delay(10);
  }
}

void servo_down() {
  for(int angle = end_pos; angle >= st_pos ; angle-=1)
  {
  servoSG90.write(angle);
  delay(10);
  }
}
