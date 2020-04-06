# Отправка на сервер

## Задача:
Отправлять с ардуино показания на сервер, а на сервере получать эти данные.



## Arduino code
```ino
// Отправка данных на сервер

#include <SPI.h>
#include <Ethernet.h>


// Сервер на котрый надо отправлять данные
char server           []  = "192.168.0.104";

// Настройка подключения и конфигурации сети
byte ethernet_mac     [] = {0x78, 0xAC, 0xC0, 0x43, 0x7B, 0xC1};               // Мак адрес
byte ethernet_dns     [] = {192, 168, 0, 1};
byte ethernet_gateway [] = {192, 168, 0, 1};
byte ethernet_subnet  [] = {255, 255, 255, 0}; 

// Счетчик 
int Cnt = 0;

// IP сети личный
IPAddress ethernet_ip(192, 168, 0, 177);

// Клиент
EthernetClient client;


//*********************************************
// Сетап
//*********************************************
void setup() {
  // Скорость обмена
  Serial.begin(9600);
  
  // Конфигурация сетевого подключения
  Ethernet.begin(ethernet_mac, ethernet_ip, ethernet_dns, ethernet_gateway, ethernet_subnet); 
  
  // Время для подключения
  delay(1000);
}


//*********************************************
// Цикл
//*********************************************
void loop() {
   Cnt++;
   Serial.println("Oтправка");
  
   sensor(Cnt);
 
   // 5 Second
   delay(5000);
}


/*--------------------------------------------------------------
  Функция отправляет данные о сотоянии датчиков, реле и тд.
 --------------------------------------------------------------*/
void sensor(int Cnt) {
  
  Serial.println("Сенсор отправил данные на сервер");
  client.connect(server, 8000);

  client.print("GET /add/");
  client.print(Cnt);
  
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(server);
  client.println("Connection: close");
  client.println();
  client.println();
  client.stop();
  client.flush();
}

```

# Go code
```golang


package main

import (
  "fmt"
  "net/http"
  "log"
  "time"
 
)


func main(){
  Port:="8000"
 
  // Api Route
  http.HandleFunc("/add/",                 Api_bi_load)                 // Загрузка
  
  // Settings portal
  srv := &http.Server{
                      Addr:         ":" + Port,
                      IdleTimeout:  120 * time.Second,
                      ReadTimeout:  50  * time.Second,
                      WriteTimeout: 50  * time.Second,
                     }



    fmt.Println("Ok start....8000!")
    if err := srv.ListenAndServe(); err != nil {
       log.Fatal(err)
    }
}


/*********************************************************
 Add 
*********************************************************/
func Api_bi_load(w http.ResponseWriter, r *http.Request){

	re:= r.URL.Path[len("/add/"):] // чтение адресной строки   
	fmt.Println("Ok....", re)
}

```



