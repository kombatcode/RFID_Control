// Загружаем библеотеки
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// контакты
#define LED1 8
#define LED2 7
#define BTM 2
#define SS_PIN 10
#define RST_PIN 9

Servo servo;

MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  servo.attach(0); // сервомоторчик в исходное положение (закрыто)
  pinMode(LED1, OUTPUT);   // 8 пин - выход
  pinMode(LED2, OUTPUT);  // 7 пин - выход
  pinMode(BTM, INPUT_PULLUP); // 2 пин вход
  // Далее мы показываем, что замок готов к работе, включая на 3 секунды 2 светодиода
  digitalWrite(LED1, HIGH); 
  digitalWrite(LED2, HIGH);
  delay(3000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  // гасим
}


// Разрешённый идентификатор Card UID, задаётся после прошивки примера из библиотеки)
byte uidCard[4] = {0xCA, 0xA4, 0x1A, 0x0B};


void loop() {
  // Ожидание
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  // чтение
  if ( !mfrc522.PICC_ReadCardSerial())
    return;

  for (byte i = 0; i < 4; i++) {
    // Если идентификатор не совпадает с заданным номером
    if (uidCard[i] != mfrc522.uid.uidByte[i]) {
      Serial.println("У вас нет доступа");
      digitalWrite(LED2, HIGH); // Нет доступа, начинаем мигать красным светодиодом
      digitalWrite(LED1, LOW);
      delay(1000);
      digitalWrite(LED2, LOW);
      digitalWrite(LED2, HIGH);
      return;
    }else{
      Serial.println("Проходите");
      digitalWrite(LED1, HIGH); // Карточка подошла - милости просим, зелёный лед, дверь открыта)
      digitalWrite(LED2, LOW);
      servo.write(90); // открываем дверь
      delay(10000); // ждём 10 сек, чтобы человек успел пройти
      servo.write(0); // и закрываем
    }
  }
}
