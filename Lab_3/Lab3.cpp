#include <iostream>
#include <cmath>

using namespace std;

double f(double x){
    return x*x - 10;
}

double fp(double x){
    return 2 * x;
}

double poldelMethod(double a, double b, double e){
    double c;

    while ((abs(b - a) / 2) > e){
        c = (a + b) / 2;
        if ((f(a) * f(c)) > 0){
            a = c;
        }
        else {
            b = c;
        }

        c = (a + b) / 2;
    }

    return c;
}

double chordMethod(double a, double b, double e){
    double c1;
    double c2;

    do {
        c1 = (a * f(b) - b * f(a)) / (f(b) - f(a));
                if ((f(a) * f(c1)) > 0){
                a = c1;
            }
            else {
                b = c1;
            }
        
        c2 = (a * f(b) - b * f(a)) / (f(b) - f(a));
    } while((c2 - c1) > e);

    return c2;

}

double newtonMethod(double x0, double e){
    double x;

    while ((x0 - x) > e){
        x = x0 - (f(x0) / fp(x0));

        x0 = x;

        x = x0 - (f(x0) / fp(x0));
    }

    return x;
}

int main(){

    double a = 0;
    double b = 5;
    double e = 0.001;
    double x0 = 2;

    cout << "Метод половинного деления: " << poldelMethod(a, b, e) << endl;
    cout << "Метод хорд: " << chordMethod(a, b, e) << endl;
    cout << "Метод Ньютона: " << newtonMethod(x0, e) << endl;


    return 0;
}