#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Values {
    float x;
    float y;
};

float newtonInterpolationFirst(vector<float> &x, vector<vector<float>> &y, int n, float xi){
    int i, j; 
    float h, q, interpolatedValue, p; 
    for (j = 1; j < n; j++) { 
        for (i = 0; i < n - j; i++) { 
            y[i][j] = y[i + 1][j - 1] - y[i][j - 1]; 
        } 
    }

    cout << "-----------FIRST FORMULA-----------" << endl; 
    for (i = 0; i < n; i++) { 
        cout << endl;
        for (j = 0; j < n - i; j++) { 
            printf("%f\t", y[i][j]);
        } 
    }

    cout << endl;

    p = 1.0; 
    interpolatedValue = y[0][0]; 
    h = x[1] - x[0]; 
    q = (xi - x[0]) / h; 
    for (j = 1; j < n; j++) { 
        p = p * (q - j + 1) / j; 
        interpolatedValue = interpolatedValue + p * y[0][j]; 
    } 

    cout << "Interpolated value at x = " << xi << ": " << interpolatedValue << endl;

    return interpolatedValue;
}

float newtonInterpolationSecond(vector<float> &x, vector<vector<float>> &y, int n, float xi){
    int i, j; 
    float h, q, interpolatedValue, p; 
    for (j = 1; j < n; j++) { 
        for (i = 0; i < n - j; i++) { 
            y[i][j] = y[i + 1][j - 1] - y[i][j - 1]; 
        } 
    }

    cout << "-----------SECOND FORMULA-----------" << endl; 
    for (i = 0; i < n; i++) { 
        cout << endl;
        for (j = 0; j < n - i; j++) { 
            printf("%f\t", y[i][j]);
        } 
    }

    cout << endl;

    p = 1.0; 
    interpolatedValue = y[n - 1][0]; 
    h = x[1] - x[0]; 
    q = (xi - x[n - 1]) / h; 
    for (j = 1; j < n; j++) { 
    p = p * (q + j - 1) / j; 
    interpolatedValue = interpolatedValue + p * y[n - (j + 1)][j];
    }

    cout << "Interpolated value at x = " << xi << ": " << interpolatedValue << endl;

    return interpolatedValue;
}

bool cmp (const Values& c1, const Values& c2) {
    return c1.x < c2.x;
}

int main(){

    vector<float> x = {1, 1.5, 2, 2.5};
    vector<vector<float>> y = { 
        { 1, 0, 0, 0 }, 
        { 1.2247, 0, 0, 0 }, 
        { 1.4142, 0, 0, 0 }, 
        { 1.5811, 0, 0, 0 }, 
    }; 

    float xi = 1.69;
    int n = y.size();
    float interpolatedValue_first;
    float interpolatedValue_second;

    interpolatedValue_first = newtonInterpolationFirst(x, y, n, xi);
    cout << endl;
    interpolatedValue_second = newtonInterpolationSecond(x, y, n, xi);

    vector<float> x_first = x;
    vector<float> x_second = x;
    vector<float> y_first;
    vector<float> y_second;

    for (int i = 0; i < n; i++){
        y_first.push_back(y[i][0]);
        y_second.push_back(y[i][0]);
    }

    x_first.push_back(xi);
    y_first.push_back(interpolatedValue_first);

    x_second.push_back(xi);
    y_second.push_back(interpolatedValue_first);


    vector<Values> values_first;
    vector<Values> values_second;
    Values a;

    for (int i = 0; i < n + 1; i++){
        a.x = x_first[i];
        a.y = y_first[i];
        values_first.push_back(a);
    }

    sort(values_first.begin(), values_first.end(), cmp);

    ofstream fileOut("dataOutput.txt");

    for (int i = 0; i < n + 1; i++) {
        fileOut << values_first[i].x << " " << values_first[i].y << endl;
    }

    fileOut.close();

    system("gnuplot plotScript.gnu");

    return 0;
}