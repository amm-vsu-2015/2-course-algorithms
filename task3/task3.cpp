#include <iostream>

const int SIZE = 8;

int board[SIZE][SIZE];
int results_count = 0;


void showBoard()
{
    for(int a = 0; a < SIZE; ++a)
    {
        for(int b = 0; b < SIZE; ++b)
        {
            std::cout << ((board[a][b]) ? "Q " : ". ");
        }
        std::cout << '\n';
    }
}


bool tryQueen(int row, int column)
{
    for(int i = 0; i < column; ++i)
    {
        if(board[row][i])
        {
            return false;
        }
    }

    for(int i = 1; i <= column && row-i >= 0; ++i)
    {
        if(board[row-i][column-i])
        {
            return false;
        }
    }

    for(int i = 1; i <= column && row+i < SIZE; i++)
    {
        if(board[row+i][column-i])
        {
            return false;
        }
    }

    return true;
}



void setQueen(int column, int &counter, int solution)
{
    if (column == SIZE) counter++;

    if ((counter == solution || counter == 92 - solution + 1) && column == SIZE)
    {
        showBoard();
        std::cout << '\n';
        return;
    }

    for(int i = 0; i < SIZE; ++i)
    {
        if(tryQueen(i, column))
        {
            board[i][column] = 1;
            setQueen(column + 1, counter, solution);
            board[i][column] = 0;
        }
    }

    return;
}

int main()
{
    int counter = 0;
    int solution = 1;

    std::cout << "Write number of solution (1 of 46): ";
    std::cin >> solution;

    std::cout << "Solution number: " << solution << '\n';
    setQueen(0, counter, solution);

    return 0;
}
