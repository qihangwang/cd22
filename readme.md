# pike

## Build

Для сборки используется CMake, VS2015. Внешние зависимости - Qt5.

```
md build
cd build
cmake -G"Visual Studio 14 2015" -Ax64 -DQt5_DIR=${VS_QT}/lib/cmake/Qt5 ..
cmake --build . --target ALL_BUILD --config Release
```

где ${VS_QT} - путь к тулчейну QT (например, C:/Qt/Qt5.12.3/5.12.3/msvc2015_64).

### Build and run tests

```
cmake -G"Visual Studio 14 2015" -Ax64 -DQt5_DIR=${VS_QT}/lib/cmake/Qt5 -DBUILD_TESTING=ON ..
cmake --build . --target ALL_BUILD --config Release
# или так, чтобы собрать только тесты
cmake --build . --target RUN_TESTS --config Release
ctest
```

## Архитектура ПО

Термины:
- Сечение - измерение глубины в одной плоскости и результат такого измерения.

Проект разбит на библиотеки (по логическим уровням):
- dc - устройство сбора данных (Л-Кард и DummyDaq).
- devices - устройства, входящие в "Пику" (двигатели, одометр, инклинометр, глубинометр и "концевые" датчики).
- logic - логика работы/операции (определение пройденного расстояния, положения в пространстве и текущих показаний глубины и "концевых" датчиков, управление с помощью джойстика через UDP, измерение глубины и конфигурация).
- modules - MVP-модули окон приложения (main). Частично логика перемещения и вращения измерительного блока.
- pike-qwidgets - GUI-приложение на основе QtWidgets.

Все устройства и операции "развязаны" через интерфейсы (абстрактные классы). Разделение логики и GUI через MVP.

### Реализация devices

- Depthometer - Датчик расстояния/глубины (FASTUS CD22). Подключение через COM-порт.
- Ender - "Концевой" датчик. Подключение через входную линию ТТЛ.
- Inclinometer - Инклинометр. Подключение через АЦП - с датчика приходят два PWM-сигнала. Для упрощения считаем по ним СКЗ и используем таблицы пересчёта (вместо расчёта коэффициента заполнения).
- Mover - Перемещение вперёд-назад с помощью коллекторного двигателя. Подключение через выходные линии ТТЛ - PWM и Dir. Ожидаемая частота импульсов PWM 10 кГц, но мы используем режим максимальной скорости (единичный коэфф. заполнения).
- Odometer - Одометр/курвиметр/датчик пройденного расстояния (ЛИР-119). Подключение через АЦП - с датчика приходят два strobe-сигнала.
- Rotator - Вращение измерительного блока с помощью шагового двигателя (TI DRV8825). Подключение через выходные линии ТТЛ - Enable, Step, Dir и M0.

### Реализация logic

- Conf - Конфигурация ПО через файл Conf.json.
- OngoingReader - Режим измерения пройденного расстояния, положения в пространстве, состояния "концевых" датчиков и глубины. Измерение идёт постоянно, кроме "концевых" датчиков и глубины, которые "приостанавливаются" на время измерения сечения (Slicer).
- Pike - "Пика". По идее сюда нужно перенести управление перемещением, вращением и измерением сечения из MainPresenterImpl.
- RemoteServer - Режим приёма событий от джойстка, подключенного на удалённом копьютере, через UDP.
- Slicer - Режим измерения сечения - поворот измерительного блока в крайнее левое положение, измерение положения в пространстве и циклическое измерение глубины (и инкремент угла) до крайнего правого положения.

## TODO

- камеры
- сохранение видео и фото
- джойстик (через pike-remote)
- сохранение "сечения" (SliceMsrMapper)
- логирование?
- перед запуском на устройстве:
  - "активное" состояние "концевого" датчика - 0 или 1? (нужен тест)
  - одометр: вперёд/назад - запаздывание фронтов (нужен тест)
  - инклинометр: неполная блок-схема (СНН)
  - инклинометр: СКЗ? (нужен тест)
  - инклинометр: файл с таблицей пересчёта СКЗ в угол
