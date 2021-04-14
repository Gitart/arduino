// https://www.myarduino.net/article/143/%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%87%E0%B8%B2%E0%B8%99-nodemcu-esp8266-%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B8%AA%E0%B8%B7%E0%B9%88%E0%B8%AD%E0%B8%AA%E0%B8%B2%E0%B8%A3%E0%B8%AD%E0%B8%99%E0%B8%B8%E0%B8%81%E0%B8%A3%E0%B8%A1-serial-%E0%B8%AD%E0%B9%88%E0%B8%B2%E0%B8%99%E0%B8%84%E0%B9%88%E0%B8%B2%E0%B8%82%E0%B9%89%E0%B8%AD%E0%B8%84%E0%B8%A7%E0%B8%B2%E0%B8%A1%E0%B8%97%E0%B8%B5%E0%B9%88-nodemcu-%E0%B8%AA%E0%B9%88%E0%B8%87%E0%B8%A1%E0%B8%B2%E0%B9%83%E0%B8%AB%E0%B9%89%E0%B8%84%E0%B8%AD%E0%B8%A1%E0%B8%9E%E0%B8%B4%E0%B8%A7%E0%B9%80%E0%B8%95%E0%B8%AD%E0%B8%A3%E0%B9%8C

int led1 = D0; 
int val = 1;
void setup()
{
  pinMode(led1, OUTPUT); // D0 OUTPUT
  Serial.begin(9600);
  Serial.println("My arduino.net");
}
void loop()
{
  digitalWrite(led1, HIGH); // ไฟ LED 1 ติด
  Serial.print(val); // NodeMCU ส่งค่าในตัว แปล val ให้ arduino
  Serial.print(" ON "); // NodeMCU ส่งคำว่า " ON " 
  Serial.println("LED"); // NodeMCU ส่งคำว่า "LED"
  delay(2000); // ดีเลย์ 2000 มิลลิวินาที
  digitalWrite(led1, LOW); // ไฟ LED 1 ดับ
  Serial.print("OFF "); // NodeMCU ส่งคำว่า "OFF "
  Serial.println("LED"); // NodeMCU ส่งคำว่า "LED"
  delay(2000); // ดีเลย์ 2000 มิลลิวินาที

}
