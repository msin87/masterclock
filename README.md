# Первичные часы
Первичные часы (задающие часы, мастер часы) предназначены для управления электромеханическими часами (вторичными часами). 
## Характеристики
- [x] Интерфейс на базе STemWin
- [x] Тачскрин
- [x] 4 линии (в данной версии). На каждую линию может быть нагруженно несколько вторичных часов
- [x] Выбор типа выходного импульса: однополярный, с чередующейся полярностью
- [x] Питание RTC от VBAT
- [x] Хранение настроек в Backup регистрах
- [x] Проверка сохраненных данных по CRC
- [x] Калибровка RTC (+/- N секунд через K дней) 
- [x] Автоматический переход на зимнее/летнее время
- [x] Отключение автоматического перехода на зимнее/летнее время
- [x] Отключение/приостановка линий (всего три состояния: СТОП,ПУСК,ВЫКЛ)
- [x] Автоматическая коррекция времени на линиях после пропадания питания и последующего его появления
- [x] Ручная коррекция времени на линиях
- [x] Независимые часовые пояса для линий
- [x] Встроенный календарь, не позволяющий установить неправильную дату
- [ ] Индикация потребляемого линиями тока
- [ ] Автоматическая блокировка интерфейса 
- [ ] Экран разблокировки интерфейса при помощи предустановленного пароля
- [ ] Контроль питания 
- [ ] Дистанционное управление через UART
- [ ] Расписание событий
- [ ] УНЧ, подключение динамиков, выдача музыкального фона по наступлению события
## Описание программной части
Программная часть базируется на библиотеке HAL для stm32. Для облегчения разработки GUI используется FreeRTOS. Во FreeRTOS "крутится" несколько задач:
- **defaultTask** - производится опрос тачскрина
- **GUI** - крутится библиотека STemWin. Каждую секунду происходит обновление структуры, хранящей в себе системное время, и при необходимости обновляется дата. Каждую минуту выдаются семафоры для тасков линий
- **vTaskLineN**,где N-номер линии - таски линий, в которых производится инкремент времени в masterClock.line[N], и изменяется состояние соответствующего пина для выдачи импульса. Для положительного и отрицательного импульса назначены свои пины. Длительность импульса задается переменной masterClock.line[N].Width (0..15), и рассчитывается по формуле: 
```
T=masterClock.line[N].Width*LINE_WIDTH_MULT (мС)
```
LINE_WIDTH_MULT - именованная константа в guivars.h
# Планы
- Переход с STM32F103VET6 на STM32F407ZGT6. Необходим для обеспечения возможности подключения внешней SRAM, что позволит устранить мерцание GUI при его изменении. Рендеринг будет производится в памяти силами API STemWin. 
- Получение данных с DTMF модема, который будет работать на соседнем микроконтроллере. Прием данных будет осуществляться при помощи линий пожарного оповещения. Данные должны передаваться мастер-устройствами (датчики температуры, давления, синхронизация времени...) в диапазоне частот от 16кгц до 20кгц. Алгоритм декодирования отработан, испытан. Реализация демодулятора представлена здесь: https://github.com/msin87/gerz Выделение модема в другой микроконтроллер необходим для облегчения использования данного модема в других проектах. 
- Пересылка данных в часовые линии в DTMF виде. Необходимо для реализации возможности управления цифровыми часами (LED)
Проект видится возможным для продажи в качестве исходного кода + схемы + дизайны плат фирмам производителям первичных часов, так и в качестве самостоятельного изготовления и последующей самостоятельной продажи первичных часов. 
## Плюсы проекта
- Графический интерфейс
- Сенсорное управление
- Независимые линии (параметры импульсов, времени)
- Возможность диганостики линий
- Возможность интеграции в сложные офисные центры благодаря наличию DTMF модема (нет необходимости прокладывать новые кабельные сети для передачи данных)
- Возможность развертывания вторичных устройств типа "Умный офис" на основе существующих линий пожарного оповещения
- Следовательно, экономия на развертывании дополнительных кабельных сетей. 
## Ссылки
https://www.youtube.com/playlist?list=PLETA3sQc0F7jAHRk-ew5IhVjwY3-kG1VV здесь периодически выкладываю этапы разработки
## Гостям
Приглашаю к совместной работе над данным большим проектом. У меня есть уникальная возможность протестировать в реальных "боевых" условиях всю систему, есть выход на потенциальных покупателей данной системы.
Все вопросы и предложения пишите на почту: msin87@yandex.ru 
