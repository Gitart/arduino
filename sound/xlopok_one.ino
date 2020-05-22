// Включение и выключение по хлопку
const int sensorD0 = 5;   // Пин Arduino к которому подключен выход D0 датчика
const int diod = 13;      // Пин Arduino к которому подключен светодиод
int diodState = LOW;      // Статус светодиода "выключен"
 
void setup ()
{
  Serial.begin(9600);
  pinMode(diod, OUTPUT); // устанавливаем цифровой пин 2 в режим выхода 
}
 
void loop ()
{
    // получаем сигнал с датчика
    int sensorValue = digitalRead(sensorD0); 

 //если порог громкости достигнут и светодиод был ВЫКЛЮЧЕН
if (sensorValue == 1 && diodState == LOW) {
      Serial.println("Ok");
      digitalWrite(diod, HIGH);   // включаем светодиод
      diodState = HIGH;           // устанавливаем статус светодиода "включен"
      delay(100);                 // небольшая задержка для фильтрации помех
    
}
else {
      // если порог громкости достигнут и светодиод был ВКЛЮЧЕН
      if (sensorValue == 1 && diodState == HIGH)  {
          Serial.println("Выкл");
          digitalWrite(diod, LOW);      // выключаем светодиод
          diodState = LOW;             // устанавливаем статус светодиода "выключен"
          delay(100);                  // небольшая задержка для фильтрации помех
         }
}   
}
