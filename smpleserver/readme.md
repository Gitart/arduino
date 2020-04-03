## Клиентская часть на Arduino

Итак, давайте для начала разберемся, как вообще послать какой-либо запрос к Web-серверу. Если Вы думаете, что это слишком сложно, то Вы ошибаетесь. Человек так устроен, что просто не способен создавать что-то невообразимое, в чем он сам же не смог разобраться.
В нашем распоряжении имеется устройство на базе Arduino с которого необходимо отправить запрос на WEB-сервер. Инициатором обмена данными обычно выступает браузер, в нашем случае – Arduino. Web-сервер никому и никогда просто так ничего не пошлет, чтобы он что-нибудь отправил клиенту надо, чтобы клиент его об этом попросил. Простейший HTTP запрос может выглядеть, например, так:

```
GET http://www.php.net/ HTTP/1.0\r\n\r\n
GET - тип запроса, тип запроса может быть разным, например POST, HEAD, PUT, DELETE.
http://www.php.net/ - URI от которого мы хотим получить хоть какую-нибудь информацию.
HTTP/1.0 - тип и версия протокола, который мы будем использовать в процессе общения с сервером.
\r\n - конец строки, который необходимо повторить два раза.
```

В нашем случае запрос к серверу выглядит следующим образом:

```
GET /add.php?k=asREb25C&t=24.00&h=35.00 HTTP/1.1
Host: site.ru
Connection: close
```

### Скетч программы представлен ниже:

```ino
#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
 
//Константы
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Мак адрес
 
EthernetClient client;
 
//Переменные
unsigned long int timeConn = millis();      // Частота отправки данных о t/h на сервер
float h;                                    // Значение температуры
float t;                                    // Значение влажности
char server[] = "site.ru";
 
/*--------------------------------------------------------------
 Необходимые настройки
 --------------------------------------------------------------*/
void setup()
{
  //Старт
  Serial.begin(9600);
  Ethernet.begin(mac);
  dht.begin();
}
/*--------------------------------------------------------------
 Основное тело программы
 --------------------------------------------------------------*/
void loop()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (millis() - timeConn > 2000) {
    sendData(t,h);
    timeConn = millis();
    Serial.println("CONNECT SERVER: Send temp/hum");
  }
}
/*--------------------------------------------------------------
 Функция отправляет данные о температуре и влажности на 
 WEB сервер.
 --------------------------------------------------------------*/
void sendData(float t, float h) {
  client.connect(server, 80);
  client.print( "GET /add.php?");
  client.print("k=");  // Специальный код, например asREb25C
  client.print("&");
  client.print("t=");
  client.print(t);
  client.print("&");
  client.print("h=");
  client.print(h);
  client.println(" HTTP/1.1");
  client.print( "Host: " );
  client.println(server);
  client.println( "Connection: close" );
  client.println();
  client.println();
  client.stop();
  client.flush();
}
```

Как было сказано выше, в своем устройстве я использовал также и другие датчики, в связи с чем скетч моего устройства выглядит следующим образом:

```ino
/*--------------------------------------------------------------
 Программа:    Arduino Home Server 
 Автор:       С.С. Гранкин, http://www.factoblog.ru
 --------------------------------------------------------------*/
 
#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
#include <LiquidCrystal.h>
#include <IRremote.h>
 
 
//Константы
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7 );
 
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Мак адрес
 
EthernetClient client;
 
//Переменные
long unsigned int lowIn;                  // Время, в которое был принят сигнал отсутствия движения(LOW)    
boolean lockLow = true;                   // Флаг. false = значит движение уже обнаружено, true - уже известно, что движения нет
boolean takeLowTime;                      // Флаг. Сигнализирует о необходимости запомнить время начала отсутствия движения
boolean PIR = false;                      // Вкл./Выкл. датчик движения
unsigned long int timeConn = millis();    // Частота отправки данных о t/h на сервер
unsigned long int sendSens = millis();    // Частота отправки данных о датчиках на сервер
int h;                                    // Значение температуры
int t;                                    // Значение влажности
int codeLCD = 0;                          // Код для LCDisplay()
boolean REBOOT = true;                    // Перезагрузка (не менять!)
IRrecv irrecv(19);                        // Пин, к которому подключен приемник
decode_results results;
char server[] = "site.ru";
byte load[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte gradus[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
 
/*--------------------------------------------------------------
 Вводим необходимые настройки
 --------------------------------------------------------------*/
void setup()
{
  //Пины
  pinMode(3, OUTPUT);            // Подсветка LCD
  pinMode(14, OUTPUT);           // Реле-1
  pinMode(18, INPUT);            // Датчик движения
 
  //Значения
  digitalWrite(14, HIGH);         // Отключаем реле-1
 
  //Старт
  Serial.begin(9600);
  irrecv.enableIRIn();
  Ethernet.begin(mac);
  dht.begin();
  lcd.begin(16, 2);
  lcd.createChar(0,load);
  lcd.createChar(1,gradus);
  display("Calibrating PIR","sensor - 10 sec.");
  digitalWrite(3, HIGH);
  lcd.clear();
  for(int i = 0; i < 16; i++) {
    lcd.setCursor(0,0);
    lcd.print("Calibrating PIR");
    lcd.setCursor(i,2);
    lcd.write(byte(0));
    delay(1500);
  }
  digitalWrite(3, LOW);
  //Приветствие LCD
  display("Arduino Server","Status: is RUN");
 
}
/*--------------------------------------------------------------
 Основное тело программы
 --------------------------------------------------------------*/
void loop()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  motion(PIR);
  if (millis() - sendSens > 120000 || REBOOT==true) {
    sensor(PIR, REBOOT);
    sendSens = millis();
    display("CONNECT SERVER","Sending data");
  }
  if (millis() - timeConn > 14400000 || REBOOT == true) {
    sendData(t,h);
    timeConn = millis();
    REBOOT = false;
    display("CONNECT SERVER","Send temp/hum");
  }
  LCDispay(codeLCD);
  if (irrecv.decode(&results)) {
    switch (results.value) {
    case 16738455: // 1
      LCDispay(0);
      codeLCD = 0;
      break;
 
    case 16750695: // 2
      LCDispay(1);
      codeLCD = 1;
      break;
 
    case 16712445: //ОК
      digitalWrite(3, HIGH);
      delay(1500);
      digitalWrite(3, LOW);
      break;
 
    case 16728765: //*
      PIR = true;
      display("MOTION SENSOR","Status: ON");
      break;
 
    case 16732845: //#
      PIR = false;
      lockLow = true; 
      digitalWrite(14, HIGH);
      display("MOTION SENSOR","Status: OFF");
      break;
    }
    irrecv.resume(); 
  }
 
}
/*--------------------------------------------------------------
 Функция вывода информации на LCD KeyPad Shield
 Принемает параметр id.
 --------------------------------------------------------------*/
void LCDispay(int id) {
  switch(id) {
  case 1:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rele-1:OFF Rele-2:ON");
    lcd.setCursor(0,2);
    lcd.print("Light:1950");
    break;
 
  default:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(5,0);
    lcd.print(t);
    lcd.write(byte(1));
    lcd.setCursor(9,0);
    lcd.print("Hum:");
    lcd.setCursor(13,0);
    lcd.print(h);
    lcd.print("%");
    lcd.setCursor(0,2);
    lcd.print("Motion:");
    if (PIR == true) {
      lcd.print("ON");
      lcd.setCursor(7,2);
    } 
    else {
      lcd.print("OFF");
      lcd.setCursor(8,2);
    }
    break;
  }
}
/*--------------------------------------------------------------
 Функция отправляет данные о сотоянии датчиков, реле и тд.
 на WEB сервер.
 --------------------------------------------------------------*/
void sensor(int p1, int rb) {
  client.connect(server, 80);
  client.print( "GET /add.php?");
  client.print("k="); // Специальный код, например asREb25C
  client.print("&");
  client.print("p1=");
  client.print(p1);
  client.print("&");
  client.print("rb=");
  client.print(rb);
  client.print("&");
  client.print("ram=");
  client.print(freeRam());
  client.println(" HTTP/1.1");
  client.print( "Host: " );
  client.println(server);
  client.println( "Connection: close" );
  client.println();
  client.println();
  client.stop();
  client.flush();
}
/*--------------------------------------------------------------
 Функция датчика движения (PIR-sensor)
 --------------------------------------------------------------*/
void motion(int PIR) {
 
  if (PIR==true) {
    if(digitalRead(18) == HIGH) {
      if(lockLow) {
        lockLow = false;     
        digitalWrite(14, LOW);
        display("MOTION DETECTED","RELE-1 is ON");
        Serial.println(lowIn);
        Serial.println("MOTION DETECTED RELE-1 is ON");
      }        
      takeLowTime = true;
    } 
    else {      
      if(takeLowTime) {
        lowIn = millis();
        takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > 5000) { 
        lockLow = true;               
        digitalWrite(14, HIGH);
        display("MOTION FINISH","RELE-1 is OFF");
        Serial.println(lowIn);
        Serial.println("MOTION FINISH RELE-1 is OFF");
      }
    }
  }
}
/*--------------------------------------------------------------
 Функция отправляет данные о температуре и влажности на 
 WEB сервер.
 --------------------------------------------------------------*/
void sendData(float t, float h) {
  client.connect(server, 80);
  client.print( "GET /add.php?");
  client.print("k="); // Специальный код, например asREb25C
  client.print("&");
  client.print("t=");
  client.print(t);
  client.print("&");
  client.print("h=");
  client.print(h);
  client.println(" HTTP/1.1");
  client.print( "Host: " );
  client.println(server);
  client.println( "Connection: close" );
  client.println();
  client.println();
  client.stop();
  client.flush();
}
/*--------------------------------------------------------------
 Функция вывода информации на LCD KeyPad Shild
 Принемает параметр title1 - первая строка (max 16 символов),
 title2 - вторая сторока.
 --------------------------------------------------------------*/
void display(String title1, String title2) {
  lcd.clear();
  lcd.setCursor(0,0);
  digitalWrite(3, HIGH);
  lcd.print(title1);
  lcd.setCursor(0,2);
  lcd.print(title2);
  delay(1600);
  digitalWrite(3, LOW);
}
/*--------------------------------------------------------------
 Функция выводит количество свободных байт RAM
 --------------------------------------------------------------*/
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
```

## Серверная часть

Наше устройство на базе Arduino будет посылать на сервер различные данные с разной периодичностью, сделано это для того, чтобы просто не засорять базу данных MySQL излишней информацией. Для примера установим, что данные о состоянии датчиков (датчиков движения, реле и тд) буду отправляться с периодичностью в 2 мин., а данные о температуре и влажности каждые 4 часа. 
Арендовать полноценный Web сервер мы, конечно, не будем, потому что это дорого, да и попросту неразумно, обойдемся услугой хостинга. Хостинг – это не компьютер и не программа, а услуга по предоставлению вебмастеру для его сайта места на своих серверах. Требования к хостингу минимальны: php не ниже 5.3, MySQL с субд.

Код серверной части прикреплен к данной статье. Для удобства он разбит на несколько файлов:

```
/system/core.php – «ядро» нашего сервера, здесь прописываются данные для подключения к базе данных.
/system/functions.php – здесь содержатся различные пользовательские функции, которые нам понадобятся при работе.
/style/ - стили CSS.
.htaccess – Содержит настройки для сервера. По умолчанию выставлен часовой пояс +3 (Москва).
_sever.sql – дамп БД. Данный файл необходимо импортировать в базу данных.
Index.php – наш главный файл (страница), который будет выводить информацию о состоянии датчиков.
Add.php – данный файл будет принимать и обрабатывать данные от Arduino.
```

Для того, чтобы только наше устройство могло отправлять данные на сервер, мы в GET-запросе будем передавать специальный код (ключ), как бы подтверждая тот факт, что данные действительно передает Arduino.

## Заключение

В статье я не коснулся вопроса, как обрабатывать ответ от сервера (если мы хотим управлять устройством через интернет), сделал я так потому, что наша серверная часть никак не защищена, т.е. любой желающий может зайти на сайт и посмотреть информацию о датчиках движения и т.д. В связи с этим, необходимо организовывать полноценную аунтификацию на PHP и MySQL, а это уже никак не подходит под тематику данного ресурса.

Всем, кто захочет собрать нечто подобное самостоятельно, я желаю удачи! Задавайте свои вопросы в комментариях, с радостью на них отвечу. 
