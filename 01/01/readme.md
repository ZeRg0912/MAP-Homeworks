# Домашнее задание к занятию «Многопоточность»

### Цель задания

1. Сделать программы для имитации очереди клиентов и для многопточной обработки массивов.
2. Научиться запускать потоки и передавать им данные.
3. Научиться распараллеливать вычисления и определять время исполнения кода.

------

### Задание 1

#### Очередь клиентов

Вам нужно создать приложение, которое имитирует очередь в окошко. Для этого нужно создать два потока, работающие с одной разделяемой переменной.

Первый поток имитирует клиента: раз в секунду он обращается к счётчику клиентов и увеличивает его на 1. Максимальное количество клиентов должно быть параметризировано.

Второй поток имитирует операциониста: раз в 2 секунды он обращается к счётчику клиентов и уменьшает его на 1. «Операционист» работает до последнего клиента.

------

### Правила приёма домашней работы

Чтобы сдать домашнее задание, прикрепите в личном кабинете ссылку на ваш репозиторий.

### Критерии оценки домашней работы

1. В личном кабинете прикреплена ссылка на репозиторий с кодом для заданий 1 и 2.
2. В ссылке содержится код, который при запуске выполняет описанный в задании алгоритм.



