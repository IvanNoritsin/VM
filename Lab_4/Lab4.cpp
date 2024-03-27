#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

double lagrangeInterpolation(const vector<double>& x, const vector<double>& y, double xi) {
    double result = 0.0;
    for (int i = 0; i < x.size(); i++) {
        double yi = y[i];
        for (int j = 0; j < x.size(); j++) {
            if (j != i) {
                yi *= (xi - x[j]) / (x[i] - x[j]);
            }
        }
        result += yi;
    }
    return result;
}

int main() {
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
    double interpolatedValue = lagrangeInterpolation(x, y, xi);
    
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
