int ena = 5;
int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
int enb = 10;

int speed_A;
int speed_B;


int value_X;
int value_Y;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345";

int value_servo;

byte mang[7];

void setup() 
{
  Serial.begin(9600);
  
  pinMode (ena, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (enb, OUTPUT);
  
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }    
  radio.openReadingPipe(0, diachi);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);  
  radio.startListening();
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với TX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }
  
}

void loop() 
{
  if (radio.available()) 
  {
    radio.read(&mang, sizeof(mang));
    if(mang[0] == 1)
    {
      if (value_X >= 550)      
        forward();
      else if (value_X <= 550) 
        back();
    }
    else if (mang[1] == 1)
    {
      if (value_Y >= 550)      
        left();
      else if (value_Y <= 550) 
        right();  
    }
    else 
    {
      Stop();
    }
  }
}

void forward() { 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  speed_A = map(value_X,550,1023,0,255);
  speed_B = map(value_Y,550,1023,0,255);
  analogWrite (ena, speed_A);
  analogWrite (enb, speed_B);
}



void back() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  speed_A = map(value_X,550,1023,0,255);
  speed_B = map(value_Y,550,1023,0,255);
  analogWrite (ena, speed_A);
  analogWrite (enb, speed_B);
}
  
void left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  speed_A = map(value_X,550,1023,0,255);
  speed_B = map(value_Y,550,1023,0,255);
  analogWrite (ena, speed_A);
  analogWrite (enb, speed_B);
}


void right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  speed_A = map(value_X,550,1023,0,255);
  speed_B = map(value_Y,550,1023,0,255);
  analogWrite (ena, speed_A);
  analogWrite (enb, speed_B);
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite (ena, 0);
  analogWrite (enb, 0);
}
