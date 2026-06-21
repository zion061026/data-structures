/*
 * 12-graph-adjacency-matrix / q3.cpp
 * ------------------------------------------------------------
 * [문제] 인접 행렬로 만드는 친구 관계(SNS) — 공통 친구
 *   - 정점=사용자, 간선=친구 관계.
 *   - 명령: signup id / make_friend id1 id2 eid / leave id / break_friend eid /
 *           popularity id(친구 수=차수) / mutual_friends u v(공통 친구 id 오름차순)
 *   - 없는 사용자 등 오류 상황은 "error"/-1 출력.
 * [핵심] popularity는 한 행의 0 아닌 칸 수. mutual_friends는 두 정점의
 *        이웃 목록을 교집합.
 */
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Graph {
private:
	vector<int> vids;
	vector<int> eids;
	vector<pair<int, int>> edge_pair;
	vector<vector<int>> matrix;

	int vidx(int vid) {
		for (int i = 0; i < vids.size(); i++) {
			if (vids[i] == vid) return i;
		}
		return -1;
	}
	int eidx(int eid) {
		for (int i = 0; i < eids.size(); i++) {
			if (eids[i] == eid) return i;
		}
		return -1;
	}
public:
	bool insertVertex(int vid) {
		int vi = vidx(vid);
		if (vi >= 0) return false;
		vids.push_back(vid);
		for (auto& row : matrix) row.push_back(0);
		matrix.emplace_back(matrix.size() + 1, 0);
		return true;
	}
	bool insertEdge(int vid1, int vid2, int eid) {
		int ei = eidx(eid);
		int i = vidx(vid1), j = vidx(vid2);
		if (i < 0 || j < 0 || ei >= 0 || matrix[i][j]) {
			cout << "error" << '\n'; return false;
		}
		matrix[i][j] = matrix[j][i] = eid;
		edge_pair.push_back({ vid1,vid2 });
		eids.push_back(eid);
		return true;
	}
	bool eraseVertex(int vid) {
		int vi = vidx(vid);
		if (vi < 0)return false;
		for (int i = 0; i < matrix.size(); i++) {
			if (matrix[vi][i]) eraseEdge(matrix[vi][i]);
		}
		for (auto& row : matrix) row.erase(row.begin() + vi);
		matrix.erase(matrix.begin() + vi);
		vids.erase(vids.begin() + vi);
		return true;
	}
	bool eraseEdge(int eid) {
		int ei = eidx(eid);
		if (ei < 0)return false;
		int i = vidx(edge_pair[ei].first), j = vidx(edge_pair[ei].second);
		matrix[i][j] = matrix[j][i] = 0;
		edge_pair.erase(edge_pair.begin() + ei);
		eids.erase(eids.begin() + ei);
		return true;
	}
	void popularity(int vid) {
		int vi = vidx(vid);
		int cnt = 0;
		if (vi < 0) { cout << "error" << '\n'; return; }
		for (int j = 0; j < matrix.size(); j++) {
			if (vi == j) continue;
			if (matrix[vi][j]) cnt++;
		}
		cout << cnt << '\n';
	}
	void mutual_friends(int u, int v) {
		int vi1 = vidx(u), vi2 = vidx(v);
		if (vi1 < 0 || vi2 < 0) {
			cout << -1 << '\n'; return;
		}
		vector<int> u_incident;
		vector<int> v_incident;
		for (int i = 0; i < matrix.size(); i++) {
			if (matrix[vi1][i]) u_incident.push_back(i);
		}
		for (int i = 0; i < matrix.size(); i++) {
			if (matrix[vi2][i]) v_incident.push_back(i);
		}
		vector<int> res;
		bool seen[1001] = { false };
		for (int u : u_incident) {
			for (int v : v_incident) {
				if (u == v) {
					if (seen[u] == false) {
						res.push_back(vids[u]);
						seen[u] = true;
					}
				}
			}
		}
		if (res.empty()) {
			cout << -1 << '\n'; return;
		}
		std::sort(res.begin(), res.end());
		for (int x : res) {
			cout << x << " ";
		}
		cout << '\n';
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int Q; cin >> Q;
	Graph g;
	string input;
	for (int i = 0; i < Q; i++) {
		cin >> input;
		if (input == "signup") {
			int id; cin >> id;
			g.insertVertex(id);
		}
		else if (input == "make_friend") {
			int id1, id2, eid; cin >> id1 >> id2 >> eid;
			g.insertEdge(id1, id2, eid);
		}
		else if (input == "leave") {
			int id; cin >> id;
			g.eraseVertex(id);
		}
		else if (input == "break_friend") {
			int eid; cin >> eid;
			g.eraseEdge(eid);
		}
		else if (input == "popularity") {
			int id; cin >> id;
			g.popularity(id);
		}
		else if (input == "mutual_friends") {
			int u, v; cin >> u >> v;
			g.mutual_friends(u, v);
		}
	}
	cout << flush;
}