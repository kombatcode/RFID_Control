#define led1 2 // Жёлтый лед
#define led2 3 // Красный лед

// Сравнение двух массивов известного размера
bool compareUIDs(uint8_t *in1, uint8_t *in2, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {  // Проходим по всем элементам
    if (in1[i] != in2[i]) return false; // Если хоть один не сошелся - массивы не совпадают
  }
  return true;                          // Все сошлись - массивы идентичны
}


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:

}
