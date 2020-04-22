# AP веб-сервера ESP8266 (точка доступа)

 16 декабря 2016 г.
 ### Учебные пособия по IoT, Arduino , код , ESP8266 , Интернет вещей , iot


В этом уроке мы делаем ESP8266 в качестве точки доступа и используем ее для создания веб-сервера.  
Мы видели, как подключиться к WiFi Router и сделать веб-сервер в предыдущем посте .

***Веб-сервер*** - это программа, которая использует HTTP (протокол передачи гипертекста) для предоставления 
пользователям файлов, формирующих веб-страницы, в ответ на их запросы, которые пересылаются HTTP-клиентами их компьютеров.

Чтобы внедрить веб-сервер в ESP, есть два способа, чтобы ваш первый веб-сервер сначала подключился к вашему WiFi-маршрутизатору или сделал ESP точкой доступа.

### Веб-сервер шаг за шагом  
Как мы знаем, все веб-серверы имеют веб-страницу для обслуживания.

### Шаг 1: Создание веб-сервера на ESP8266
ESP может действовать как точка доступа и может подключаться к точке доступа или к обоим.

Сначала мы создаем программу для подключения к точке доступа WiFi (Точка доступа)

Программа для подключения к точке доступа и сделать веб-сервер
Нам нужны эти библиотеки, чтобы сделать веб-сервер.

**ESP8266WiFi.h** требуется для выполнения всех функций, связанных с WiFi, таких как подключение, точка доступа и т. Д.   
**WiFiClient.h** этот файл необходим для отправки запроса в веб-браузер   

### ESP8266WebServer.h он обрабатывает все протоколы HTTP

```ino
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
/// Определите свой SSID и пароль вашего WiFi-маршрутизатора, к которому подключается ESP

//SSID and Password for ESP8266
const char* ssid = "your_ssid";
const char* password = "password";

//SSID and Password for ESP8266
const char* ssid = "your_ssid";
const char* password = "password";
```

Веб-сервер находится на порте 80, вы также можете использовать другие порты, порт HTTP по умолчанию - 80, чтобы открыть веб-страницу с другим номером порта, вы должны ввести номер порта после IP-адреса. Ex. Для порта номер 81 вы должны набрать 192.168.2.2:81 в браузере.

### ESP8266WebServer server(80); 
//Server on port 80

Есть два способа сделать веб-сервер одним: подключиться к горячей точке WiFi или сделать ESP горячей точкой ( Точка доступа ). В этом уроке мы делаем ESP как AP.

### ESP как точка доступа
Вы можете обнаружить, что ESP также виден как горячая точка в предыдущем примере ; Вы можете скрыть его AP (Точка доступа), используя эту команду в начале установки.


WiFi.mode(WIFI_STA);   //This line hides the viewing of ESP as wifi network

В некоторых приложениях вы можете обнаружить, что как точка доступа, так и подключение к маршрутизатору WiFi полезны для настройки конфигурации используемой точки доступа ESP8266 и для отправки данных в облако с использованием подключения WiFi, в этом случае используйте эту команду и оба подключения. Таким образом, вы можете получить доступ к веб-странице ESP с двумя разными IP-адресами.

### WiFi.mode(WIFI_AP_STA);  
//Both hotspot and client are enabled

Третий способ - только точка доступа, по умолчанию все AP и STA включены, чтобы получить только AP, используйте эту команду.

### WiFi.mode(WIFI_AP);         
//Only Access point

Чтобы запустить ESP в качестве точки доступа, вы должны использовать эту простую команду

### WiFi.softAP(ssid, password);  

//Start HOTspot removing password will disable security

Чтобы получить IP-адрес, т.е. назначенный ESP8266 вашим WiFi-роутером, используйте эту команду

IPAddress myIP <strong>=</strong> WiFi<strong>.</strong>softAPIP<strong>();</strong> //Get IP address

## Обработка веб-сервера  
Когда клиент запрашивает веб-страницу, вводя IP-адрес ESP, данные для отправки обрабатываются подпрограммой, и это имя подпрограммы определяется в server.on (путь, имя подпрограммы).

## server.on("/", handleRoot); //Which routine to handle at root location

Пример: если у вас есть две страницы, вы можете определить это

Server.on ( «/», корень); //192.168.2.2 (IP ESP) это корневой каталог
Server.on ( «/ стр.1», FIRST_PAGE); //Аный192.168.2.2/page1 »это первое расположение страницы
Server.on ( «/ страница2», Second_page); //Аный192.168.2.2/page2 »это место на второй странице

## У вас есть три подпрограммы, которые обрабатывают запросы клиентов.

Для запуска сервера используйте эту команду

server.begin();                  //Start server
В основном цикле мы обрабатываем запрос клиента

server.handleClient();          //Handle client requests
Эта подпрограмма вызывается, когда вы вводите IP-адрес в веб-браузере и нажимаете Enter. Эта процедура отправляет тест «привет от esp8266» в веб-браузер.

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

### Полная программа для Hello от esp8266 в качестве точки доступа

```ino
/*
 * Hello world web server
 * circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//SSID and Password to your ESP Access Point
const char* ssid = "ESPWebServer";
const char* password = "12345678";

ESP8266WebServer server(80); //Server on port 80

//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

//===============================================================
//                  SETUP
//===============================================================
void setup(void){
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
 
  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//===============================================================
//                     LOOP
//===============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
```

## Sample Hello world
```ino
/*
 * Hello world web server
 * circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
//SSID and Password to your ESP Access Point
const char* ssid = "ESPWebServer";
const char* password = "12345678";
 
ESP8266WebServer server(80); //Server on port 80
 
//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
 
//===============================================================
//                  SETUP
//===============================================================
void setup(void){
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security
 
  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
 
  server.on("/", handleRoot);      //Which routine to handle at root location
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//===============================================================
//                     LOOP
//===============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
```
### Полученные результаты

После загрузки программы включите Wi-Fi на своем мобильном телефоне и в настройке Wi-Fi «Сканирование горячей точки» вы найдете горячую точку « ESPWebServer », подключенную к ней с паролем « 12345678 », как мы указали в программе. После подключения к горячей точке ESP, откройте веб-браузер на мобильном телефоне и введите IP 192.168.4.1, вы увидите «привет от esp8266!» сообщение. IP-адрес можно найти в последовательном мониторе.
