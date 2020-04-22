### ESP8266 веб-сервер с веб-страницей HTML  

16 декабря 2016 г.Учебные пособия по IoT, Arduino , код , ESP8266 , Интернет вещей , iot , сервер , веб

В этом руководстве мы создаем веб-сервер ESP8266 с веб-страницей HTML. ESP8266  подключается к сети WiFi, и мы получаем веб-страницу в нашем телефоне и ПК, которая подключена к той же сети WiFi.

В предыдущем уроке мы видели, как сделать ESP8266 точкой доступа и  веб-сервером .

Веб-сервер - это программа, которая использует HTTP (протокол передачи гипертекста) для предоставления пользователям файлов, формирующих веб-страницы, в ответ на их запросы, которые пересылаются HTTP-клиентами их компьютеров.
Чтобы внедрить веб-сервер в ESP, есть два способа, чтобы ваш первый веб-сервер сначала подключился к вашему WiFi-маршрутизатору или сделал ESP точкой доступа.

### Веб-сервер шаг за шагом
Как мы знаем, все веб-серверы имеют веб-страницу для обслуживания. Сначала создайте веб-страницу с использованием HTML и протестируйте ее на своем компьютере.

#### Шаг 1. Создайте красивую веб-страницу
Откройте свой блокнот и начните писать HTML-код. Сохранить как index.htm.

```html
<HTML>
	<HEAD>
		<TITLE>My first web page</TITLE>
	</HEAD>
<BODY>
	<CENTER>
		<B>Hello World.... </B>
	</CENTER>	
</BODY>
</HTML>
```

<HEAD> и <TITLE> используются для указания заголовка страницы, который виден в верхней части браузера.
Тег <CENTER> используется для выравнивания текста по центру, <B> - для выделения текста жирным шрифтом.

### Протестируйте свою веб-страницу
Откройте веб-страницу в веб-браузере. Вы можете заметить, что вверху вы видите заголовок «Моя первая веб-страница». И веб-страница с Hello World ... сообщение.

Чтобы увидеть изменения в вашем HTML-коде, просто измените свою HTML-программу и нажмите «Обновить» в браузере. Это отразится сразу. Таким образом, вы можете проверить свою веб-страницу, а затем развернуть ее на ESP8266. Это экономит ваше много времени.

### HTML веб-страница

### Шаг 2: Создание веб-сервера на ESP8266  
ESP может действовать как точка доступа и может подключаться к точке доступа или к обоим.
Сначала мы создаем программу для подключения к точке доступа WiFi (Точка доступа)
Программа для подключения к точке доступа и сделать веб-сервер
Нам нужны эти библиотеки, чтобы сделать веб-сервер.

**ESP8266WiFi.h** требуется для выполнения всех функций, связанных с WiFi, таких как подключение, точка доступа и т. Д.
**WiFiClient.h**   этот файл необходим для отправки запроса в веб-браузер

### ESP8266WebServer.h он обрабатывает все протоколы HTTP  

```ino
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
```

Определите свой SSID и пароль вашего WiFi-маршрутизатора, к которому подключается ESP

//SSID and Password of your WiFi router
```ino
const char* ssid     = "your_ssid";
const char* password = "password";
```


Веб-сервер находится на порте 80, вы также можете использовать другие порты, порт HTTP по умолчанию - 80, чтобы открыть веб-страницу с другим номером порта, вы должны ввести номер порта после IP-адреса. Ex. Для порта номер 81 вы должны набрать 192.168.2.2:81 в браузере.
```ino
ESP8266WebServer server(80); //Server on port 80
```

Есть два способа сделать веб-сервер одним:   
* подключиться к горячей точке WiFi   
* сделать ESP горячей точкой (Точка доступа).  

Эта команда используется для подключения к вашей точке доступа WiFi. 
Термин Точка доступа (AP) такой же, как Wi-Fi Hot Spot. 
Если сеть открыта, вы можете удалить поле пароля из команды.

```ino
WiFi.begin(ssid, password);     //Connect to your WiFi router
```

После запроса на подключение мы ждем подключения WiFi. После подключения и отключения ESP8266 из-за потери сигнала или по любой другой причине, нет необходимости давать эту команду снова, он попытается подключиться снова автоматически. Это обрабатывается его ОС, вы можете обнаружить некоторые ошибки стека, отображаемые в последовательном мониторе, и эти ошибки происходят из его внутренней ОС.
```ino
// Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
```
Чтобы получить IP-адрес, т.е. назначенный ESP8266 вашим WiFi-роутером, используйте эту команду
```ino
WiFi.localIP();
```

Когда клиент запрашивает веб-страницу, вводя IP-адрес ESP, данные для отправки обрабатываются подпрограммой, и это имя подпрограммы определяется в server.on (путь, имя подпрограммы).
```ino
server.on("/", handleRoot); //Which routine to handle at root location
```

Пример: если у вас есть две страницы, вы можете определить это

```ino
Server.on ( «/», корень); //192.168.2.2 (IP ESP) это корневой каталог
Server.on ( «/ стр.1», FIRST_PAGE); //Аный192.168.2.2/page1 »это первое расположение страницы
Server.on ( «/ страница2», Second_page); //Аный192.168.2.2/page2 »это место на второй странице
```

У вас есть три подпрограммы, которые обрабатывают запросы клиентов.

```ino
server.begin();                  //Start server
```

В основном цикле мы обрабатываем запрос клиента
```ino
server.handleClient();          //Handle client requests
```

Эта подпрограмма вызывается, когда вы вводите IP-адрес в веб-браузере и нажимаете Enter. Эта процедура отправляет тест «привет от esp8266» в веб-браузер.

```ino
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
```

Загрузите свой собственный HTML-код в качестве веб-страницы

Мы узнали, как создать веб-сервер и его основы, теперь мы хотим загрузить нашу веб-страницу HTML. Это очень просто, просто замените «привет из esp8266» HTML-кодом.
```ino
server.send(200, "text/plain", "hello from esp8266!");
```

Сначала мы берем код веб-страницы в отдельном заголовочном файле, называем его «index.h», теперь наша веб-страница представляет собой массив символов, хранящихся в переменной MAIN_page . Не используйте комментарии в этом файле. Это HTML-данные как символьный массив, а не программа. Теперь HTML-код находится в заголовочном файле .h, а не .html.

### файл index.h

```ino
const char MAIN_page[] PROGMEM = R"=====(
<HTML>
	<HEAD>
			<TITLE>My first web page</TITLE>
	</HEAD>
<BODY>
	<CENTER>
			<B>Hello World.... </B>
	</CENTER>	
</BODY>
</HTML>
)=====";
```

Теперь мы импортируем этот заголовочный файл в нашу программу, используя #import «index.h» . Убедитесь, что этот файл должен быть с файлом кода Arduino .ino

Изменения в основных программах вносятся в подпрограмму handleRoot, которая отправляет веб-страницу клиенту, теперь мы отправляем html-страницу с текстом text / plain в text / html .

```ino
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
} 
```

Модифицированная функция handleRoot
```inovoid handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}
```

### Полная программа для веб-страницы HTML от esp8266
.ino файл

```ino
/*
 * Hello world web server
 * circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h" //Our HTML webpage contents

//SSID and Password of your WiFi router
const char* ssid = "Circuits4you.com";
const char* password = "123456789";

ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
```


```ino
/*
 * Hello world web server
 * circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
#include "index.h" //Our HTML webpage contents
 
//SSID and Password of your WiFi router
const char* ssid = "Circuits4you.com";
const char* password = "123456789";
 
ESP8266WebServer server(80); //Server on port 80
 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
```


### Полученные результаты
Чтобы увидеть результат, сначала получите IP-адрес от последовательного монитора. Откройте последовательный монитор и нажмите «Сброс». Он отправляет IP-адрес и показывает состояние своего подключения, если он не может подключиться, на последовательном мониторе отображаются точки «…… ..». Проверьте ваш ssid и пароль.
```ino
//SSID and Password of your WiFi router
const char* ssid = "your_ssid";
const char* password = "password";
```

После подключения он покажет следующее

IP-адрес подключения назначен
Откройте веб-браузер и введите этот IP-адрес (192.168.2.2), чтобы использовать доменное имя, прочитайте этот пост. Убедитесь, что ваш ноутбук или телефон должен быть подключен к той же сети. Вы можете увидеть эту веб-страницу, которую мы создали на всех устройствах, которые подключены к маршрутизатору WiFi, к которому подключен ESP8266.


