/*
 * 01-array / p4.cpp
 * ------------------------------------------------------------
 * [문제] 배열 구간 조작 + count_even  (p2의 변형: 홀수 → 짝수)
 *   - 0,1,...,N-1로 초기화. 명령: reverse i j / shuffle i j / print / count_even
 *   - count_even: 짝수 원소 개수 출력.
 * [핵심] p2_reverse_shuffle과 동일, 세는 조건만 짝수로.
 */
#include <iostream>
#include <string>
using namespace std;

class Array {
	public:
		Array(int N) :N{ N } {
			element = new int[N];
			for (int i = 0; i < N; i++) {
				element[i] = i;
			}
		}
		~Array() {
			delete element;
		}
		void reverse(int i, int j) {
			while (i < j) {
				swap(element[i], element[j]);
				i++;
				j--;
			}
		}
		void shuffle(int i, int j) {
			element[i]++;
			element[j]++;
			swap(element[i], element[j]);
		}
		void count_even() {
			int count = 0;
			for (int i = 0; i < N; i++) {
				if (element[i] % 2 == 0) {
					count++;
				}
			}
			cout << count << '\n';
		}
		void print() {
			for (int i = 0; i < N; i++) {
				cout << element[i] << " ";
			}
			cout << '\n';
		}
	
	private:
		int N;
		int* element;
		void swap(int& x, int& y) {
			int temp = x;
			x = y;
			y = temp;
		}
};

int main() {
	string input;
	int T; cin >> T;
	while (T--) {
		int N, Q; cin >> N >> Q;
		Array a(N);
		for (int i = 0; i < Q; i++) {
			cin >> input;
			if (input == "reverse") {
				int i, j; cin >> i >> j;
				a.reverse(i, j);
			}
			else if (input == "shuffle") {
				int i, j; cin >> i >> j;
				a.shuffle(i, j);
			}
			else if (input == "print") {
				a.print();
			}
			else if (input == "count_even") {
				a.count_even();
			}
		}
	}
}