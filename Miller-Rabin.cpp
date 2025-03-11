#include <bits/stdc++.h>
using namespace std;

/*
Алгоритм Миллера–Рабина — это вероятностный тест простоты числа.
Он используется для проверки, является ли число простым, с высокой вероятностью.

Идея алгоритма:
1. Любое нечетное простое число p можно представить в виде p - 1 = 2^s * d, где d нечетное.
2. Выбираем случайное основание a (1 < a < n - 1) и проверяем условия, которые должны выполняться для простых чисел.
3. Если найден контрпример, число составное.
4. Если несколько раундов не выявили составность, число, вероятно, простое.
*/


// Быстрое возведение в степень по модулю (a^b % mod)
long long power_mod(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // Если степень нечетная, умножаем на base
            res = (res * base) % mod;
        }
        base = (base * base) % mod; // Возводим base в квадрат
        exp /= 2; // Двигаемся к следующему разряду
    }
    return res;
}

// Один раунд теста Миллера–Рабина для проверки числа n на простоту
bool miller_rabin_test(long long n, long long a, long long d, int s) {
    long long x = power_mod(a, d, n); // a^d % n
    if (x == 1 || x == n - 1) {
        return true; // Возможно простое
    }
    for (int i = 0; i < s - 1; i++) { // Проверяем 2^r * d
        x = (x * x) % n;
        if (x == n - 1) {
            return true; // Возможно простое
        }
    }
    return false; // Число составное
}

// Основная функция теста Миллера–Рабина
bool is_prime(long long n, int iterations = 30) {
    // Параметр iterations задает количество раундов тестирования, что влияет на точность проверки, больше параметр - дольше работа, но выше точность
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) { // Представляем n-1 в виде 2^s * d
        d /= 2;
        s++;
    }

    srand(time(0)); // Инициализация генератора случайных чисел
    for (int i = 0; i < iterations; i++) {
        long long a = 2 + rand() % (n - 3); // Выбираем случайное a в диапазоне [2, n-2]
        if (!miller_rabin_test(n, a, d, s)) {
            return false; // Число составное
        }
    }
    return true; // Вероятно простое
}

int main() {
    long long num;
    cout << "Введите число для проверки на простоту: ";
    cin >> num;
    if (is_prime(num)) {
        cout << num << " вероятно простое" << endl;
    } else {
        cout << num << " составное" << endl;
    }
}
