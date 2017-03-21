
/**
	Сравнить скорость выполнения двух сортировок:
  1. Сортировка Хоара, итеративная без рекурсии(быстрая сортировка);
  2. Прямым выбором.

  Входные данные для проверки:
  Генерируются программно.
*/

#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

const int START_ARRAY = 0;
const int LENGTH_ARRAY = 25000;
const int STACK_DEPTH = 2048; // iteration of quick sort


void quickSort(int* arr) {
  int i, j, left, right, sizeCount;
  int value, buffer, size;
  int* deepDown = new int[STACK_DEPTH];
  int* deepUp = new int[STACK_DEPTH];

  size = LENGTH_ARRAY;
  sizeCount = 1;

  deepDown[sizeCount] =  0;
  deepUp[sizeCount] =  size - 1;

  do {
    left = deepDown[sizeCount];
    right = deepUp[sizeCount];
    sizeCount--;
    do {
      i = left;
      j = right;
  	  value  =  arr[(left + right) / 2];

      // partiotion
      do {
        while (arr[i] < value) i++;
        while (value < arr[j]) j--;

        if (i <= j) {
          buffer  =  arr[i];
          arr[i]  =  arr[j];
          arr[j]  =  buffer;
          i++; j--;
        }
      } while(i < j);

      if (i < right) {
        sizeCount++;
        deepDown[sizeCount] =  i;
        deepUp[sizeCount] =  right;
      }

      right = j;
    } while (left < right);
  } while (sizeCount > 0);
}

void selectionSort(int* arr) {
  int i, j, n, k, value;
  n = LENGTH_ARRAY - 1;
  for (i = 0; i < n - 1; i++) {
    k = i;
    value = arr[i];

    for (j = i + 1; j < n + 1; j++) {
      if (arr[j] < value) {
        k = j;
        value = arr[k];
      }
    }

    arr[k] = arr[i];
    arr[i] = value;
  }
}


void generateArray(int* array) {
  srand(time(0));
  for (int i = START_ARRAY; i < LENGTH_ARRAY; i++) {
    array[i] = rand() % 25000 + 1; // 1..100
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
    if (i % 20 == 0) {
      cout << endl;
    }
  }
}

int main() {
  int stop, times, selectionTime, quickTime;
  int* selectionArray = new int[LENGTH_ARRAY];
  int* quickArray = new int[LENGTH_ARRAY];

  srand(time(0));

  generateArray(selectionArray);
  copyArray(selectionArray, quickArray);

  times = clock();
  selectionSort(selectionArray);
  selectionTime = clock() - times;

  times = clock();
  quickSort(quickArray);
  quickTime = clock() - times;

  // outputArray(selectionArray);
  // outputArray(quickArray);

  cout.setf(ios::fixed); // fixed output
  cout.precision(4);     // accc
  cout << "SORTS:" << endl;
  cout << endl << "selection time: " << ((float) selectionTime) / CLOCKS_PER_SEC << 's' << endl;
  cout << endl << "quick time:     " << ((float) quickTime) / CLOCKS_PER_SEC << 's' << endl;


  cin >> stop;
  return 0;
}
