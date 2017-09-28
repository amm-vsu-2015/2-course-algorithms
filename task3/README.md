# Алгоритмы и структуры данных: Задача 3.

Задача о восьми ферзях:
1. Узнать количество положение ферзей, при которых они не бьют друг друга.
2. Выбрать одну пару компинаций (т.к. положения будут зеркальными)
3. Положения зеркальны относительно горизонтальной плоскости.

Входные данные для проверки: не требуются.

Нужно выбрать номер решения.

# Функции

```cpp

// print board on the screen
void showBoard();

// checking actual position for set queen
bool tryQueen(int row, int column)

// recursive search for position and setting queens
void setQueen(int column, int &counter, int solution)


```
