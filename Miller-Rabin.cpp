#include <bits/stdc++.h>
using namespace std;

/*
�������� �������������� � ��� ������������� ���� �������� �����.
�� ������������ ��� ��������, �������� �� ����� �������, � ������� ������������.

���� ���������:
1. ����� �������� ������� ����� p ����� ����������� � ���� p - 1 = 2^s * d, ��� d ��������.
2. �������� ��������� ��������� a (1 < a < n - 1) � ��������� �������, ������� ������ ����������� ��� ������� �����.
3. ���� ������ �����������, ����� ���������.
4. ���� ��������� ������� �� ������� �����������, �����, ��������, �������.
*/


// ������� ���������� � ������� �� ������ (a^b % mod)
long long power_mod(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // ���� ������� ��������, �������� �� base
            res = (res * base) % mod;
        }
        base = (base * base) % mod; // �������� base � �������
        exp /= 2; // ��������� � ���������� �������
    }
    return res;
}

// ���� ����� ����� �������������� ��� �������� ����� n �� ��������
bool miller_rabin_test(long long n, long long a, long long d, int s) {
    long long x = power_mod(a, d, n); // a^d % n
    if (x == 1 || x == n - 1) {
        return true; // �������� �������
    }
    for (int i = 0; i < s - 1; i++) { // ��������� 2^r * d
        x = (x * x) % n;
        if (x == n - 1) {
            return true; // �������� �������
        }
    }
    return false; // ����� ���������
}

// �������� ������� ����� ��������������
bool is_prime(long long n, int iterations = 30) {
    // �������� iterations ������ ���������� ������� ������������, ��� ������ �� �������� ��������, ������ �������� - ������ ������, �� ���� ��������
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) { // ������������ n-1 � ���� 2^s * d
        d /= 2;
        s++;
    }

    srand(time(0)); // ������������� ���������� ��������� �����
    for (int i = 0; i < iterations; i++) {
        long long a = 2 + rand() % (n - 3); // �������� ��������� a � ��������� [2, n-2]
        if (!miller_rabin_test(n, a, d, s)) {
            return false; // ����� ���������
        }
    }
    return true; // �������� �������
}

int main() {
    long long num;
    cout << "������� ����� ��� �������� �� ��������: ";
    cin >> num;
    if (is_prime(num)) {
        cout << num << " �������� �������" << endl;
    } else {
        cout << num << " ���������" << endl;
    }
}
