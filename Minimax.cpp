#include <bits/stdc++.h>
using namespace std;

// Константы для обозначения бесконечности
const int INF = numeric_limits<int>::max(); // Положительная бесконечность
const int NEG_INF = numeric_limits<int>::min(); // Отрицательная бесконечность

/*
Алгоритм Минимакс используется в играх с двумя игроками (например, шахматы, крестики-нолики)
для поиска оптимального хода.

Цель алгоритма:
- Найти наилучшее возможное действие для максимизирующего игрока,
  при этом предполагая, что оппонент (минимизирующий игрок) также будет делать стратегические ходы.
- В процессе работы строится игровое дерево — это дерево возможных состояний игры.
  * Листовые узлы представляют возможные конечные состояния игры и их оценку.
  * Внутренние узлы представляют выборы игроков, где они чередуются (максимизатор и минимизатор).
  * Корень дерева — текущее состояние игры, алгоритм рекурсивно оценивает возможные ходы.
- *Альфа-бета отсечение ускоряет процесс поиска, отсекая ветви, которые гарантированно не повлияют на результат.
*/

// Функция минимакса с альфа-бета отсечением
// gameTree - массив с оценками листовых узлов
// depth - оставшаяся глубина рекурсии
// nodeIndex - индекс текущего узла в массиве gameTree
// isMaximizing - булево значение, указывающее, максимизирующий или минимизирующий игрок делает ход
// alpha - наибольшее найденное значение для максимизирующего игрока (нижняя граница)
// beta - наименьшее найденное значение для минимизирующего игрока (верхняя граница)
int minimax(vector<int>& gameTree, int depth, int nodeIndex, bool isMaximizing, int alpha, int beta) {
    // Если достигнут листовой узел, возвращаем его значение
    if (depth == 0 || nodeIndex >= gameTree.size()) {
        return gameTree[nodeIndex];
    }

    if (isMaximizing) { // Ход максимизирующего игрока (ищет максимальное значение)
        int maxEval = NEG_INF; // Начинаем с минимально возможного значения
        for (int i = 0; i < 2; ++i) { // Проходим по двум дочерним узлам
            int eval = minimax(gameTree, depth - 1, nodeIndex * 2 + i, false, alpha, beta);
            maxEval = max(maxEval, eval); // Обновляем лучшее найденное значение
            alpha = max(alpha, eval); // Обновляем нижнюю границу альфа-бета отсечения
            if (beta <= alpha) { // Если beta <= alpha, дальнейший поиск не имеет смысла
                break; // Обрезаем лишние ветви (альфа-бета отсечение)
            }
        }
        return maxEval; // Возвращаем найденное наилучшее значение
    } else { // Ход минимизирующего игрока (ищет минимальное значение)
        int minEval = INF; // Начинаем с максимально возможного значения
        for (int i = 0; i < 2; ++i) { // Проходим по двум дочерним узлам
            int eval = minimax(gameTree, depth - 1, nodeIndex * 2 + i, true, alpha, beta);
            minEval = min(minEval, eval); // Обновляем лучшее найденное значение
            beta = min(beta, eval); // Обновляем верхнюю границу альфа-бета отсечения
            if (beta <= alpha) { // Если beta <= alpha, дальнейший поиск не имеет смысла
                break; // Обрезаем лишние ветви (альфа-бета отсечение)
            }
        }
        return minEval; // Возвращаем найденное наилучшее значение
    }
}

int main() {
    int d; // Глубина игрового дерева
    cout << "Введите глубину дерева: ";
    cin >> d;

    int num_L = 1 << d; // Количество листовых узлов (2^d)
    vector<int> gameTree(num_L); // Вектор для хранения оценок листовых узлов

    cout << "Введите значения листовых узлов: ";
    for (int i = 0; i < num_L; ++i) {
        cin >> gameTree[i]; // Заполняем массив значениями листовых узлов
    }

    // Запускаем алгоритм минимакс с альфа-бета отсечением, начиная с корневого узла (индекс 0)
    // Глубина изначально полная, ход за максимизирующего игрока
    int res = minimax(gameTree, d, 0, true, NEG_INF, INF);

    cout << "Оптимальное значение: " << res << endl; // Выводим оптимальное значение для максимизатора
}
