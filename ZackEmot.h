
#ifndef ZackEmot_h
#define ZackEmot_h
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo Serv;

LiquidCrystal_I2C lcd(0x27,16,2);
byte cels[] = {0x18,0x1B,0x04,0x08,0x08,0x04,0x03,0x00};
byte proc[] = {0x19,0x1A,0x1A,0x04,0x04,0x0B,0x0B,0x13};
byte rot[] = {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E,0x00};
byte zk[] = {0x11,0x0A,0x04,0x1F,0x00,0x19,0x15,0x13};
byte up[] = {0x04,0x0E,0x15,0x04,0x04,0x04,0x04,0x00};
byte down[] = {0x04,0x04,0x04,0x04,0x15,0x0E,0x04,0x00};

void Sleep()
{
  lcd.noBacklight();
  lcd.setCursor(10, 0);
  lcd.print("-_-");
  delay(300);
  lcd.setCursor(10, 0);
  lcd.print("*O*");
  delay(2000);
  lcd.setCursor(10, 0);
  lcd.print("-_-");
  Serv.write(0);
  delay(10000);
  lcd.setCursor(10, 0);
  lcd.print("o_o");
  delay(500); 
}

void Blink()
{
  lcd.setCursor(10,0);
  lcd.print("o_o");
  delay(1000);
  lcd.setCursor(10, 0);
  lcd.print("-_-");
  delay(200);
  lcd.setCursor(10,0);
  lcd.print("o_o");
  delay(100);
  lcd.setCursor(10, 0);
  lcd.print("-_-");
  delay(200);
}

void Surprise()
{
  lcd.setCursor(10,0);
  lcd.print("OoO");
  delay(1000);

  /*Serv.write(40);
  delay(100);
  Serv.write(60);
  delay(100);
  Serv.write(40);
  delay(100);
  Serv.write(60);*/

  lcd.setCursor(10,0);
  lcd.print("o_o");
  delay(500);
}

void Peeping()
{
  lcd.setCursor(10, 0);
  lcd.print("n_n");
  delay(300);
  lcd.setCursor(10, 0);
  lcd.print("O_o");
  delay(2000);
  lcd.setCursor(10, 0);
  lcd.print("o_o");
  delay(500);
}

void Yawning()
{
  lcd.setCursor(10, 0);
  lcd.print("* *");
  lcd.setCursor(11, 0);
  lcd.write(2);
  delay(1200);
  lcd.setCursor(10, 0);
  lcd.print("o_o");
  delay(500);
}

void Standart()
{
  lcd.setCursor(10, 0);
  lcd.print("n_n");
  delay(1500);
}

#endif