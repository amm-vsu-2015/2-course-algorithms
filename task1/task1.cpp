
/**
	Сравнить скорость выполнения двух сортировок:
  1. Сортировка Хоара (быстрая сортировка);
  2. Вставками (+бисекция).

  Входные данные для проверки:

  Генерируются программно.
*/

#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

const int LENGTH_ARRAY = 20000;
const int START_ARRAY = 1; // from 1 to 150k


void generateArray(int* array) {
  srand(time(0));
  for (int i = START_ARRAY; i < LENGTH_ARRAY; i++) {
    array[i] = rand() % 100000 + 1; // 1..100
  }
}



void copyArray(int* original, int* clone) {
  for (int i = START_ARRAY; i < LENGTH_ARRAY; i++) {
    clone[i] = original[i]; // copy array
  }
}



void outputArray(int* array) {
  for (int i = START_ARRAY; i < LENGTH_ARRAY; i++) {
    cout << array[i] << ' '; // copy array
    if (i % 15 == 0) {
      // cout << endl;
    }
  }
}



void insertSort(int* array) {
  int j = 0;
  double value;

  for (int i = START_ARRAY + 1; i < LENGTH_ARRAY; i++) {
    value = array[i];
    array[0] = value; // barier
    j = i;

    while (value < array[j - 1]) {
      array[j] = array[j - 1];
      j--;
    }
    array[j] = value;
  }
}



void quickSort(int* array, int first, int last) {
    int i = first, j = last, value = array[(first + last) / 2];

    do {
        while (array[i] < value) i++;
        while (array[j] > value) j--;

        if (i <= j) {
            if (array[i] > array[j]) swap(array[i], array[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        quickSort(array, i, last);
    if (first < j)
        quickSort(array, first, j);
}


int main() {
  int stop, times, insertionTime, quickTime;

  // init random array
  int* insertArray = new int[LENGTH_ARRAY];
  int* quickArray = new int[LENGTH_ARRAY];

  generateArray(insertArray);
  copyArray(insertArray, quickArray);

  // cout << endl << endl << "SOURCE ARRAY:" << endl;
  // outputArray(insertArray);

  // insertSort
  // cout << endl << endl << "INSERTED ARRAY:" << endl;
  times = clock();
  insertSort(insertArray);
  insertionTime = clock() - times;
  // outputArray(insertArray);


  // cout << endl << endl << "QUICK TWICE:" << endl;

  // quickSort
  times = clock();
  quickSort(quickArray, START_ARRAY, LENGTH_ARRAY - 1);
  quickTime = clock() - times;
  // outputArray(quickArray);


  cout.setf(ios::fixed); // fixed output
  cout.precision(4);     // accc
  cout << endl;
  cout << endl << "insertion: " << ((float) insertionTime) / CLOCKS_PER_SEC << 's' << endl;
  cout << endl << "quick:     " << ((float) quickTime) / CLOCKS_PER_SEC << 's' << endl;

  cin >> stop;
  return 0;
}
