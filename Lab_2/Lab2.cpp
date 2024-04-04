#include <iostream>
#include <vector>

using namespace std;

vector<double> simpleIteration(vector<vector<double>> A, vector<double> b, int maxIter, double accuracy) {
    int n = A.size();
    vector<double> x(n, 0.0);
    vector<double> x_new(n, 0.0);
    
    for (int iter = 0; iter < maxIter; iter++) {
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }
        
        double error = 0.0;
        for (int i = 0; i < n; i++) {
            error += abs(x_new[i] - x[i]);
            x[i] = x_new[i];
        }
        
        if (error < accuracy) {
            break;
        }
    }
    
    return x;
}

int main() {
    vector<vector<double>> A = {{5, -1, 2}, {-2, -10, 3}, {1, 2, 5}};
    vector<double> b = {3, -4, 12};
    
    int maxIter = 3;
    double accuracy = 1e-6;
    
    vector<double> result = simpleIteration(A, b, maxIter, accuracy);
    
    cout << "Результат:" << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << "x" << i << " = " << result[i] << endl;
    }
    
    return 0;
}
