#include <iostream>
#include <cmath>
#include <windows.h>

// Функция для вычисления значения подинтегральной функции в точке x
double f(double x) {
    return x * x;
}

// Функция для вычисления интеграла методом трапеции с n разбиениями на отрезке [a, b]
double trapezoidalMethod(double a, double b, int n) {
    double h = (b - a) / n;
    double result = (f(a) + f(b)) / 2;

    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        result += f(x);
    }
    return result * h;
}

// Функция для вычисления интеграла с заданной точностью
double computeIntegralWithPrecision(double a, double b, double precision) {
    int n = 2;
    double prevResult;
    double result = trapezoidalMethod(a, b, n);
    double currentPrecision = std::numeric_limits<double>::max();

    while (currentPrecision > precision) {
        n *= 2;
        prevResult = result;
        result = trapezoidalMethod(a, b, n);
        currentPrecision = abs(result - prevResult);
    }
    return result;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    double a;
    std::cout << "Введите левую границу определенного интеграла:" << std::endl;
    std::cin >> a;

    double b;
    std::cout << "Введите правую границу определенного интеграла:" << std::endl;
    std::cin >> b;

    double precision;
    std::cout << "Введите точность вычислений:" << std::endl;
    std::cin >> precision;

    double integral = computeIntegralWithPrecision(a, b, precision);
    std::cout << "Результат: " << integral;

    return 0;
}
