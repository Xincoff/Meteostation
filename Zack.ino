
#include <DHT11.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
#include "ZackEmot.h"


float svet;
int sensor = 12;


#define DHTPIN 2
#define DHTTYPE DHT11 // Пин, на котром датчик и его тип
DHT11 dht(DHTPIN);
// Инициализовация дисплея lcd(Адрес I2C, кол-во ячеек, кол-во столбцов)

uint32_t timer, timer2; // Таймер для многопоточности (на данный момент не реализован)

const int bufsize = 5;
int buf[bufsize];
int bufindex = 0;
int buftrigg = 1;

void setup() 
{
  Serial.begin(9600);

  pinMode(sensor, INPUT);
  
  Serv.attach(9);
  Serv.write(60); // Серва

  pinMode(sensor, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, cels);
  lcd.createChar(1, proc);
  lcd.createChar(2, rot);
  lcd.createChar(3, zk);
  lcd.createChar(4, up);
  lcd.createChar(5, down); // Объявление доп. символов

  
  lcd.setCursor(4, 0);
  lcd.print("Zack");
  lcd.setCursor(5, 1);
  lcd.print("P2v.1.4");
  lcd.setCursor(15, 1);
  lcd.write(3);
  delay(2000);
  lcd.clear(); // Начальная заставка

  lcd.setCursor(6,1);
  lcd.write(0);
  lcd.setCursor(6,0);
  lcd.write(1);
  lcd.setCursor(0,0);
  lcd.print("Hum: ");
  lcd.setCursor(0,1);
  lcd.print("Tem: ");
  lcd.setCursor(15, 1);
  lcd.write(3); // Просто надписи на экране
  
}

void loop() 
{
  int val = !digitalRead(sensor);
  Serial.print("Датчик: ");
  Serial.println(val);

  svet = analogRead(1); // Фоторезистор на 1 аналоговом пине
  svet = map(svet, 0, 1023, 0, 100);

  if (val == buftrigg)
  {
    buf[bufindex] = val;
    bufindex = (bufindex + 1);
    delay(1500);
  }
  else if (val == 0)
  {
    for (int i = 0; i < bufsize; i++) 
    {
      buf[i] = 0; // Заполняем буфер нулями
    }
  bufindex = 0;
  Interface();
  }

  if (bufindex >= bufsize && val == 0) 
  {
    for (int i = 0; i < bufsize; i++) 
    {
      buf[i] = 0; // Заполняем буфер нулями

    }
  bufindex = 0;
  Interface();
  }
  else if (bufindex < bufsize || val == 0)
  {
    Interface();
  }
  else if (bufindex = bufsize)
  {
    lcd.noBacklight();
    Serv.write(0);
    Serial.print("Готово");
  }
  Serial.print("Индекс: ");
  Serial.println(bufindex);
  printBuffer();

}







void printBuffer() {
  Serial.print("Buffer: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(buf[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void Interface()
{
  int rnd = random(0, 15); // Реакции Зака пока через рандом (кроме сна)
  lcd.setCursor(4,0);
  int h = 0; //dht.readHumidity();
  int t = 0; //dht.readTemperature();
  lcd.print(h);
  lcd.setCursor(4,1);
  lcd.print(t); // Считывание и вывод влажности с температурой
  //Serial.println(svet); // Для точности измерений, сопротивление фоторезистора

  if (h < 40)
  {
    lcd.setCursor(7, 0);
    lcd.write(4);
  }
  else if (h > 50)
  {
    lcd.setCursor(7, 0);
    lcd.write(5);
  }
  else
  {
    lcd.setCursor(7, 0);
    lcd.print(" ");
  }
 // Рекомендации по Влажности (Стрелки вниз и вверх)

  if (t < 20)
  {
    lcd.setCursor(7, 1);
    lcd.write(4);
  }
  else if (t > 25)
  {
    lcd.setCursor(7, 1);
    lcd.write(5);
  }// Рекомендации по Температуре (Стрелки вниз и вверх)


  for (int i; i < 4; i++)
  {
    int a[3];
    a[i] = svet;
    if (i == 3)
    {
     
      int baza = (a[0] + a[1] + a[2]) / 3;
      Serial.println(baza);
      Serial.println(a[0]);
      Serial.println(a[1]);
      Serial.println(a[2]);
    }
  }


  
  if (svet >= 95)
  {
    Sleep();// Сон, значения фоторезистора больше необходимых
  }
  else if (svet < 95)
  {
    Serv.write(60);
    lcd.backlight();
    if (rnd == 1)
    {
      for (int i = 2; i < 3; i++)
      {
        Blink(); // Моргание
      }
    }
    if (rnd == 2)
    {
      Surprise(); // Удивление
    }
    if (rnd == 3)
    {
      Peeping(); // Подглядывание
    }
    if (rnd == 4)
    {
      Yawning();  // Зевание
    }
    if (rnd >= 5)
    {
      Standart(); // Стандартная эмоция
    }
  }
}