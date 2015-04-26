#include <DHT.h>
#include <Servo.h> //используем библиотеку для работы с сервоприводом
Servo servo; //объявляем переменную servo типа Servo
int val;
int soundIn = 5;
int soundLed = 13;
#define DHTPIN 2 // номер пина, к которому подсоединен датчик
// Раскомментируйте в соответствии с используемым датчиком
// Инициируем датчик
//DHT dht(DHTPIN, DHT22);
DHT dht(DHTPIN, DHT11);
float R = 8.314472;
float p = 101325;//Па=1а.т.м.=760мм.рт.ст.
int K = 273;// Кельвины
float Vm = 24.1;
void setup() { 
  //pinMode(6,OUTPUT);
  //digitalWrite(n, LOW);
  Serial1.begin(9600);
  dht.begin();
  servo.attach(10); //привязываем привод к порту 10
}
void loop() {
  // Задержка 1 секунды между измерениями
  delay(100);
  //Считываем влажность
  float h = dht.readHumidity()+4;
  // Считываем температуру
  float t = dht.readTemperature()-2;
  int T = t + K; // из цельсия в кельвины
  // Считывем звук
  bool soundVal = digitalRead(soundIn);
   // Считывем mq7(угарный газ)
  float mq7 = analogRead(A1)*0.01; //CO
  // Считывем mq2
  float mq2 = analogRead(A2)*0.01;//(CH3)3CH
  // Считывем mq4
  float mq4 = analogRead(A3)*0.01;//CH4
    // Проверка удачно прошло ли считывание.
  if (isnan(h) || isnan(t) || isnan(mq7) || isnan(mq2) || isnan(mq4)) {
  Serial1.println("Error");
  return;
  }
//if (Serial1.available())
//{
//val = Serial1.read();
//if (val == 'W' || val == 'w')
//{
 servo.write(90);
 Serial1.print(t,0);Serial1.print(';');
 Serial1.print(h,0);Serial1.print(';');
 Serial1.print(soundVal);Serial1.print(';');
 if (soundVal == 1)
 {
 digitalWrite(soundLed, HIGH);
 servo.write(180);
 }
 else
 {
 digitalWrite(soundLed, LOW);
 servo.write(0);
 }
 Serial1.print(mq7,2);Serial1.print(';');
 Serial1.print(mq2,2);Serial1.print(';');
 Serial1.println(mq4,2);
//} 
//}
}
