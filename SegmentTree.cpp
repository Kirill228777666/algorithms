#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<int> tree; // Âåêòîð äëÿ õðàíåíèÿ äåðåâà îòðåçêîâ
    int size; // Ðàçìåð èñõîäíîãî ìàññèâà

    // Ôóíêöèÿ äëÿ ïîñòðîåíèÿ äåðåâà îòðåçêîâ
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) { // Åñëè ýòî ëèñòîâîé óçåë
            tree[node] = arr[start]; // Çàïèñûâàåì ýëåìåíò ìàññèâà
        } else {
            int mid = (start + end) / 2; // Íàõîäèì ñåðåäèíó äèàïàçîíà
            build(arr, 2 * node + 1, start, mid); // Ðåêóðñèâíî ñòðîèì ëåâîå ïîääåðåâî
            build(arr, 2 * node + 2, mid + 1, end); // Ðåêóðñèâíî ñòðîèì ïðàâîå ïîääåðåâî
            tree[node] = gcd(tree[2 * node + 1], tree[2 * node + 2]); // Îáúåäèíÿåì ðåçóëüòàòû (ÍÎÄ)
        }
    }

    // Ôóíêöèÿ äëÿ âûïîëíåíèÿ çàïðîñà ÍÎÄ íà îòðåçêå [l, r]
    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) { // Ïîëíîñòüþ âíå çàïðîñà
            return 0; // Íåéòðàëüíûé ýëåìåíò äëÿ ÍÎÄ (òàê êàê gcd(a, 0) = a)
        }
        if (l <= start && end <= r) { // Ïîëíîñòüþ âíóòðè çàïðîñà
            return tree[node]; // Âîçâðàùàåì ñîõðàíåííûé ÍÎÄ
        }
        int mid = (start + end) / 2; // Íàõîäèì ñåðåäèíó äèàïàçîíà
        int left_gcd = query(2 * node + 1, start, mid, l, r); // Çàïðîñ â ëåâîì ïîääåðåâå
        int right_gcd = query(2 * node + 2, mid + 1, end, l, r); // Çàïðîñ â ïðàâîì ïîääåðåâå
        return gcd(left_gcd, right_gcd); // Îáúåäèíÿåì ðåçóëüòàòû
    }

    // Ôóíêöèÿ äëÿ îáíîâëåíèÿ ýëåìåíòà â äåðåâå îòðåçêîâ
    void update(int node, int start, int end, int index, int value) {
        if (start == end) { // Åñëè äîøëè äî íóæíîãî ýëåìåíòà
            tree[node] = value; // Îáíîâëÿåì çíà÷åíèå
        } else {
            int mid = (start + end) / 2; // Íàõîäèì ñåðåäèíó äèàïàçîíà
            if (index <= mid) { // Åñëè èíäåêñ â ëåâîé ïîëîâèíå
                update(2 * node + 1, start, mid, index, value);
            } else { // Åñëè èíäåêñ â ïðàâîé ïîëîâèíå
                update(2 * node + 2, mid + 1, end, index, value);
            }
            tree[node] = gcd(tree[2 * node + 1], tree[2 * node + 2]); // Îáíîâëÿåì çíà÷åíèå â óçëå
        }
    }

    // Ôóíêöèÿ äëÿ âû÷èñëåíèÿ ÍÎÄ äâóõ ÷èñåë
    int gcd(int a, int b) {
        while (b != 0) { // Ïîêà âòîðîé îïåðàíä íå íîëü
            int temp = b;
            b = a % b; // Îñòàòîê îò äåëåíèÿ
            a = temp; // Îáíîâëÿåì a
        }
        return a; // Âîçâðàùàåì ÍÎÄ
    }

public:
    // Êîíñòðóêòîð: ïðèíèìàåò ìàññèâ è ñòðîèò äåðåâî îòðåçêîâ
    SegmentTree(const vector<int>& arr) {
        size = arr.size();
        tree.resize(4 * size); // Ðàçìåð äåðåâà 4 * n (áåçîïàñíàÿ îöåíêà)
        build(arr, 0, 0, size - 1);
    }

    // Ìåòîä äëÿ âûïîëíåíèÿ çàïðîñà ÍÎÄ íà îòðåçêå [l, r]
    int query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

    // Ìåòîä äëÿ îáíîâëåíèÿ ýëåìåíòà ìàññèâà
    void update(int index, int value) {
        update(0, 0, size - 1, index, value);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cout << "Ââåäèòå ðàçìåð ìàññèâà: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Ââåäèòå ýëåìåíòû ìàññèâà: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegmentTree segTree(arr);

    int q;
    cout << "Ââåäèòå êîëè÷åñòâî çàïðîñîâ: ";
    cin >> q;
    while (q--) {
        int type;
        cout << "Ââåäèòå òèï çàïðîñà (1 - çàïðîñ ÍÎÄ, 2 - îáíîâëåíèå): ";
        cin >> type;
        if (type == 1) {
            int l, r;
            cout << "Ââåäèòå ëåâóþ è ïðàâóþ ãðàíèöû îòðåçêà: ";
            cin >> l >> r;
            cout << "ÍÎÄ íà îòðåçêå (" << l << ", " << r << ") = " << segTree.query(l, r) << endl;
        } else if (type == 2) {
            int index, value;
            cout << "Ââåäèòå èíäåêñ è íîâîå çíà÷åíèå: ";
            cin >> index >> value;
            segTree.update(index, value);
            cout << "Ýëåìåíò îáíîâëåí.\n";
        }
    }
}
