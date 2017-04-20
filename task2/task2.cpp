
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

const int ROWS = 7;
const int COLUMNS = 9;

void printHorse(int position[ROWS][COLUMNS], int ROWS, int COLUMNS);
int isInsideBoard(int x, int y);

void printHorse(int position[ROWS][COLUMNS], int ROWS, int COLUMNS) {
  for (int idx_k = 0; idx_k < ROWS; idx_k++) {
    for (int idx_s = 0; idx_s < COLUMNS; idx_s++) {
      if (position[idx_k][idx_s] == -1) std::cout << setw(8) <<  " [*]";
      if (position[idx_k][idx_s] == 0)  std::cout << setw(8) <<  " [ ]";
      if (position[idx_k][idx_s] >  0)  std::cout << setw(8) << position[idx_k][idx_s];
    }
    std::cout << '\n' << '\n';
  }
}

int isInsideBoard(int x, int y) {
  if ((0 <= x) && (x < ROWS) && (0 <= y) && (y < COLUMNS))
    return 1;
  else
    return 0;
}


int main() {

  int accessCount = 0, isStepDenied = 0, x_min = 0, y_min = 0, x = 0, y = 0, x_raw = 0, y_raw = 0;

  int accessibility[ROWS][COLUMNS];
  int board[ROWS][COLUMNS];

  // step map
  int horizontal[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
  int vertical[8]   = { -1, -2, -2, -1, 1, 2, 2, 1 };

  for (int idx_i = 0; idx_i < ROWS; idx_i++) {
    for (int idx_j = 0; idx_j < COLUMNS; idx_j++) {
      board[idx_i][idx_j] = 0;
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
        std::cin >> x_raw;
        std::cin >> y_raw;
        x_raw--; y_raw--;

        if (isInsideBoard(x_raw, y_raw))
          break;
        else
          std::cout << "Error: coords outter of the field." << '\n';
      }

      board[x_raw][y_raw] = -1;

      if (blockedCellsAmount - idx_i > 0)
        std::cout << "Blocked cell was created, " << (blockedCellsAmount - idx_i) << " more left." << '\n';
      else
        std::cout << "All blocked cell was created" << '\n';
    }
  } else {
    std::cout << "Field without blocked cells." << '\n';
  }


  for (int idx_x = 0; idx_x < ROWS; idx_x++) {
    for (int idx_y = 0; idx_y < COLUMNS; idx_y++) {
      accessCount = 0;
      for (int idx_i = 0; idx_i < 8; idx_i++) {
        x = idx_x + horizontal[idx_i];
        y = idx_y + vertical[idx_i];

        if (isInsideBoard(x, y)) accessCount++;
      }

      accessibility[idx_x][idx_y] = accessCount;
    }
  }

  std::cout << "Set horse start position (x, y):" << '\n';

  while (1) {
    // check correct horse position
    std::cin >> x_raw;
    std::cin >> y_raw;
    x_raw--; y_raw--;

    if (isInsideBoard(x_raw, y_raw) && (board[x_raw][y_raw] > -1)) break;

    if (!isInsideBoard(x_raw, y_raw))
      std::cout << "Error: not valid coords: outter of the field." << '\n';
    else
      std::cout << "Error: not valid field - you cant start from blocked cell" << '\n';
  }

  std::cout << "Horse start from (" << x_raw + 1 << ", " << y_raw + 1 << ")." << '\n';

  // horse walk
  int stepNumber = 1;
  board[x_raw][y_raw] = stepNumber;

  for (stepNumber = 2; stepNumber <= (ROWS * COLUMNS + 1); stepNumber++) {
    isStepDenied = 1;

    for (int idx_i = 0; idx_i < 8; idx_i++) {
      x = x_raw + horizontal[idx_i];
      y = y_raw + vertical[idx_i];

      if (isInsideBoard(x, y) && (board[x][y] == 0)) {
        accessibility[x][y]--;
        if (isStepDenied == 1) {
          x_min = x;
          y_min = y;
          isStepDenied = 0;
        }

        if (accessibility[x][y] < accessibility[x_min][y_min]) {
          x_min = x;
          y_min = y;
        }
      }
    }

    if (isStepDenied == 1) break;

    x_raw = x_min;
    y_raw = y_min;
    board[x_raw][y_raw] = stepNumber;
  }

  // system("cls");
  std::cout << '\n';
  printHorse(board, ROWS, COLUMNS);
  std::cout << '\n';

  std::cout << "Progress: " << stepNumber - 1 << " step of " << (ROWS * COLUMNS - blockedCellsAmount) << ". Enter for continue..." << '\n';

  std::cout << '\n';
  std::cout << "Horse completed walk! -> " << stepNumber - 1 << " steps."   << '\n';

  if (stepNumber <= (ROWS * COLUMNS - blockedCellsAmount)) {
    std::cout << "Not available steps more! (available " << stepNumber - 1 << " steps form " << (ROWS * COLUMNS - blockedCellsAmount) << "). Horse cant move next." << '\n';
  }

  std::cout << "---------------" << '\n' << '\n';
  // system("pause");
  return 0;
}
