## Подключение и настройка датчика звука KY-037
Сегодня разберемся, как работать с модулем датчика звука, он же датчик хлопков KY-037. Такие датчики часто используются в охранных системах для обнаружения превышения установленного порога шума (обнаружение щелчков замков, шагов, звука двигателя и т.д.). Модуль датчика звука KY-037 так же часто используют для автоматического управления освещением, реагирующим например, на хлопки в ладоши.

На плате мы видим сам датчик в виде микрофона и микросхему компаратора, которая определяет момент превышения порога громкости. А чувствительность этого самого момента (порога громкости), выставляется с помощью переменного резистора (потенциометра) установленного рядом с компаратором. Если порог звука будет превышен, на выходе D0 появится сигнал высокого уровня.

## Подключение и настройка датчика звука KY-037
Давайте для начала подключим датчик звука KY-037 к плате Arduino. Возьмём, например отладочную плату Arduino Nano.

Пин G модуля датчика звука KY-037 подключаем к выводу GND платы Ардуино. Пин + датчика звука соединяем с выводом 5V платы Ардуино. Вывод D0 датчика, подключаем к цифровому выводу D5 платы Ардуино.

## Настройка датчика звука KY-037.
Подключаем плату Arduino Nano к компьютеру. На модуле датчика хлопков KY-037, должен сразу загореться индикатор питания L1. Необходимо сначала взять отвертку и подкрутить подстроечный резистор, настроив тем самым чувствительность датчика. А в настройке чувствительности нам поможет индикатор срабатывания датчика L2. Если индикатор L2 при включении модуля тоже загорается, крутим подстроечный резистор против часовой стрелки до тех пор, пока не дойдем до момента затухания индикатора. Если же индикатор L2 находится в выключенном состоянии при включении модуля, значит наоборот, крутим подстроечный резистор по часовой стрелке, пока не дойдем до момента, когда индикатор начнет загораться. В итоге в этом месте, где чуть повернув подстроечный резистор в одну или другую сторону, индикатор стремиться потухнуть или загореться, нам нужно повернуть совсем немного против часовой стрелки, чтобы индикатор L2 потух, но при хлопках в ладоши пытался загораться.

Открываем программу Arduino IDE, создаем новый файл и вставляем в него код, который нам покажет каким образом приходит цифровой сигнал с вывода D0 в случаях превышения порога шума установленного с помощью подстроечного резистора.

```ino
const int sensorD0 = 5;  // Пин Arduino к которому подключен пин D0 датчика
 
void setup () // Настройки
{
Serial.begin (9600); // Инициализация SerialPort
}
 
void loop () // Основной цикл программы
{
int sensorValue = digitalRead(sensorD0); // получаем сигнал от датчика
if (sensorValue == true) // Если пришел сигнал высокого уровня
Serial.println(sensorValue); // Выводим цифровое значение на терминал
}
Заливаем данный скетч и переходим в меню "Инструменты" - "Монитор порта". Окно мониторинга порта будет пустым, но как только мы будем хлопать в ладоши, в окне появятся единицы, говорящие о наличии сигнала высокого уровня на выводе D0 модуля датчика звука.
```


## Включаем свет по двойному хлопку.
Давайте усложним задачу и напишем код для работы датчика звука KY-037 по двойному хлопку. Тем самым сократим возможные случайные срабатывания от побочных звуков, которые могут возникать в режиме на один хлопок.

```ino
const int sensorD0 = 5;  // Пин Arduino к которому подключен выход D0 датчика
const int diod = 2; // Пин Arduino к которому подключен светодиод
int diodState = LOW; // Статус светодиода "выключен"
long soundTime=0; // время первого хлопка
 
void setup ()
{
pinMode(diod, OUTPUT); // устанавливаем цифровой пин 2 в режим выхода 
}
 
void loop ()
{
int sensorValue = digitalRead(sensorD0); // получаем сигнал с датчика
 
if (sensorValue == 1 && diodState == LOW) //если порог громкости достигнут и светодиод был ВЫКЛЮЧЕН
{
long diodTime=millis(); // записываем текущее время
 
//если текущее время хлопка больше времени последнего хлопка на 100 миллисекунд
//и хлопок произошел не позже чем через 1000 миллисекунд после предыдущего
//считаем такой хлопок вторым УСПЕШНЫМ
if((millis()>soundTime) && ((diodTime-soundTime)>100) && ((diodTime-soundTime)<1000))
{
digitalWrite(diod, HIGH); // включаем светодиод
diodState = HIGH; // устанавливаем статус светодиода "включен"
delay(100); // небольшая задержка для фильтрации помех
}
soundTime=millis(); //записываем время последнего хлопка
}
else // иначе
{
if (sensorValue == 1 && diodState == HIGH) // если порог громкости достигнут и светодиод был ВКЛЮЧЕН
{
digitalWrite(diod, LOW); // выключаем светодиод
diodState = LOW; // устанавливаем статус светодиода "выключен"
delay(100); // небольшая задержка для фильтрации помех
}
}   
}
```



Всё хорошо. Мы настроили датчик и убедились, что наша Ардуинка прекрасно принимает сигнал от него.

 
Включаем свет по хлопку и выключаем автоматически по таймеру.
Разобрались, как подстроить датчик звука KY-037 и как он реагирует, если превышен установленный порог громкости. Теперь добавим в нашу схему обычный светодиод и напишем простой код, который будет при обнаружении шума зажигать светодиод и тушить его по истечении какого-то времени.

## Подключение и настройка датчика звука KY-037

Светодиод подключаем к пину D2 платы Ардуино. Не забываем поставить любой резистор на землю (GND) светодиода. И загружаем следующий скетч.

```ino
const int sensorD0 = 5;  // Пин Arduino к которому подключен выход D0 датчика
const int diod = 2; // Пин Arduino к которому подключен светодиод
 
void setup ()
{
pinMode(diod, OUTPUT); // устанавливаем цифровой пин 2 в режим выхода  
}
 
void loop ()
{
int sensorValue = digitalRead(sensorD0); // получаем сигнал с датчика   
if (sensorValue == 1) //если получен сигнал от датчика в виде единицы
{
digitalWrite(diod, HIGH); // включаем светодиод
delay(4000); // делаем паузу, чтобы светодиод горел 4 секунды
}
if (sensorValue == 0) // если приходит сигнал от датчика в виде нуля
digitalWrite(diod, LOW); // выключаем светодиод   
}
```

Пробуем хлопнуть в ладоши. Видим, что светодиод загорелся, проработал 4 секунды и потух. Каждая строка подробно прокомментирована и где изменить время горения светодиода, думаю понятно.


## Датчик звука KY-037 включает свет по хлопку и выключает свет по хлопку.
Давайте загрузим новый скетч, который по хлопку будет включать или выключать наш светодиод. Светодиод мы взяли для примера, нет ни каких проблем подсоединить вместо него модуль реле и тем самым включать или выключать любые бытовые приборы.

```ino
const int sensorD0 = 5;  // Пин Arduino к которому подключен выход D0 датчика
const int diod = 2; // Пин Arduino к которому подключен светодиод
int diodState = LOW; // Статус светодиода "выключен"
 
void setup ()
{
pinMode(diod, OUTPUT); // устанавливаем цифровой пин 2 в режим выхода 
}
 
void loop ()
{
int sensorValue = digitalRead(sensorD0); // получаем сигнал с датчика
 
if (sensorValue == 1 && diodState == LOW) //если порог громкости достигнут и светодиод был ВЫКЛЮЧЕН
{
digitalWrite(diod, HIGH); // включаем светодиод
diodState = HIGH; // устанавливаем статус светодиода "включен"
delay(100); // небольшая задержка для фильтрации помех
}
else // иначе
{
if (sensorValue == 1 && diodState == HIGH) // если порог громкости достигнут и светодиод был ВКЛЮЧЕН
{
digitalWrite(diod, LOW); // выключаем светодиод
diodState = LOW; // устанавливаем статус светодиода "выключен"
delay(100); // небольшая задержка для фильтрации помех
}
}   
}
```

Хлопаем теперь один раз в ладоши, свет зажигается. Хлопаем повторно в ладоши, светодиод тухнет.

Пробуем два раза хлопнуть в ладоши, светодиод зажигается. Выключаем светодиод одинарным хлопком. 
Все хорошо срабатывает без всяких глюков. Код максимально прокомментирован, читайте, должно быть более чем понятно. 
Сделать, чтобы свет выключался тоже в два хлопка, думаю трудностей не составить. Теперь можете перекидывать провода с 
линии D2, к примеру, на релейный модуль и управлять освещением в комнате либо другими бытовыми приборами.

В принципе основные возникающие вопросы с датчиком звука KY-037 мы разобрали. Остается только напомнить, 
что на плате есть так же аналоговый вывод A0, который подсоединяется к любому аналоговому выводу платы Ардуино, 
например, к выводу A1. Принимается аналоговый сигнал строкой sensorValue = analogRead(A1);. 
Напряжение на аналоговом выходе датчика изменяется в зависимости от изменений окружающих шумов. 
Такой сигнал дает нам возможность применять программную обработку этих самых шумов, анализируя характер колебаний. 
Это может позволить реагировать не просто на шум в данный момента времени, а создавать даже свою базу различных шумов, 
опираясь на какие-то ключевые моменты в характерных изменениях показаний сигнала на выходе A0. 
В итоге сверки с такой базой шумов, можно реализовать различную реакцию на разные шумы. Но это для тех кто хочет 
больше погрузиться в программирование и тема скорей всего другой статьи.
