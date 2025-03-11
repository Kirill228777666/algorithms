#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<int> tree; // ������ ��� �������� ������ ��������
    int size; // ������ ��������� �������

    // ������� ��� ���������� ������ ��������
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) { // ���� ��� �������� ����
            tree[node] = arr[start]; // ���������� ������� �������
        } else {
            int mid = (start + end) / 2; // ������� �������� ���������
            build(arr, 2 * node + 1, start, mid); // ���������� ������ ����� ���������
            build(arr, 2 * node + 2, mid + 1, end); // ���������� ������ ������ ���������
            tree[node] = gcd(tree[2 * node + 1], tree[2 * node + 2]); // ���������� ���������� (���)
        }
    }

    // ������� ��� ���������� ������� ��� �� ������� [l, r]
    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) { // ��������� ��� �������
            return 0; // ����������� ������� ��� ��� (��� ��� gcd(a, 0) = a)
        }
        if (l <= start && end <= r) { // ��������� ������ �������
            return tree[node]; // ���������� ����������� ���
        }
        int mid = (start + end) / 2; // ������� �������� ���������
        int left_gcd = query(2 * node + 1, start, mid, l, r); // ������ � ����� ���������
        int right_gcd = query(2 * node + 2, mid + 1, end, l, r); // ������ � ������ ���������
        return gcd(left_gcd, right_gcd); // ���������� ����������
    }

    // ������� ��� ���������� �������� � ������ ��������
    void update(int node, int start, int end, int index, int value) {
        if (start == end) { // ���� ����� �� ������� ��������
            tree[node] = value; // ��������� ��������
        } else {
            int mid = (start + end) / 2; // ������� �������� ���������
            if (index <= mid) { // ���� ������ � ����� ��������
                update(2 * node + 1, start, mid, index, value);
            } else { // ���� ������ � ������ ��������
                update(2 * node + 2, mid + 1, end, index, value);
            }
            tree[node] = gcd(tree[2 * node + 1], tree[2 * node + 2]); // ��������� �������� � ����
        }
    }

    // ������� ��� ���������� ��� ���� �����
    int gcd(int a, int b) {
        while (b != 0) { // ���� ������ ������� �� ����
            int temp = b;
            b = a % b; // ������� �� �������
            a = temp; // ��������� a
        }
        return a; // ���������� ���
    }

public:
    // �����������: ��������� ������ � ������ ������ ��������
    SegmentTree(const vector<int>& arr) {
        size = arr.size();
        tree.resize(4 * size); // ������ ������ 4 * n (���������� ������)
        build(arr, 0, 0, size - 1);
    }

    // ����� ��� ���������� ������� ��� �� ������� [l, r]
    int query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

    // ����� ��� ���������� �������� �������
    void update(int index, int value) {
        update(0, 0, size - 1, index, value);
    }
};

int main() {
    int n;
    cout << "������� ������ �������: ";
    cin >> n;
    vector<int> arr(n);
    cout << "������� �������� �������: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegmentTree segTree(arr);

    int q;
    cout << "������� ���������� ��������: ";
    cin >> q;
    while (q--) {
        int type;
        cout << "������� ��� ������� (1 - ������ ���, 2 - ����������): ";
        cin >> type;
        if (type == 1) {
            int l, r;
            cout << "������� ����� � ������ ������� �������: ";
            cin >> l >> r;
            cout << "��� �� ������� (" << l << ", " << r << ") = " << segTree.query(l, r) << endl;
        } else if (type == 2) {
            int index, value;
            cout << "������� ������ � ����� ��������: ";
            cin >> index >> value;
            segTree.update(index, value);
            cout << "������� ��������.\n";
        }
    }
}
