#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void inputFile(vector<vector<double>>& A) {
    ifstream input("input.txt");
    if (!input.is_open()) {
        cout << "Ошибка при открытии файла" << endl;
        exit(1);
    }

    int n;
    input >> n;

    A.resize(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            input >> A[i][j];
        }
    }
    input.close();
}

void gaussMethod(vector<vector<double>>& A, vector<double>& x) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > abs(A[max_row][i])) {
                max_row = k;
            }
        }
        for (int k = i; k <= n; k++) {
            swap(A[max_row][k], A[i][k]);
        }

        for (int k = i + 1; k < n; k++) {
            double f = A[k][i] / A[i][i];
            for (int j = i; j <= n; j++) {
                A[k][j] -= A[i][j] * f;
            }
        }
    }

    x.resize(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = A[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

void printResult(const vector<double>& x) {
    cout << "Решение СЛАУ:" << endl;
    for (int i = 0; i < x.size(); i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }
}

int main() {
    vector<vector<double>> A;
    inputFile(A);

    vector<double> x;
    gaussMethod(A, x);

    printResult(x);

    return 0;
}