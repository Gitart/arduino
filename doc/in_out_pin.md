# Pin

### У Arduino UNO имеется 3 порта: 
***B*** (цифровые входа/выхода с 8 по 13)   
***C*** (аналоговые входа)   
***D*** (цифровые входа/выхода с 0 по 7)    

Каждый порт управляется 3 регистрами. 
Регистр ***DDR*** определяет чем будет являться нога (pin) входом или выходом. 
При помощи регистра ***PORT*** можно установить pin в состояние ***HIGH*** или ***LOW***.   
При помощи регистра PIN можно считать состояние ножек Arduino, когда они работают на вход.  

### Мы будем использовать порт B.  
Сначала, мы должны установить все ножки порта B как цифровые выхода.   
У порта B имеется только 6 ножек.   
Биты регистра для В-порта DDRB должны быть установлены в 1, если нога будет использоваться как выход (OUTPUT), 
и в 0, если нога будет использовать как вход (INPUT). 
Биты портов нумеруются с 0 по 7, но не всегда содержат все 8 ног. 

#### Пример:  
**DDRB = B00111110;**    // установить ножки порта В с 1 по 5 как выхода, а 0 как вход.

Обратите внимание, что в микроконтроллерах фирмы Microchip все наоборот. 
0 бит - нога работает как выход, а 1 - как вход.

В нашем проекте бегущего огня мы будем использовать 5 выходов:
**DDRB = B00011111;**     // установить ноги порта В с 0 по 4 как выхода

Для записи значений в порт В необходимо использовать регистр PORTB. Зажечь первый светодиод можно командой:
***PORTB = B00000001;***  
первый и четвертый:  
***PORTB = B00001001;***

Теперь вы видите, как легко мы можем включать и выключать светодиоды. Теперь расскажем вам об операторах сдвига

Есть 2 оператора двоичного сдвига: оператор сдвига влево << и оператор сдвига вправо >>. 
Оператор сдвига влево << заставляет все биты сдвигаться влево, соответственно оператор сдвига вправо >> 
сдвигает биты вправо.

### Пример: 
```ino
varA = 1; // 00000001
varA = 1 << 0; // 00000001
varA = 1 << 1; // 00000010
varA = 1 << 2; // 00000100
```
Теперь вернемся к нашей программе, которая показана ниже. Нам нужно ввести 2 переменные: первая upDown будет содержать значение куда двигаться - вверх или вниз, а вторая cylon какие светодиоды зажигать.

В функции setup() мы определяем какие ножки должны работать как выхода.

В главном цикле программы loop(), светодиоды по очереди загораются вверх путем увеличения переменной cylon, а когда доходит до самого верхнего, то переменной upDown присваивается 0 и светодиоды загораются вниз по очереди.

```ino
/*
  Бегущий огонь. 5 светодиодов
 */
 
unsigned char upDown=1;         // начинаем с движения вверх    
unsigned char cylon=0;          // определяет очередность LED
 
void setup() {                
  DDRB = B00011111;             // устанавливаем порт B с 0 по 4 как выхода   
}
 
void loop() {
  if(upDown==1){                // если идем вверх, то
    cylon++;
    if(cylon>=4) upDown=0;      // когда достигнут наибольший номер LED, то в след. цикле идем вниз
  }
  else {
    cylon--;
    if(cylon==0) upDown=1;      // когда достигнут наименьший номер LED, то в след. цикле идем вверх
  }
  
  PORTB = 1 << cylon;         //сдвиг
  delay(200);                   // пауза 200 мс
```