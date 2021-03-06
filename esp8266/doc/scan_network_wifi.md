## Scan WIFI networks

```ino
#include "ESP8266WiFi.h"


void setup() {
  Serial.begin(9600);
  // Set WiFi to station mode and disconnect from an AP if it was  previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);
  Serial.println("Setup done");
}


void loop() {
    Serial.println("scan start");
    // WiFi.scanNetworks will return the   number of networks found
    int n = WiFi.scanNetworks();
    
    Serial.println("scan done");
    
    if (n == 0){
        Serial.println("no networks found");
    } else  {
        Serial.print(n);
        Serial.println(" networks found");
  
    for (int i = 0; i < n; ++i) {
        // Print SSID and RSSI for each network found
      Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ": "*");
        delay(10);
     }
}

 Serial.println("");
 // Wait a bit before scanning again
 delay(5000);
}
```


### Output

```ino
17:56:35.015 -> scan start
17:56:37.204 -> scan done
17:56:37.204 -> 5 networks found
17:56:37.237 -> 1: Penjushkin (-89)*
17:56:37.270 -> 2: TD-Discon (-92)*
17:56:37.270 -> 3: DIR-615T-e6c6 (-91)*
17:56:37.303 -> 4: Gerda (-80)*
17:56:37.303 -> 5: Otsosinovik (-90)*
17:56:37.336 -> 
```

