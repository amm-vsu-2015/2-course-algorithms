

/**

Задача о восьми ферзях:
1. Узнать количество положение ферзей, при которых они не бьют друг друга.
2. Выбрать одну пару компинаций (т.к. положения будут зеркальными)
3. Положения зеркальны относительно горизонтальной плоскости.

Входные данные для проверки: номер решения (1 из 46)
Результат: вывод решения и решения зеркального ему (относительно нижней границы матрицы)

*/
#include <iostream>

const int SIZE = 8;

int board[SIZE][SIZE];
int results_count = 0;


void showBoard() {
    for (int idx_a = 0; idx_a < SIZE; ++idx_a) {
        for (int idx_b = 0; idx_b < SIZE; ++idx_b) {
            std::cout << ((board[idx_a][idx_b]) ? "O " : ". ");
        }
        std::cout << '\n';
    }
}


bool tryQueen(int row, int column) {
    for (int idx_i = 0; idx_i < column; ++idx_i) {
        if (board[row][idx_i]) {
            return false;
        }
    }

    for(int idx_i = 1; idx_i <= column && (row - idx_i >= 0); ++idx_i) {
        if(board[row - idx_i][column - idx_i]) {
            return false;
        }
    }

    for(int idx_i = 1; idx_i <= column && (row + idx_i < SIZE); idx_i++) {
        if(board[row + idx_i][column - idx_i]) {
            return false;
        }
    }

    return true;
}



void setQueen(int column, int &counter, int solution) {
    if (column == SIZE) counter++;

    // show selected suluions and similar mirrored solution
    if ((counter == solution || counter == 92 - solution + 1) && column == SIZE) {
        showBoard();
        std::cout << '\n';
        return;
    }

    for(int idx_i = 0; idx_i < SIZE; ++idx_i) {
        if(tryQueen(idx_i, column)) {
            board[idx_i][column] = 1;
            setQueen(column + 1, counter, solution);
            board[idx_i][column] = 0;
        }
    }
    return;
}

int main() {
    int counter = 0;
    int solution = 1;

    std::cout << "Write number of solution (1 of 46): ";
    std::cin >> solution;

    std::cout << "Solution number: " << solution << '\n';
    setQueen(0, counter, solution);

    return 0;
}
