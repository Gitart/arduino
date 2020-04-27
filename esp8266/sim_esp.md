## Загрузка кода на ESP8266

[По материалам](http://wikihandbk.com/wiki/ESP8266:%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D1%8B/%D0%9A%D0%B0%D0%BA_%D1%83%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D1%8F%D1%82%D1%8C_%D1%83%D1%81%D1%82%D1%80%D0%BE%D0%B9%D1%81%D1%82%D0%B2%D0%B0%D0%BC%D0%B8_%D1%87%D0%B5%D1%80%D0%B5%D0%B7_%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D0%BD%D0%B5%D1%82)

[Примеры использования](http://wikihandbk.com/wiki/ESP8266:%D0%A1%D0%BE%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D0%BD%D0%B8%D0%B5)







Подключив ESP8266 к программирующему устройству одним из способов, описанных выше, откройте IDE Arduino и 
кликните по Инструменты > Плата > Generic ESP8266 Module (Tools > Board > Generic ESP8266 Module).

Примечание:   
Если вы еще не установили в IDE Arduino ядро для чипа ESP8266, то о том, как это сделать, написано в этом руководстве (в разделе «Installing the ESP8266 Platform», что переводится как «Установка ядра ESP8266»). Установив ядро, вернитесь сюда. 

Теперь скопируйте в IDE Arduino код ниже и нажмите на кнопку «Загрузка». 
Поменяйте в коде надпись YOUR_SSID на SSID вашей точки доступа WiFi, а также надпись YOUR_PASSWORD на пароль, 
который вы используете для своей точки доступа. Затем скомпилируйте скетч. 

```ino
#include <ESP8266WiFi.h>

const char* ssid     = "YOUR_SSID";  // для SSID точки доступа
const char* password = "YOUR_PASSWORD";  // для пароля к точке доступа

int ledPin = 2; // контакт GPIO2 на ESP8266
WiFiServer server(80);  //  порт веб-сервера

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // подключаемся к WiFi-сети:
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");  //  "Подключение к "
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");");  //  "Подключение к WiFi
                                        //  выполнено"
  // запускаем сервер:
  server.begin();
  Serial.println("Server started");  //  "Сервер запущен"

  // печатаем IP-адрес:
  Serial.print("Use this URL to connect: ");  //  "Используем этот URL 
                                              //  для подключения: "
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // проверяем, подключен ли клиент:
  WiFiClient client = server.available();
  if (!client) {
     return;
  }

  // ждем, когда клиент отправит какие-нибудь данные:
  Serial.println("new client");  //  "новый клиент"
  while(!client.available()){
  delay(1);
  }
  // считываем первую строчку запроса:
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

   // обрабатываем запрос:
   int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 

if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

  // выставляем значение на ledPin в соответствии с запросом:
  //digitalWrite(ledPin, value);
   

  // возвращаем ответ:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");  //  "Тип контента: 
                                              //  text/html "

  client.println("");  //  не забываем это...
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Led pin is now: ");  //  "Контакт светодиода теперь 
                                     //  в состоянии: "


  if(value == HIGH) {
    client.print("On");   //  "Вкл"
  } else {
    client.print("Off");  //  "Выкл"
  }

  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 2 ON<br>");  //  "Кликните тут, чтобы включить светодиод
                 //  на контакте 2"
  client.println("Click <a href=\"/LED=OFF\">here turn the LED on pin 2 OFF<br>");     //  "Кликните тут, чтобы выключить светодиод
                 //  на контакте 2"
  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");  //  "Клиент отключен"
  Serial.println("");
}
```



```ino
/*
  Моргание
  Включает светодиод и держит его в таком состоянии 1 секунду,
  затем выключает светодиод и держит его в таком состоянии 1 секунду,
  затем повторяет эти действия заново.

  У большинства Arduino есть встроенный светодиод. На Uno и Leonardo
  он подключен к 13-ому контакту. Если вы не уверены, есть ли 
  на вашей модели Arduino встроенный светодиод, сверьтесь 

  с документацией на сайте http://arduino.cc
  Скетч не защищен авторскими правами.

  Модифицирован 8 мая 2014 года 
  Скоттом Фитцдеральдом (Scott Fitzgerald)
 */


// блок setup() запускается, когда вы нажимаете на кнопку сброса или подключаете плату к питанию:

void setup() {
  // выставляем 13-ый цифровой контакт в режим вывода данных:
  pinMode(2, OUTPUT);
}


// блок loop() будет работать снова и снова:
void loop() {
  digitalWrite(2, HIGH);   // включаем светодиод 
                           // (т.е. подаем значение HIGH)
  delay(1000);             // ждем секунду
  digitalWrite(2, LOW);    // выключаем светодиод
                           // (т.е. подаем значение LOW)
  delay(1000);             // ждем секунду

}
```


