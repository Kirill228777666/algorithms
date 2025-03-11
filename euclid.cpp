#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) { // Пока b не равно нулю
        int t = b; // Сохраняем значение b во временной переменной
        b = a % b; // Присваиваем b остаток от деления a на b
        a = t; // Присваиваем a старое значение b
    }
    return a; // Когда b становится 0, a содержит НОД
}

int main() {
    int num1, num2;
    cin >> num1 >> num2;
    // Вычисление и вывод наибольшего общего делителя
    cout << "НОД(" << num1 << ", " << num2 << ") = " << gcd(num1, num2) << endl;
}
