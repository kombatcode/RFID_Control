#include <MFRC522.h>
MFRC522 rfid(10, 9); // SDA, RST

#define YELLOW_LED 2 // Жёлтый лед
#define RED_LED 3 // Красный лед

// Сравнение двух массивов известного размера
bool compareUIDs(uint8_t *in1, uint8_t *in2, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {  // Проходим по всем элементам
    if (in1[i] != in2[i]) return false; // Если хоть один не сошелся - массивы не совпадают
  }
  return true;                          // Все сошлись - массивы идентичны
}


void setup() {
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
  Serial.begin(9600);
  SPI.begin();      // запуск шины
  rfid.PCD_Init();  // инициализация модуля
  uint32_t IDsetup;
    for (byte i = 0; i < 4; i++) {
      IDsetup <<= 8;
      IDsetup |= rfid.uid.uidByte[i];
    }
    // выведем
    Serial.println("Setup");    
    Serial.println(IDsetup, HEX);
    delay(500);
}


void loop() {
  // если поднесена метка
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // запишем метку в 4 байта
    uint32_t ID;
    for (byte i = 0; i < 4; i++) {
      ID <<= 8;
      ID |= rfid.uid.uidByte[i];
    }
    // выведем
    if (ID != IDsetup) {
      Serial.println("Error");
    } else {
      Serial.println("Success");
      Serial.println(ID, HEX);
      delay(500);
    }
  }  
}
