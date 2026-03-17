#include <iostream>
#include <vector>
using namespace std;

int n;    
// Глобальные переменные для 1-го решения
vector<vector<int>> board;      
int solutionCount = 0;     

//Глобальные переменные для 2-го решения
const int MAXN = 20;
int S[MAXN + 1];
int Q[MAXN + 1];
int R[2 * MAXN + 1];
int L[2 * MAXN + 2];
int ch;

void Queen(int j);
void Place_for_Quin(int stolbec);
bool Safe_Plase(int stroka, int stolbec);

int main() {
    setlocale(LC_ALL, "RU");

    cout << "Введите количество ферзей" << endl;
    cin >> n;

    cout << endl;
    cout << "Выберите способ решения" << endl;
    cout << "1.Матрица" << endl;
    cout << "2.Лекция" << endl;
    int t;
    cin >> t;
    if (t == 1) {
        
        // Инициализация доски (матрицы) нулями
        board.assign(n, vector<int>(n, 0));

        solutionCount = 0;
        Place_for_Quin(0);

        cout << "Всего найдено решений: " << solutionCount << endl;

    }
    else {
        for (int i = 1; i <= n; i++) {
            S[i] = 0;
        }
        for (int i = 1; i <= 2 * n - 1; i++) {
            R[i] = 0;
        }
        for (int i = 2; i <= 2 * n; i++) {
            L[i] = 0;
        }

        ch = 0;
        Queen(1);
        cout << "Всего решений: " << ch << endl;
    }

    return 0;
}

void Queen(int j) {
    for (int i = 1; i <= n; i++) {
        if (S[i] == 0 && R[j - i + n] == 0 && L[j + i] == 0) {
            S[i] = 1;
            R[j - i + n] = 1;
            L[j + i] = 1;
            Q[j] = i;

            if (j == n) {
                ch++;
                for (int k = 1; k <= n; k++) {
                    for (int i = 1; i <= n; i++) {
                        if (i != Q[k]) {
                            cout << ". ";
                        }
                        else cout << "Q ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            else {
                Queen(j + 1);
            }

            S[i] = 0;
            R[j - i + n] = 0;
            L[j + i] = 0;
        }
    }
}

//Функция для решения матрицами
void Place_for_Quin(int stolbec) {
    if (stolbec >= n) {
        solutionCount++;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != 1) {
                    cout << ". ";
                }
                else cout << "Q ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    for (int stroka = 0; stroka < n; stroka++) {
        if (Safe_Plase(stroka,stolbec)) {
            // Ставим ферзя
            board[stroka][stolbec] = 1;

            Place_for_Quin(stolbec + 1);

            board[stroka][stolbec] = 0;
        }
    }
}

bool Safe_Plase(int stroka, int stolbec) {
    // Проверка строки (слева от текущей позици)
    for (int j = 0; j < stolbec; j++) {
        if (board[stroka][j] == 1) return false;
    }

    // Проверка верхней диагонали (влево-вверх)
    for (int i = stroka, j = stolbec; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false;
    }

    // Проверка нижней диагонали (влево-вниз)
    for (int i = stroka, j = stolbec; i < n && j >= 0; i++, j--) {
        if (board[i][j] == 1) return false;
    }

    return true;
}
