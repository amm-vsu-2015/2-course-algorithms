
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

  int rows = 7;
  int columns = 9;

  int board[rows][columns];

  for (int idx_i = 0; idx_i < rows; idx_i++) {
    for (int idx_j = 0; idx_j < columns; idx_j++) {
      board[idx_i][idx_j] = 0;
    }
  }

  std::cout << "Field created!" << '\n';
  std::cout << "Write block cells amount." << '\n';

  int buffer = 0;
  while (1) {
    std::cin >> buffer;
    if (buffer < (rows * columns)) break;
    else std::cout << "Error: amount of blocked cells is bigger!" << '\n';
  }

  if (buffer > 0) {
    std::cout << "Set coords for blocked cell." << '\n';
    for (int idx_i = 0; idx_i < buffer; idx_i++) {
      while (1) {
        // std::cin >> /* variable */;
      }
    }
  }

  std::cout << "---------------" << '\n';
  int stop;
  cin >> stop;
  return 0;
}
