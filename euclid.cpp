#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) { // ���� b �� ����� ����
        int t = b; // ��������� �������� b �� ��������� ����������
        b = a % b; // ����������� b ������� �� ������� a �� b
        a = t; // ����������� a ������ �������� b
    }
    return a; // ����� b ���������� 0, a �������� ���
}

int main() {
    int num1, num2;
    cin >> num1 >> num2;
    // ���������� � ����� ����������� ������ ��������
    cout << "���(" << num1 << ", " << num2 << ") = " << gcd(num1, num2) << endl;
}
