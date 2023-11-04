
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345"; //Mảng kí tự dạng chuỗi có 6 kí tự
boolean button_F = A0;
boolean button_B = A4;
boolean button_L = A5;
boolean button_R = A3;

int value_F;
int value_B;
int value_L;
int value_R;

int VR_X = A1;
int VR_Y = A2;
int SW = 2;

int value_X;
int value_Y;
int value_SW;

byte mang[7]; //Mảng có 7 phần tử

void setup() 
{
  Serial.begin(9600);

  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }   
  radio.openWritingPipe(diachi);
  radio.setPALevel(RF24_PA_MIN); //Cài bộ khuyết địa công suất ở mức MIN
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);  
  radio.stopListening(); //Cài đặt module là TX
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }

  pinMode(button_F, INPUT_PULLUP);
  pinMode(button_B, INPUT_PULLUP);
  pinMode(button_L, INPUT_PULLUP);
  pinMode(button_R, INPUT_PULLUP);
  pinMode(VR_X, INPUT);
  pinMode(VR_Y, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

void loop() 
{
  value_X = analogRead(VR_X);
  mang[0] = value_X; //Ghi gtbiendoi vào phần tử 0
  Serial.print("X: "); Serial.print(value_X); Serial.print("   ");
  
  value_Y = analogRead(VR_Y);
  mang[1] = value_Y;
  Serial.print("X: "); Serial.print(value_X); Serial.print("   ");

  value_SW = analogRead(SW);
  mang[2] = value_SW; //Ghi gtbiendoi vào phần tử 2
  Serial.print("SW: "); Serial.print(value_SW); Serial.print("   ");
  
  value_F = digitalRead(button_F);
  mang[3] = value_F;
  Serial.print("Giá Trị nút nhấn F: "); Serial.println(value_F);
  radio.write(&mang, sizeof(mang));
  delay(50);

  value_B = digitalRead(button_B);
  mang[4] = value_B;
  Serial.print("Giá Trị nút nhấn B: "); Serial.println(value_B);
  radio.write(&mang, sizeof(mang));
  delay(50);

  value_L = digitalRead(button_L);
  mang[5] = value_L;
  Serial.print("Giá Trị nút nhấn L: "); Serial.println(value_L);
  radio.write(&mang, sizeof(mang));
  delay(50);

  value_R = digitalRead(button_R);
  mang[6] = value_R;
  Serial.print("Giá Trị nút nhấn R: "); Serial.println(value_R);
  radio.write(&mang, sizeof(mang));
  delay(50);
}
