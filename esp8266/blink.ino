int led1 = D0; // กำหนดขาใช้งาน
int val = 1;
void setup()
{
  pinMode(led1, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา D0 เป็น OUTPUT
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
