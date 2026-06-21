/*
 * 12-graph-adjacency-matrix / q1.cpp
 * ------------------------------------------------------------
 * [문제] 인접 행렬 그래프 (무방향) — 간선 질의
 *   - 명령: insert_vertex v / insert_edge v1 v2 eid / is_adjacent v1 v2 /
 *           erase_vertex v / erase_edge eid / incident_edges v
 *   - incident_edges: v에 연결된 간선 id들을 오름차순 출력(없으면 -1).
 * [핵심] matrix[i][j]에 간선 id를 저장(0=없음). 정점 추가 시 행렬을 한 칸씩 확장.
 *        정점/간선 id ↔ 행렬 인덱스는 vids/eids 배열로 선형 매핑.
 */
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
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
			if (vi >= 0) { return false; }
			for (auto& row : matrix) row.push_back(0);
			matrix.emplace_back(matrix.size() + 1, 0);
			vids.push_back(vid);
			return true;
		}
		bool insertEdge(int vid1, int vid2, int eid) {
			int ei = eidx(eid);
			int i = vidx(vid1), j = vidx(vid2);
			if (i < 0 || j < 0 || matrix[i][j] || ei >= 0) { return false; }
			eids.push_back(eid);
			edge_pair.push_back({ vid1,vid2 });
			matrix[i][j] = matrix[j][i] = eid;
			return true;
		}
		bool eraseEdge(int eid) {
			int ei = eidx(eid);
			if (ei < 0) { return false; }
			int i = vidx(edge_pair[ei].first), j = vidx(edge_pair[ei].second);
			matrix[i][j] = matrix[j][i] = 0;
			eids.erase(eids.begin() + ei);
			edge_pair.erase(edge_pair.begin() + ei);
			return true;
		}
		bool eraseVertex(int vid) {
			int vi = vidx(vid);
			if (vi < 0) return false;
			for (int i = 0; i < matrix.size(); i++) {
				if (matrix[vi][i]) eraseEdge(matrix[vi][i]);
			}
			for (auto& row : matrix) row.erase(row.begin() + vi);
			matrix.erase(matrix.begin() + vi);
			vids.erase(vids.begin() + vi);
			return true;
		}
		bool adjacent(int vid1, int vid2) {
			int i = vidx(vid1), j = vidx(vid2);
			return i >= 0 && j >= 0 && matrix[i][j];
		}
		void incident_edges(int vid) {
			vector<int> res;
			int vi = vidx(vid);
			if (vi < 0) { cout << -1 << '\n'; return; }
			for (int i = 0; i < matrix.size(); i++) {
				if (matrix[vi][i]) res.push_back(matrix[vi][i]);
			}
			if(res.empty()) { cout << -1 << '\n'; return; }
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
		else if (input == "incident_edges") {
			int vid; cin >> vid;
			g.incident_edges(vid);
		}
	}
	cout << flush;
}