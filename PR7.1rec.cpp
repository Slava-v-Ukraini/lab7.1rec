#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

// ���������� ������� ��� ���������� ������� ����������� ����������
void Create(int a[8][7], const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0) {
    if (i >= rowCount) return; // ����� � ������, ���� �������� �� �����
    if (j < colCount) {
        a[i][j] = Low + rand() % (High - Low + 1);
        Create(a, rowCount, colCount, Low, High, i, j + 1); // ������� ��� ���������� ���������
    }
    else {
        Create(a, rowCount, colCount, Low, High, i + 1, 0); // ������� ��� ���������� �����
    }
}

// ���������� ������� ��� ����� �������
void Print(const int a[8][7], int rowCount, int colCount, int i = 0, int j = 0) {
    if (i >= rowCount) return; // ����� � ������, ���� �������� �� �����
    if (j < colCount) {
        cout << setw(4) << a[i][j];
        Print(a, rowCount, colCount, i, j + 1); // ������� ��� ���������� ���������
    }
    else {
        cout << endl;
        Print(a, rowCount, colCount, i + 1, 0); // ������� ��� ���������� �����
    }
}

// ������� ��� ����������, �� �������� ������� �� ������� �������
bool Criteria(int value, int row, int col) {
    return value > 0 && !(row % 2 == 0 && col % 2 == 0);
}

// ���������� ������� ��� ������� ������� (��������� � ����� �� ���)
void ProcessMatrix(int a[8][7], int rowCount, int colCount, int& count, int& sum, int i = 0, int j = 0) {
    if (i >= rowCount) return; // ����� � ������, ���� �������� �� �����
    if (j < colCount) {
        if (Criteria(a[i][j], i, j)) {
            sum += a[i][j];
            count++;
            a[i][j] = 0; // ����� �� ����
        }
        ProcessMatrix(a, rowCount, colCount, count, sum, i, j + 1); // ������� ��� ���������� ���������
    }
    else {
        ProcessMatrix(a, rowCount, colCount, count, sum, i + 1, 0); // ������� ��� ���������� �����
    }
}

// ������� ��� ��������� ���� ����� �������
bool CompareRows(const int row1[7], const int row2[7]) {
    if (row1[0] != row2[0]) return row1[0] > row2[0]; // �������� �� ������ ����������
    if (row1[1] != row2[1]) return row1[1] > row2[1]; // �������� �� ������ ����������
    return row1[2] < row2[2]; // ��������� �� ����� ����������
}

// ���������� ������� ��� ���������� ����� �������
void SortMatrix(int a[8][7], int rowCount, int colCount, int i = 0, int j = 1) {
    if (i >= rowCount - 1) return; // ����� � ������, ���� �������� �� �����
    if (j < rowCount) {
        if (!CompareRows(a[i], a[j])) {
            for (int k = 0; k < colCount; k++) {
                swap(a[i][k], a[j][k]); // ���� �������
            }
        }
        SortMatrix(a, rowCount, colCount, i, j + 1); // ������� ��� ���������� �����
    }
    else {
        SortMatrix(a, rowCount, colCount, i + 1, i + 2); // ������� ��� ���������� ���� ���������
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

    // ��������� �������
    Create(a, rowCount, colCount, Low, High);
    cout << "Initial Matrix:" << endl;
    Print(a, rowCount, colCount);

    // ������� �������
    ProcessMatrix(a, rowCount, colCount, count, sum);
    cout << "\nMatrix after processing (elements replaced by zero):" << endl;
    Print(a, rowCount, colCount);
    cout << "Count of elements matching criteria: " << count << endl;
    cout << "Sum of elements matching criteria: " << sum << endl;

    // ���������� �������
    SortMatrix(a, rowCount, colCount);
    cout << "\nSorted Matrix:" << endl;
    Print(a, rowCount, colCount);

    return 0;
}

