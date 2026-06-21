/*
 * 01-array / p2_reverse_shuffle.cpp
 * ------------------------------------------------------------
 * [문제] 배열 구간 조작 + count_odd
 *   - 배열은 0,1,2,...,N-1로 초기화된 상태에서 시작.
 *   - 명령: reverse i j / shuffle i j / print / count_odd
 *   - reverse: [i,j] 구간을 양끝에서 swap하며 뒤집기.
 *   - shuffle: element[i], element[j]를 1씩 증가시킨 뒤 두 값을 교환.
 *   - count_odd: 홀수 원소 개수 출력.
 * [핵심] 투 포인터로 구간 뒤집기 O(구간 길이).
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
		void count_odd() {
			int count = 0;
			for (int i = 0; i < N; i++) {
				if (element[i] % 2 != 0) {
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
			else if (input == "count_odd") {
				a.count_odd();
			}
		}
	}
}