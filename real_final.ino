#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Trig 2
#define Echo 3
#include <Servo.h>

int x = 0;
int input = A0;
int state = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;
long duration;
int distance;

void setup() 
{
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Turn counter ");
  lcd.setCursor(0, 1);
  lcd.print(x);
  lcd.print("     =turn  ");

  myservo.attach(4);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}
void loop() 
{
    int counter = digitalRead(A0);
  if (state == 0)
  {
    switch (counter) {

      case 1 : state = 1; lcd.setCursor (0, 1); x = x + 1; lcd.print(x-1); break;
      case 0 : state = 0; break;

    }
  }

  if (counter == LOW) {
    state = 0;
  }
  delay(10);

  digitalWrite(Trig, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo,HIGH);
  distance = duration *0.034 / 2;
  if (distance <= 15)
  {
    myservo.write(0);
    delay(1500);
  }
  else
  {
    myservo.write(80);
  }
}