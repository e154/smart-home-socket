Автомат управления розетками/нагрузками
---------------------------------------

##### Функции
    Контроль температуры силового блока
    Включение/Выключения по команде управляющего сервера
    Контроль наличия сети/фазы

##### Общение с сервером
    Общение происходит по линии связи rs485, с помощью модифицированного 
    протокола MODBUS ASCII

##### Поведение автомата

    состояния:
    включен/выключен

    температура:
    в пределах нормы
    за пределами нормы

    комманды консоли:
    запрос состояния
          температура
          фаза
          вкл/выкл
          максимальный предел температуры
    включить
    выключить

<img src="images/DSC_0055.JPG" alt="smart home socket" width="630">
<img src="images/DSC_0030.JPG" alt="smart home socket" width="630">
<img src="images/DSC_0031.JPG" alt="smart home socket" width="630">
<img src="images/DSC_0048.JPG" alt="smart home socket" width="630">
<img src="images/DSC_0054.JPG" alt="smart home socket" width="630">

#### LICENSE

Smart home socket is licensed under the [MIT License (MIT)](https://github.com/e154/smart-home-socket/blob/master/LICENSE).