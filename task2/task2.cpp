
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
#include <iomanip>

using namespace std;

const int ROWS = 7; // m
const int COLUMNS = 9; // n

void printHorse(int position[ROWS][COLUMNS], int ROWS, int COLUMNS);

void printHorse(int position[ROWS][COLUMNS], int ROWS, int COLUMNS) {

  // std::cout.precision(4);     // accc
  for (int idx_k = 0; idx_k < ROWS; idx_k++) {
    for (int idx_s = 0; idx_s < COLUMNS; idx_s++) {
      if (position[idx_k][idx_s] == -1) std::cout << setw(8) <<  " [*]";
      if (position[idx_k][idx_s] == 0)  std::cout << setw(8) <<  " [ ]";

      if ((0 < position[idx_k][idx_s]) && (position[idx_k][idx_s] < 10))  std::cout << setw(8) << position[idx_k][idx_s];
      if ((9 < position[idx_k][idx_s]) && (position[idx_k][idx_s] < 100)) std::cout << setw(8) << position[idx_k][idx_s];

      if (position[idx_k][idx_s] >= 100) std::cout << setw(8) << position[idx_k][idx_s] << '\n';
    }
    std::cout << '\n' << '\n';
  }
}


int main() {

  int accessCount = 0;
  int flag = 0;
  int flagR = 0;
  int numR = 0;
  int xMin = 0, yMin = 0, x1 = 0, y1 = 0, x0R = 0, y0R = 0, x0 = 0, y0 = 0;

  int accessibility[ROWS][COLUMNS];
  int board[ROWS][COLUMNS];

  int number;

  // step map
  int horizontal[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
  int vertical[8]   = { -1, -2, -2, -1, 1, 2, 2, 1 };

  for (int idx_i = 0; idx_i < ROWS; idx_i++) {
    for (int idx_j = 0; idx_j < COLUMNS; idx_j++) {
      board[idx_i][idx_j] = 0;
      // accessibility[idx_i][idx_j] = 0;
    }
  }

  std::cout << "Field created! Size: " << ROWS << 'x' << COLUMNS << '\n';
  std::cout << "Write block cells amount." << '\n';

  int blockedCellsAmount = 0;
  while (1) {
    std::cin >> blockedCellsAmount;
    if (blockedCellsAmount < (ROWS * COLUMNS)) break;
    else std::cout << "Error: amount of blocked cells is bigger!" << '\n';
  }

  if (blockedCellsAmount > 0) {
    std::cout << "Set coords for blocked cell." << '\n';
    for (int idx_i = 1; idx_i <= blockedCellsAmount; idx_i++) {
      while (1) {
        std::cin >> x0;
        std::cin >> y0;
        x0--; y0--;

        if ((0 <= x0) && (x0 < ROWS) && (0 <= y0) && (y0 < COLUMNS))
          break;
        else
          std::cout << "Error: coords outter of the field." << '\n';
      }

      board[x0][y0] = -1;

      if (blockedCellsAmount - idx_i > 0)
        std::cout << "Blocked cell was created, " << (blockedCellsAmount - idx_i) << " more left." << '\n';
      else
        std::cout << "All blocked cell was created" << '\n';
    }
  } else {
    std::cout << "Field without blocked cells." << '\n';
  }


  for (x0 = 0; x0 < ROWS; x0++) {
    for (y0 = 0; y0 < COLUMNS; y0++) {
      accessCount = 0;
      for (int idx_i = 0; idx_i < 8; idx_i++) {
        x1 = x0 + horizontal[idx_i];
        y1 = y0 + vertical[idx_i];

        if ((0 <= x1) && (x1 < ROWS) && (0 <= y1) && (y1 < COLUMNS)) accessCount++;
      }

      accessibility[x0][y0] = accessCount;
    }
  }

  std::cout << "Set horse start position (x, y):" << '\n';

  while (1) {
    // check correct horse position
    std::cin >> x0;
    std::cin >> y0;
    x0--; y0--;
    if ((0 <= x0) && (x0 < ROWS) && (0 <= y0) && (y0 < COLUMNS) && (board[x0][y0] > -1))
      break;

    if (!((0 <= x0) && (x0 < ROWS) && (0 <= y0) && (y0 < COLUMNS))) {
      std::cout << "Error: not valid coords: outter of the field." << '\n';
    } else {
      std::cout << "Error: not valid field - you cant start from blocked cell" << '\n';
    }
  }

  std::cout << "Horse start from (" << x0 + 1 << ", " << y0 + 1 << ")." << '\n';

  // horse walk
  number = 1;
  board[x0][y0] = number;
  int stop = 0;
  for (number = 2; number <= (ROWS * COLUMNS + 1); number++) {
    flag = 1;

    for (int idx_i = 0; idx_i < 8; idx_i++) {
      x1 = x0 + horizontal[idx_i];
      y1 = y0 + vertical[idx_i];

      if ((0 <= x1) && (x1 < ROWS) && (0 <= y1) && (y1 < COLUMNS) && (board[x1][y1] == 0)) {
        accessibility[x1][y1]--;
        if (flag == 1) {
          xMin = x1;
          yMin = y1;
          flag = 0;
        }

        if (accessibility[x1][y1] < accessibility[xMin][yMin]) {
          xMin = x1;
          yMin = y1;
        }
      }
    }

    if (flag == 1) break;

    x0 = xMin;
    y0 = yMin;
    board[x0][y0] = number;
  }

  // system("cls");
  std::cout << '\n';
  printHorse(board, ROWS, COLUMNS);
  std::cout << '\n';

  std::cout << "Progress: " << number - 1 << " step of " << (ROWS * COLUMNS - blockedCellsAmount) << ". Enter for continue..." << '\n';

  std::cout << '\n';
  std::cout << "Horse completed walk! -> " << number - 1 << " steps."   << '\n';

  if (number <= (ROWS * COLUMNS - blockedCellsAmount)) {
    std::cout << "Not available steps more! (available " << number - 1 << " steps form " << (ROWS * COLUMNS - blockedCellsAmount) << "). Horse cant move next." << '\n';
  }

  std::cout << "---------------" << '\n' << '\n';
  // system("pause");
  return 0;
}
