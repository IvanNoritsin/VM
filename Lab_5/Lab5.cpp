#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std; 

double aitkenInterpolation(const vector<double> &x, const vector<double> &y, double xi){
    int N = x.size();
    vector<vector<double>> table(N, vector<double>(N));

    for (int i = 0; i < N; i++){
        table[i][0] = y[i];
    }

    for (int j = 1; j < N; j++) {
        for (int i = 0; i < N - j; i++) {
            table[i][j] = (table[i + 1][j - 1] * (xi - x[i]) - table[i][j - 1] * (xi - x[i + j])) / (x[i + j] - x[i]);
        }
    }

    return table[0][N - 1];
}

int main(){
    vector<double> x;
    vector<double> y;

    ifstream file("dataInput.txt");

    double num1, num2;
    while (file >> num1 >> num2) {
        x.push_back(num1);
        y.push_back(num2);
    }

    file.close();

    double xi = 2.56;

    double interpolatedValue = aitkenInterpolation(x, y, xi);

    cout << "Interpolated value at x = " << xi << ": " << interpolatedValue << endl;

    x.push_back(xi);
    y.push_back(interpolatedValue);

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    ofstream fileOut("dataOutput.txt");

    for (int i = 0; i < x.size(); i++) {
        fileOut << x[i] << " " << y[i] << endl;
    }

    fileOut.close();

    system("gnuplot plotScript.gnu");

    return 0;

}