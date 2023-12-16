# MazeProject
Проект по графике.

## Описание
Хотел сделать типа хоррор карту лабиринт с базовым ИИ.

## Реализованные фичи
1. Генерация рандомного лабиринта. (Обычный обход в ширину)
2. Хождение от первого лица, с управлением мышкой. На SHIFT можно бежать
3. Во время хотьбы камера покачивается (во время бега частота качения увеличивается в два раза)
4. Реализован точечный источник света, правее камеры (типа факел)
5. Генерация стен лабиринта (Тупо смотрим связи клеток. Где связи нет - там ставим стену с подпоркой)
6. Небольшая оптимизация (Генерация стен только в пределах радиуса)

## Нереализованные фичи
0. Физика (достаточно двумерной)
0. ИИ (Тупо времени не хватило)
  <p>Идеи реализации</p>
  - Иметь две стадии 
    a. Покоя (Идем в рандомную сторону, в которой мы не были. Или, если таких нет забыть направление и повторять
    b. Агрессии (слеования по запомненным координатам с удвоенной скоростью)
      - Если персонаж на прямой от ИИ (на определенном расстоянии), запоминаем его положение (например кладем его в стэк)
      - Если персонаж издал звук (например бежал) в радиусе от ИИ, запоминаем координаты этого места.
  - Отрисовывает его только на определенном расстоянии, но движение по лабиринту проводить все-ровно
0. Звуки (Крч, в OpenGl бедовые звуки... Встроенные алгоритмы синхронные и останавливает GUI)
0. Генерация потолка...
0. Генрация выхода
0. Уровни
