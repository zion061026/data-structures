/*
 * 12-graph-adjacency-matrix / q2.cpp
 * ------------------------------------------------------------
 * [문제] 인접 행렬 그래프 — 인접 정점 질의 (q1의 변형)
 *   - 명령: insert_vertex / insert_edge / is_adjacent / erase_vertex /
 *           erase_edge / adjacent_vertices v
 *   - adjacent_vertices: v와 인접한 정점 id들을 오름차순 출력(없으면 -1).
 * [핵심] q1과 동일 구조, 출력 대상이 "간선 id" → "이웃 정점 id"로 바뀜.
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
		if (i < 0 || j < 0 || ei >= 0 || matrix[i][j]) return false;
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
	bool adjacent(int vid1, int vid2) {
		int i = vidx(vid1), j = vidx(vid2);
		return i >= 0 && j >= 0 && matrix[i][j] != 0;
	}
	void incident(int vid) {
		int vi = vidx(vid);
		vector<int> res;
		if (vi < 0) { cout << -1 << '\n'; return; }
		for (int i = 0; i < matrix.size(); i++) {
			if (matrix[vi][i]) res.push_back(vids[i]);
		}
		if (res.empty()) { cout << -1 << '\n'; return; }
		std::sort(res.begin(), res.end());
		for (int j = 0; j < res.size(); j++) {
			cout << res[j] << " ";
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
		if (input == "insert_vertex") {
			int vid; cin >> vid;
			g.insertVertex(vid);
		}
		else if (input == "insert_edge") {
			int vid1, vid2, eid; cin >> vid1 >> vid2 >> eid;
			g.insertEdge(vid1, vid2, eid);
		}
		else if (input == "is_adjacent") {
			int vid1, vid2; cin >> vid1 >> vid2;
			if (g.adjacent(vid1, vid2)) {
				cout << "True" << '\n';
			}
			else cout << "False" << '\n';
		}
		else if (input == "erase_vertex") {
			int vid; cin >> vid;
			g.eraseVertex(vid);
		}
		else if (input == "erase_edge") {
			int eid; cin >> eid;
			g.eraseEdge(eid);
		}
		else if (input == "adjacent_vertices") {
			int vid; cin >> vid;
			g.incident(vid);
		}
	}
	cout << flush;
}