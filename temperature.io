    #include "DHT.h"
    #define DHTPIN 7 // Тот самый номер пина, о котором упоминалось выше
    // Одна из следующих строк закоментирована. Снимите комментарий, если подключаете датчик DHT11 к arduino
    //DHT dht(DHTPIN, DHT22); //Инициация датчика
    DHT dht(DHTPIN, DHT11);
    void setup() {
      Serial.begin(9600);
      dht.begin();
    }
    void loop() {
      // 2 секунды задержки
      delay(3000); 
      float h = dht.readHumidity();     // Измеряем влажность
      float t = dht.readTemperature();  // Измеряем температуру

      // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
      if (isnan(h) || isnan(t)) {       
          Serial.println("Ошибка считывания");
          return;
      }
      
       Serial.print("Влажность: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Температура: ");
  Serial.print(t);
  Serial.println(" *C "); //Вывод показателей на экран


        
    }


    
