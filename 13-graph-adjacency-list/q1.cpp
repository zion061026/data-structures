/*
 * 13-graph-adjacency-list / q1.cpp
 * ------------------------------------------------------------
 * [문제] 인접 리스트 그래프 (무방향)
 *   - 명령: insert_vertex v / insert_edge u v eid / erase_vertex v /
 *           erase_edge eid / find_edge u v / edges / vertices
 *   - find_edge: u-v를 잇는 간선 id(없으면 -1). edges/vertices: 전체 id 오름차순.
 * [핵심] adj[i] = {(이웃 vid, eid), ...} 형태의 인접 리스트.
 *        무방향이라 간선은 양쪽 리스트에 모두 추가/삭제.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Graph {
private:
    vector<int> vids;
    vector<vector<pair<int, int>>> adj;  
    vector<int> eids;                    // 존재하는 간선 ID 목록
    vector<pair<int, int>> edge_pair;     

    int vidx(int vid) {
        for (int i = 0; i < vids.size(); i++)
            if (vids[i] == vid) return i;
        return -1;
    }
    int eidx(int eid) {
        for (int i = 0; i < eids.size(); i++)
            if (eids[i] == eid) return i;
        return -1;
    }
public:
    void insertVertex(int vid) {
        if (vidx(vid) >= 0) { cout << -1 << '\n'; return; }
        vids.push_back(vid);
        adj.push_back({});
    }

    void insertEdge(int u, int v, int eid) {
        int i = vidx(u), j = vidx(v);
        if (i < 0 || j < 0 || eidx(eid) >= 0) return;
        for (auto& p : adj[i])           // 이미 연결되어 있으면 중단
            if (p.first == v) return;
        adj[i].push_back({ v, eid });
        adj[j].push_back({ u, eid });
        eids.push_back(eid);
        edge_pair.push_back({ u, v });
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

    void findEdge(int u, int v) {
        int i = vidx(u), j = vidx(v);
        if (i < 0 || j < 0) { cout << -1 << '\n'; return; }
        for (auto& p : adj[i])
            if (p.first == v) { cout << p.second << '\n'; return; }
        cout << -1 << '\n';
    }

    void edges() {
        if (eids.empty()) { cout << -1 << '\n'; return; }
        vector<int> res = eids;
        sort(res.begin(), res.end());
        for (int e : res) cout << e << " ";
        cout << '\n';
    }

    void vertices() {
        if (vids.empty()) { cout << -1 << '\n'; return; }
        vector<int> res = vids;
        sort(res.begin(), res.end());
        for (int v : res) cout << v << " ";
        cout << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int Q; cin >> Q;
    Graph g;
    string cmd;
    while (Q--) {
        cin >> cmd;
        if (cmd == "insert_vertex") {
            int v; cin >> v;
            g.insertVertex(v);
        }
        else if (cmd == "insert_edge") {
            int u, v, e; cin >> u >> v >> e;
            g.insertEdge(u, v, e);
        }
        else if (cmd == "erase_vertex") {
            int v; cin >> v;
            g.eraseVertex(v);
        }
        else if (cmd == "erase_edge") {
            int e; cin >> e;
            g.eraseEdge(e);
        }
        else if (cmd == "find_edge") {
            int u, v; cin >> u >> v;
            g.findEdge(u, v);
        }
        else if (cmd == "edges") {
            g.edges();
        }
        else if (cmd == "vertices") {
            g.vertices();
        }
    }
    cout << flush;
}