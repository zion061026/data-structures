/*
 * 08-priority-queue / q1.cpp
 * ------------------------------------------------------------
 * [문제] 정렬되지 않은 리스트 기반 우선순위 큐
 *   - 명령: Push v / Top(최댓값) / Pop(최댓값 제거) /
 *           Print_Bottom k(가장 작은 k개) / Print_Med(중앙값) /
 *           Sum_Under(중앙값보다 작은 값들의 합)
 *   - 빈 큐 연산은 "empty"(Sum_Under는 0) 출력.
 * [핵심] 원소는 정렬 없이 list에 보관 → Top/Pop은 매번 선형 탐색 O(n).
 *        통계 명령은 버블 정렬한 임시 vector로 계산.
 */
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

class PQ {
public:
    PQ() = default;

    int size() { return elements.size(); }
    bool empty() { return size() == 0; }

    void push(int v) {
        elements.push_back(v);
    }

    int top() {
        int best = elements.front();
        for (int x : elements)
            if (x > best) best = x;
        return best;
    }

    void pop() {
        auto best = elements.begin();
        for (auto it = elements.begin(); it != elements.end(); ++it)
            if (*it > *best) best = it;
        elements.erase(best);
    }

    void bubbleSort(vector<int>& v) {
        int n = v.size();
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (v[j] > v[j + 1]) {
                    int tmp = v[j]; v[j] = v[j + 1]; v[j + 1] = tmp;
                }
    }

    void printBottom(int k) {
        vector<int> sorted(elements.begin(), elements.end());
        bubbleSort(sorted);
        for (int i = 0; i < k && i < (int)sorted.size(); i++) {
            if (i) cout << ' ';
            cout << sorted[i];
        }
        cout << "\n";
    }

    void printMed() {
        vector<int> sorted(elements.begin(), elements.end());
        bubbleSort(sorted);
        int sz = sorted.size();
        if (sz % 2 == 1)
            cout << sorted[sz / 2] << "\n";
        else
            cout << (sorted[sz / 2 - 1] + sorted[sz / 2]) / 2 << "\n";
    }

    void sumUnder() {
        vector<int> sorted(elements.begin(), elements.end());
        bubbleSort(sorted);
        int sz = sorted.size();
        double med = (sz % 2 == 1)
            ? sorted[sz / 2]
            : (sorted[sz / 2 - 1] + sorted[sz / 2]) / 2.0;
        long long sum = 0;
        for (int x : elements)
            if (x < med) sum += x;
        cout << sum << "\n";
    }

private:
    list<int> elements;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    PQ pq;

    while (n--) {
        string cmd;
        cin >> cmd;

        if (cmd == "Push") {
            int v; cin >> v;
            pq.push(v);
        }
        else if (cmd == "Top") {
            if (pq.empty()) cout << "empty\n";
            else cout << pq.top() << "\n";
        }
        else if (cmd == "Pop") {
            if (pq.empty()) cout << "empty\n";
            else pq.pop();
        }
        else if (cmd == "Print_Bottom") {
            int k; cin >> k;
            if (pq.empty()) cout << "empty\n";
            else pq.printBottom(k);
        }
        else if (cmd == "Print_Med") {
            if (pq.empty()) cout << "empty\n";
            else pq.printMed();
        }
        else if (cmd == "Sum_Under") {
            if (pq.empty()) cout << 0 << "\n";
            else pq.sumUnder();
        }
    }

    cout << flush;
    return 0;
}