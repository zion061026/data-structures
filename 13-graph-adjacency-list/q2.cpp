/*
 * 13-graph-adjacency-list / q2.cpp
 * ------------------------------------------------------------
 * [문제] 인접 리스트 그래프 (q1의 변형)
 *   - 명령: insert_vertex / insert_edge / erase_vertex / erase_edge /
 *           find_edge u v / edges
 * [핵심] q1과 동일한 인접 리스트 구조(여기선 edges/find_edge 위주).
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
		vector<vector<pair<int, int>>> adj;

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
		void insertVertex(int vid) {
			int vi = vidx(vid);
			if (vi >= 0) { cout << -1 << '\n'; return; }
			vids.push_back(vid);
			adj.push_back({});
		}
		void insertEdge(int vid1, int vid2, int eid) {
			int i = vidx(vid1), j = vidx(vid2);
			int ei = eidx(eid);
			if (i < 0 || j < 0 || ei >= 0) return;
			for (auto& p : adj[i]) {
				if (p.first == vid2) return;
			}
			adj[i].push_back({ vid2,eid });
			adj[j].push_back({ vid1,eid });
			eids.push_back(eid);
			edge_pair.push_back({ vid1,vid2 });
		}
		void eraseEdge(int eid) {
			int ei = eidx(eid);
			if (ei < 0) { cout << -1 << '\n'; return; }
			int u = edge_pair[ei].first, v = edge_pair[ei].second;
			int i = vidx(u), j = vidx(v);
			for (int k = 0; k < adj[i].size(); k++)      // adj[i]에서 이 간선 제거
				if (adj[i][k].second == eid) { adj[i].erase(adj[i].begin() + k); break; }
			for (int k = 0; k < adj[j].size(); k++)      // adj[j]에서도 제거
				if (adj[j][k].second == eid) { adj[j].erase(adj[j].begin() + k); break; }
			eids.erase(eids.begin() + ei);
			edge_pair.erase(edge_pair.begin() + ei);
		}

		void eraseVertex(int vid) {
			int vi = vidx(vid);
			if (vi < 0) { cout << -1 << '\n'; return; }
			vector<int> to_erase;                        // 인접 간선 eid 모으기
			for (auto& p : adj[vi]) to_erase.push_back(p.second);
			for (int eid : to_erase) eraseEdge(eid);     // 다 삭제
			adj.erase(adj.begin() + vi);
			vids.erase(vids.begin() + vi);
		}
		void find_edge(int u, int v) {
			int i = vidx(u), j = vidx(v);
			if (i < 0 || j < 0) { cout << -1 << '\n'; return; }
			for (auto& p : adj[i]) {
				if (p.first == v) {
					cout << p.second << '\n';
					return;
				}
			}
			cout << -1 << '\n';
		}
		void edges() {
			vector<int> res;
			for (int x : eids) {
				res.push_back(x);
			}
			if (res.empty()) { cout << -1 << '\n'; return; }
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
			int v; cin >> v;
			g.insertVertex(v);
		}
		else if (input == "insert_edge") {
			int u, v, e; cin >> u >> v >> e;
			g.insertEdge(u, v, e);
		}
		else if (input == "erase_vertex") {
			int v;cin >> v;
			g.eraseVertex(v);
		}
		else if (input == "erase_edge") {
			int e; cin >> e;
			g.eraseEdge(e);
		}
		else if (input == "find_edge") {
			int u, v; cin >> u >> v;
			g.find_edge(u, v);
		}
		else if (input == "edges") {
			g.edges();
		}
	}
}