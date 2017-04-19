
/**

  Задача на ход коня:
    1. Сетка 7х9,
    2. Две клетки заблокированы
    3. Вывести 2 результата работы программы: успешный полный обход, неуспешный обход.
    4. Вывести результат на экран символьной графикой (пошагово).

  Входные данные для проверки:

  (1) Координаты заблокированных клеток: (1,1), (2,2).
      Старт фигуры с координат: (1,3),

*/

#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

void printHorse(int[][] position, int rows, int columns) {
  for (int idx_k = 0; idx_k < rows; idx_k++) {
    for (size_t idx_s = 0; idx_s < columns; idx_s++) {
      if (position[idx_k][idx_s] == -1) std::cout << " *";
      if (position[idx_k][idx_s] ==  0) std::cout << " .";

      if (0 < position[idx_k][idx_s]) && (position[idx_k][idx_s] < 10)  std::cout << ' ' << position[idx_k][idx_s] << ' ';
      if (9 < position[idx_k][idx_s]) && (position[idx_k][idx_s] < 100) std::cout << ' ' << position[idx_k][idx_s] << ' ';

      if (position[idx_k][idx_s] >= 100) std::cout << position[idx_k][idx_s] << ' ' << '\n';
    }
    std::cout << '\n' << '\n';
  }
}


int main() {
  cout << "Hello world!" << '\n';

  int accessCount;
  int flag;
  int flagR;
  int numR;
  int xMin, yMin, x1, y1, x0R, y0R, x0, y0;

  int accessibility[ROWS][COLUMNS];
  int accessibility1[ROWS][COLUMNS];
  int board[ROWS][COLUMNS];
  int board1[ROWS][COLUMNS];

  int number;

  // step map
  int horizontal[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
  int vertical[8]   = { -1, -2, -2, -1, 1, 2, 2, 1 };

  for (int idx_i = 0; idx_i < ROWS; idx_i++) {
    for (int idx_j = 0; idx_j < COLUMNS; idx_j++) {
      board[idx_i][idx_j] = 0;
    }
  }

  std::cout << "Field created!" << '\n';
  std::cout << "Write block cells amount." << '\n';

  int blockedCellsAmount = 0;
  while (1) {
    std::cin >> blockedCellsAmount;
    if (blockedCellsAmount < (ROWS * COLUMNS)) break;
    else std::cout << "Error: amount of blocked cells is bigger!" << '\n';
  }

  if (blockedCellsAmount > 0) {
    std::cout << "Set coords for blocked cell." << '\n';
    for (int idx_i = 0; idx_i < blockedCellsAmount; idx_i++) {
      while (1) {
        std::cin >> x0;
        std::cin >> y0;
        x0--; y0--;
        // system("cls");
        break;
        if ((0 <= x0) && (x0 < COLUMNS) && (0 <= y0) && (y0 < ROWS))
          break;
        else
          std::cout << "Error: coords outter of the field." << '\n';
      }

      if (blockedCellsAmount - idx_i > 0)
        std::cout << "Blocked cell was created, " << blockedCellsAmount << " more left.";
      else
        std::cout << "All blocked cell was created";
    }
  } else {
    std::cout << "Field without blocked cells." << '\n';
  }

  for (int x0 = 0; x0 < ROWS; x0++) {
    for (int y0 = 0; y0 < COLUMNS; y0++) {
      accessCount = 0;
      for (int idx_i = 0; idx_i <= 7; idx_i++) {
        x1 += horizontal[idx_i];
        y1 += vertical[idx_i];
        
        if ((0 <= x1) && (x1 <= ROWS) && (0 <= y1) && (y1 < COLUMNS)) 
          accessCount++;
      }

      accessibility[x0][y0] = accessCount;
    }
  }

  std::cout << "---------------" << '\n';
  int stop;
  cin >> stop;
  return 0;
}
