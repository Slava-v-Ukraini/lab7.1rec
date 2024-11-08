#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

// Рекурсивна функція для заповнення матриці випадковими значеннями
void Create(int a[8][7], const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0) {
    if (i >= rowCount) return; // Вихід з рекурсії, коли пройдено всі рядки
    if (j < colCount) {
        a[i][j] = Low + rand() % (High - Low + 1);
        Create(a, rowCount, colCount, Low, High, i, j + 1); // Рекурсія для наступного стовпчика
    }
    else {
        Create(a, rowCount, colCount, Low, High, i + 1, 0); // Рекурсія для наступного рядка
    }
}

// Рекурсивна функція для друку матриці
void Print(const int a[8][7], int rowCount, int colCount, int i = 0, int j = 0) {
    if (i >= rowCount) return; // Вихід з рекурсії, коли пройдено всі рядки
    if (j < colCount) {
        cout << setw(4) << a[i][j];
        Print(a, rowCount, colCount, i, j + 1); // Рекурсія для наступного стовпчика
    }
    else {
        cout << endl;
        Print(a, rowCount, colCount, i + 1, 0); // Рекурсія для наступного рядка
    }
}

// Функція для визначення, чи підходить елемент під заданий критерій
bool Criteria(int value, int row, int col) {
    return value > 0 && !(row % 2 == 0 && col % 2 == 0);
}

// Рекурсивна функція для обробки матриці (підрахунок і заміна на нулі)
void ProcessMatrix(int a[8][7], int rowCount, int colCount, int& count, int& sum, int i = 0, int j = 0) {
    if (i >= rowCount) return; // Вихід з рекурсії, коли пройдено всі рядки
    if (j < colCount) {
        if (Criteria(a[i][j], i, j)) {
            sum += a[i][j];
            count++;
            a[i][j] = 0; // Заміна на нуль
        }
        ProcessMatrix(a, rowCount, colCount, count, sum, i, j + 1); // Рекурсія для наступного стовпчика
    }
    else {
        ProcessMatrix(a, rowCount, colCount, count, sum, i + 1, 0); // Рекурсія для наступного рядка
    }
}

// Функція для порівняння двох рядків матриці
bool CompareRows(const int row1[7], const int row2[7]) {
    if (row1[0] != row2[0]) return row1[0] > row2[0]; // Спадання за першим стовпчиком
    if (row1[1] != row2[1]) return row1[1] > row2[1]; // Спадання за другим стовпчиком
    return row1[2] < row2[2]; // Зростання за третім стовпчиком
}

// Рекурсивна функція для сортування рядків матриці
void SortMatrix(int a[8][7], int rowCount, int colCount, int i = 0, int j = 1) {
    if (i >= rowCount - 1) return; // Вихід з рекурсії, коли пройдено всі рядки
    if (j < rowCount) {
        if (!CompareRows(a[i], a[j])) {
            for (int k = 0; k < colCount; k++) {
                swap(a[i][k], a[j][k]); // Обмін рядками
            }
        }
        SortMatrix(a, rowCount, colCount, i, j + 1); // Рекурсія для наступного рядка
    }
    else {
        SortMatrix(a, rowCount, colCount, i + 1, i + 2); // Рекурсія для наступного ряду порівняння
    }
}

int main() {
    srand(unsigned(time(NULL)));

    const int rowCount = 8;
    const int colCount = 7;
    const int Low = -8;
    const int High = 42;

    int a[rowCount][colCount];
    int count = 0, sum = 0;

    // Генерація матриці
    Create(a, rowCount, colCount, Low, High);
    cout << "Initial Matrix:" << endl;
    Print(a, rowCount, colCount);

    // Обробка матриці
    ProcessMatrix(a, rowCount, colCount, count, sum);
    cout << "\nMatrix after processing (elements replaced by zero):" << endl;
    Print(a, rowCount, colCount);
    cout << "Count of elements matching criteria: " << count << endl;
    cout << "Sum of elements matching criteria: " << sum << endl;

    // Сортування матриці
    SortMatrix(a, rowCount, colCount);
    cout << "\nSorted Matrix:" << endl;
    Print(a, rowCount, colCount);

    return 0;
}

