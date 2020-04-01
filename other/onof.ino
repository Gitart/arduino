/*
   Данный код демонстрирует переключение режимов работы при помощи кнопки
   Для удобства используется библиотека отработки нажатий кнопки
*/

#define PIN 3              // кнопка подключена сюда (PIN --- КНОПКА --- GND)
#define MODE_AM 5          // количество режимов (от 0 до указанного)
#include "GyverButton.h"

// моя библиотека для более удобной работы с кнопкой
// скачать мождно здесь https://github.com/AlexGyver/GyverLibs
GButton butt1(PIN);       // создаём нашу "кнопку"
byte mode = 0;            // переменная режима

void setup() {
     Serial.begin(9600);
}


void loop() {
   butt1.tick();             // обязательная функция отработки. Должна постоянно опрашиваться
  
   if (butt1.isPress()) {    // правильная отработка нажатия с защитой от дребезга
      // увеличиваем переменную номера режима. Если вышла за количество режимов - обнуляем
      if (++mode >= MODE_AM) mode = 0;
  }
   
  // всё переключение в итоге сводится к оператору switch
  switch (mode) {
    case 0: task_0();
      break;
    case 1: task_1();
      break;
    case 2: task_2();
      break;
    case 3: task_3();
      break;
    case 4: task_4();
      break;
  }
}
// наши задачи, внутри функций понятное дело может быть всё что угодно
void task_0() {
     Serial.println("Task 0");
}

void task_1() {
     Serial.println("Task 1");
}

void task_2() {
     Serial.println("Task 2");
}

void task_3() {
     Serial.println("Task 3");
}

void task_4() {
     Serial.println("Task 4");
}
