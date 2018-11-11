

/**

Задача о восьми ферзях:
1. Узнать количество положение ферзей, при которых они не бьют друг друга.
2. Выбрать одну пару компинаций (т.к. положения будут зеркальными)
3. Положения зеркальны относительно горизонтальной плоскости.

Входные данные для проверки: номер решения (1 из 46)
Результат: вывод решения и решения зеркального ему (относительно нижней границы матрицы)

Принцип работы такой, что каждый ферзь смотрит только на строку, в которой находится и по левой верхней и левой нижней диагонили
Это позволяет контролировать уже установленные фигуры. Так как справа (справа сверху и справа снизу) фигуры еще не установлены.
Нет смысла проверять правую часть.

По логике работы программы происходит постепенный обход всех строк и столбцов. Инкремент строки происходит с помощью цикла, а
инкремент столбца – шаг рекурсии. Получается, что каждый раз, когда установлена фигура, происходит смещений на один столбец вправо,
а затем постепенный проход от верхней строки к нижней до тех пор, пока не будет найдено место, куда будет установлена фигура (затем снова смешение).

В случае, когда происходит такое заполнение, когда не остается свободных мест на доске для других фигур, но фигур менее 8, происходит
постепенной снятие фигур, начиная с конца.

Для примера указан результат выполнения программы:

. . O . . . . .
. . . . . O . .
. . . O . . . .
. O . . . . . .
. . . . . . . O
. . . . O . . .
. . . . . . O .
O . . . . . . .

Логика оценки безопасной позиции фигуры (x):
. . O . . . . .
x . . . . O . .
. x . O . . . .
. O x . . . . .
. . . x . . . O
x x x x O . . .
. . . x . . O .
O . x . . . . .

*/
#include <iostream>

const int SIZE = 8;

int board[SIZE][SIZE];

void showBoard() {
    for (int idx_a = 0; idx_a < SIZE; ++idx_a) {
        for (int idx_b = 0; idx_b < SIZE; ++idx_b) {
            std::cout << ((board[idx_a][idx_b]) ? "O " : ". ");
        }
        std::cout << '\n';
    }
}


/// Queens watch only on row and top left/right diagonalies.
/// They don't need to know what under them (bc, nothing now).
bool tryQueen(int row, int column) {
    // check stroke (left/right sides) on safety setups
    for (int idx_i = 0; idx_i < column; ++idx_i) {
        if (board[row][idx_i]) {
            return false;
        }
    }

    // check diag top-left from queen
    for (int idx_i = 1; idx_i <= column && (row - idx_i >= 0); ++idx_i) {
        if(board[row - idx_i][column - idx_i]) {
            return false;
        }
    }

    // check diag bottom-left from queen
    for (int idx_i = 1; idx_i <= column && (row + idx_i < SIZE); idx_i++) {
        if(board[row + idx_i][column - idx_i]) {
            return false;
        }
    }

    return true;
}

/// Function checks places for setup Queen. And setups her if place safety for figure.
/// It is recursion function. Before recursive calling, setups queen on current place.
/// Function can unset latest queen from her places if Queen's count less than SIZE on board.
///
/// Parameters:
///   @counter: is number of solution that's program calculating in this moment (func recursive context).
///   @solution: is user's selected number of sulution for queens positions.
void setQueen(int column, int &counter, int solution) {
    if (column == SIZE) counter++;

    // Show selected suluions or similar mirrored solution, while columns == size (means 8 queens on board)
    // Ends the recursive stack after 8 Queen on board
    if ((counter == solution || counter == 92 - solution + 1) && column == SIZE) {
        showBoard();
        std::cout << '\n';
        return;
    }

    for (int idx_i = 0; idx_i < SIZE; ++idx_i) {
        // if can't setup queen on this position, increment row and check again.
        if (tryQueen(idx_i, column)) {
            // setup queen on current position
            board[idx_i][column] = 1;
            // trying to setup queen on the right column (and any row)
            setQueen(column + 1, counter, solution);
            // after recursion clear current queen position
            // this is gives a opportinity for clearing board after program solvation
            // and clear latest Quees, because bad position blocking other queens
            // (this useful because we need to place 8 queens on board)
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
