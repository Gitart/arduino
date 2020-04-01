http://developer.alexanderklimov.ru/arduino/button.php
/*
   Получение сигналов с реле
*/

// Инициализация пинов
const int In2     = 4;                // Входной датчик 1
const int In1     = 5;                // Входной датчик 2
const int Relein  = 6;                // Реле входное
const int Releout = 7;                // Реле выходное

// Global variables
int knopka= 0;
int dis   = 0;
int din   = 0;
int stage = 0;
int inr   = 0;

// Настройка
void setup() {
  
  // Входные пины 4 и 5
  pinMode(In1,     INPUT);         // устанавливаем режим работы вывода, как "вход"
  pinMode(In2,     INPUT);         // устанавливаем режим работы вывода, как "вход"

  // Выходные пины 6 и 7
  pinMode(Relein,  OUTPUT);      // устанавливаем режим работы вывода, как "выход"
  pinMode(Releout, OUTPUT);      // устанавливаем режим работы вывода, как "выход"
  pinMode(13, OUTPUT);           // устанавливаем режим работы вывода, как "выход"

  pinMode(1, INPUT_PULLUP);      // Датчик 1
  pinMode(2, INPUT_PULLUP);      // Датчик 2  

  // Скорость чтения порта
  Serial.begin(9600);

  // Внимание !!!!
  // Выключение реле при старте
  // Для включения реле необходимо подать сигнал  - LOW
  // Для выключения реле необходимо подать сигнал - HIGH
  digitalWrite(Relein,HIGH);
  digitalWrite(Releout,HIGH);
}


// Основной цикл
void loop() {
  
  // снимаем показания кнопки
  int sensorVal = digitalRead(2);
  
  // выводим в Serial Monitor
  Serial.println(sensorVal);

  // Помните, что при использовании подтягивающего к питанию резистора, 
  // состояние кнопки инвертировано
  // В не нажатом состоянии кнопка имеет значение HIGH, и LOW при нажатии.
  // При нажатии на кнопку включим светодиод, при отпускании - выключим

  if (sensorVal == HIGH) {
     relemig(Releout);
     Serial.println("Выкл реле");
     digitalWrite(13, LOW);
  } else {
     relemig(Relein);
     Serial.println("Yes signal !вкл реле" );
     digitalWrite(13, HIGH);
  }

 
//   delay(1000);
//   if(digitalRead(In1)==1&&stage==1){
//       digitalWrite(Relein,LOW);
//       digitalWrite(Releout,LOW);
//       delay(500);
//       Serial.println("High");
//       stage=0;
//       
//   }
//  
//   if (digitalRead(In1)==0&&stage==0){
//    
//       digitalWrite(Relein,HIGH);
//       digitalWrite(Releout,HIGH);
//       delay(500);
//       Serial.println("Low");
//       stage=1;
//       
//   }
        
     // 60000=1 min
     delay(60000);
     // digitalWrite(13,HIGH);
     // delay(1000);
     // relemig(Releout);
     // Serial.println(inr);   
     
    // digitalWrite(Relein,LOW);
    // digitalWrite(Releout,HIGH);
    // delay(3000);
    // digitalWrite(Releout,LOW);
}

// Функция включения на время реле по имени
int relemig(int Nam){
  digitalWrite(Nam,  LOW);   // Включение
  delay(1000);
  digitalWrite(Nam,  HIGH);   // Выключение  
  delay(3000);
  return HIGH;
}
