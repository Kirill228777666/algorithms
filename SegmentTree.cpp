#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<int> tree; // Вектор для хранения дерева отрезков
    int size; // Размер исходного массива

    // Функция для построения дерева отрезков
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) { // Если это листовой узел
            tree[node] = arr[start]; // Записываем элемент массива
        } else {
            int mid = (start + end) / 2; // Находим середину диапазона
            build(arr, 2 * node + 1, start, mid); // Рекурсивно строим левое поддерево
            build(arr, 2 * node + 2, mid + 1, end); // Рекурсивно строим правое поддерево
            tree[node] = gcd(tree[2 * node + 1], tree[2 * node + 2]); // Объединяем результаты (НОД)
        }
    }

    // Функция для выполнения запроса НОД на отрезке [l, r]
    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) { // Полностью вне запроса
            return 0; // Нейтральный элемент для НОД (так как gcd(a, 0) = a)
        }
        if (l <= start && end <= r) { // Полностью внутри запроса
            return tree[node]; // Возвращаем сохраненный НОД
        }
        int mid = (start + end) / 2; // Находим середину диапазона
        int left_gcd = query(2 * node + 1, start, mid, l, r); // Запрос в левом поддереве
        int right_gcd = query(2 * node + 2, mid + 1, end, l, r); // Запрос в правом поддереве
        return gcd(left_gcd, right_gcd); // Объединяем результаты
    }

    // Функция для обновления элемента в дереве отрезков
    void update(int node, int start, int end, int index, int value) {
        if (start == end) { // Если дошли до нужного элемента
            tree[node] = value; // Обновляем значение
        } else {
            int mid = (start + end) / 2; // Находим середину диапазона
            if (index <= mid) { // Если индекс в левой половине
                update(2 * node + 1, start, mid, index, value);
            } else { // Если индекс в правой половине
                update(2 * node + 2, mid + 1, end, index, value);
            }
            tree[node] = gcd(tree[2 * node + 1], tree[2 * node + 2]); // Обновляем значение в узле
        }
    }

    // Функция для вычисления НОД двух чисел
    int gcd(int a, int b) {
        while (b != 0) { // Пока второй операнд не ноль
            int temp = b;
            b = a % b; // Остаток от деления
            a = temp; // Обновляем a
        }
        return a; // Возвращаем НОД
    }

public:
    // Конструктор: принимает массив и строит дерево отрезков
    SegmentTree(const vector<int>& arr) {
        size = arr.size();
        tree.resize(4 * size); // Размер дерева 4 * n (безопасная оценка)
        build(arr, 0, 0, size - 1);
    }

    // Метод для выполнения запроса НОД на отрезке [l, r]
    int query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

    // Метод для обновления элемента массива
    void update(int index, int value) {
        update(0, 0, size - 1, index, value);
    }
};

int main() {
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Введите элементы массива: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegmentTree segTree(arr);

    int q;
    cout << "Введите количество запросов: ";
    cin >> q;
    while (q--) {
        int type;
        cout << "Введите тип запроса (1 - запрос НОД, 2 - обновление): ";
        cin >> type;
        if (type == 1) {
            int l, r;
            cout << "Введите левую и правую границы отрезка: ";
            cin >> l >> r;
            cout << "НОД на отрезке (" << l << ", " << r << ") = " << segTree.query(l, r) << endl;
        } else if (type == 2) {
            int index, value;
            cout << "Введите индекс и новое значение: ";
            cin >> index >> value;
            segTree.update(index, value);
            cout << "Элемент обновлен.\n";
        }
    }
}
