# Домашнее задание к занятию «Асинхронное программирование»

### Цель задания

1. Реализовать многопточное исполннение на основе асинхронных задач.
2. Научиться использовать синхронизации потоков через связку std::promise-std::future.
3. Научиться выполнять рекурсивный запуск асинхронных задач.

------

### Задание 2

#### For_each

* Реализуйте параллельный вариант оператора for_each.<br/>
* Функция должна принимать итераторы на начало и конец контейнера и ссылку, обрабатывающую функцию.<br/>
* При реализации нужно рекурсивно разделить контейнер на несколько блоков и для каждого запустить отдельную задачу, применяющую обрабатывающую функцию к части контейнера.

------

### Правила приёма домашней работы

Чтобы сдать домашнее задание, прикрепите в личном кабинете ссылку на ваш репозиторий.

### Критерии оценки домашней работы

1. В личном кабинете прикреплена ссылка на репозиторий с кодом для заданий 1 и 2.
2. В ссылке содержится код, который при запуске выполняет описанный в задании алгоритм.




