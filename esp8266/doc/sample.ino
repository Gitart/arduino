#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
//SSID and Password to your ESP Access Point
const char* ssid     = "HeadOffice";
const char* password = "Pass$word";

// Server on port 80
ESP8266WebServer server(80); 

 
/*********************************************************************
 *     This rutine is exicuted when you open its IP in browser
 *********************************************************************/
void handleRoot() {
    String t = "Новость котрорую Используя данный модуль можно управлять устройствами по SMS или через интернет, осуществлять SMS уведомления (например, о проникновении в помещение, транспорт, дом, склад) или создать SMS рассылку, отправлять данные (например, статистику) на интернет ресурсы, осуществлять голосовую связь (двухстороннюю или одностороннюю), и многое многое другое. Данный модуль является реальной альтернативной устройствам беспроводной радиосвязи на больших дистанциях.";
    server.send(200, "text/html", "<!DOCTYPE html> <html> <head> <meta charset='utf-8' /> </head> <body> <h2>HTTP</h2> <br> Привет дорогой друг</body>"+t+" </html>");
}


/*********************************************************************
 * Второй роутинг для старницы
 *********************************************************************/
void hRt() {
 server.send(200, "text/html", "<html> <body> <h2>Hello</h2> <br> Привет дорогой друг</body> </html>");
}

 
//===============================================================
//                  SETUP
//===============================================================
void setup(void){
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);                //  Только точка доступа      -- Only Access point
  WiFi.softAP(ssid, password);       //  Название сети и пароль    -- Start HOTspot removing password will disable security

  // Get IP address
  IPAddress myIP = WiFi.softAPIP();  
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
 
  server.on("/",      handleRoot);   // Главная страница стартовая
  server.on("/test/", hRt);          // Вторая страница

  // Start server
  server.begin();                    
  Serial.println("Старт...");
}



//===============================================================
//                     LOOP
//===============================================================
void loop(void){
     server.handleClient();          // Handle client requests
}
