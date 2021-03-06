
#### Список наиболее используемых AT\-команд:

```
*   AT – для проверки правильности подключения модуля. Если все исправно, возвращается OK.
*   A/ – повтор предыдущей команды.
*   AT+IPR? – получение информации о скорости порта. Ответом будет +IPR: 0 OK (0 в данном случае – автоматически).
*   AT+ICF? – настройка передачи. В ответ придет +ICF: бит, четность.
*   AT+IFC? – контроль передачи. Ответом будет +IFC: терминал от модуля, модуль от терминала (0 – отсутствует контроль, 1 – программный контроль, 2 – аппаратный).
*   AT+GCAP – показывает возможности модуля. Пример ответа – +GCAP:+FCLASS,+CGSM.
*   AT+GSN – получение IMEI модуля. Пример ответа 01322600XXXXXXX.
*   AT+COPS? – показывает доступные операторы.
*   AT+CPAS – состояние модуля. Ответ +CPAS: 0. 0 – готовность к работе, 3 – входящий звонок, 4 – голосовое соединение, 2 – неизвестно.
*   AT+CCLK? – информация о текущем времени и дате.
*   AT+CLIP=1 – включение/выключение АОН. 1 – включен, 0 – выключен.
*   AT+CSCB=0 – прием специальных смс\-сообщений. 0 – разрешено, 1 – запрещено.
*   AT+CSCS= “GSM” – кодирование смс\-сообщения. Можно выбрать одну из следующих кодировок: IRA, GSM, UCS2, HEX, PCCP, PCDN, 8859\-1.
*   AT+CMEE=0 – получение информации об ошибке.
*   AT+CPIN=XXXX – ввод пин\-кода сим\-карты.
*   AT&F – сброс до заводских настроек.
*   AT+CPOWD=1 – срочное(0) или нормальное(1) выключение модуля.
*   ATD+790XXXXXXXX – звонок на номер +790XXXXXXXX.
*   ATA – ответ на вызов.
*   AT+CMGS=”+790XXXXXXXX”>Test sms – отправка смс\-сообщения на номер +790XXXXXXXX.
```


## Скетчи для работы с модулем GSM

### Отправка СМС на примере SIM900

Перед тем, как отправить сообщение, нужно настроить модуль. В первую очередь нужно перевести в текстовый формат передаваемое сообщение. Для этого существует команда AT+CMGF=1. Нужно перевести кодировку на GSM командой AT+CSCS=»GSM». Эта кодировка наиболее удобная, так как там символы представлены в ASCII коде, который легко понимает компилятор.

Затем нужно набрать смс\-сообщение. Для этого посылается команда с номером абонента AT+CMGS=»+79XXXXXXXXX» r, в ответ предлагается набрать текст смс. Нужно выполнить отправку сообщения. По окончании требуется отправить код комбинации  Ctrl+Z, модуль позволит отправку текста адресату. Когда сообщение будет отправлено, вернется OK.

Взаимодействие с модулем основано на индексах, которые присваиваются каждому новому сообщению. По этому индексу можно указать, какое из сообщений удалить или прочитать.

Получение смс. Для чтения смс\-сообщения используется команда AT + CNMI = 2,2,0,0,0. Когда на модуль придет текстовое сообщение, он отправит в последовательный порт +CMTI: «SM»,2 (в данном случае 2 – порядковый номер сообщения). Чтобы его прочитать, нужно отправить команду AT+CMGR=2.

Прием голосового звонка. В первую очередь для разговора нужно подключить к модулю динамик и микрофон. При получении звонка будет показан номер, с которого он совершен. Для осуществления работы нужно включить библиотеку GSM:

#include <GSM.h>

Если сим\-карта заблокирована, нужно ввести ее пин\-код. Если пин\-код не требуется, это поле нужно оставить пустым.

#define PINNUMBER “”

В setup() должна быть произведена инициализация передачи данных на компьютер. Следующим шагом будет создание локальной переменной, чтобы отследить статус подключения к сети. Скетч не будет запущен, пока сим\-карта не подключена к сети.

boolean notConnected = true;

С помощью функции gsmAccess.begin() происходит подключение к сети. При установлении соединения вернется значение GSM\_READY.

vcs.hangCall(); – функция, показывающая, что модем готов принимать звонки.

getvoiceCallStatus() – определяет статус скетча. Если кто\-то звонит, она возвращает значение RECEIVINGCALL. Для записи номера нужно воспользоваться функцией retrieveCallingNumber(). Когда будет совершен ответ на звонок, вернется TALKING. Затем скетч будет ждать символа новой строки, чтобы прервать разговор.

### Установить GPRS\-соединение и отправить данные на удаленный сервер

Сначала нужно установить библиотеку SoftwareSerial, которая позволяет обеспечивать последовательную передачу информации и связать GSM\-модуль и микроконтроллер Ардуино.

Для отправки данных на сервер нужно отправить следующие команды:

AT+SAPBR=1,1 – открытие Carrier.

Следующие три команды связаны с установкой настроек подключения к сети.

AT+SAPBR=3,1,\\”APN\\”,\\”internet.mts.ru\\” – выбор оператора mts, имя точки доступа.

AT+SAPBR=3,1,\\”USER\\”,\\” mts \\” – выбор пользователя mts.

AT+SAPBR=3,1,\\”PWD\\”,\\” mts \\”

AT+SAPBR=1,1 – установка соединения.

AT+HTTPINIT – инициализация http.

AT+HTTPPARA=”URL”, – URL адрес.

AT+HTTPREAD – ожидание ответа.

AT+HTTPTERM – остановка http.

Если все выполнено правильно, в мониторе порта будут появляться строчки с АТ командами. Если отсутствует связь с модемом, то будет показывать по одной строке. При успешной установке GPRS\-соединения  на модуле начнет мигать светодиод.
