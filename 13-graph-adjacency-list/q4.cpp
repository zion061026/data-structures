/*
 * 13-graph-adjacency-list / q4.cpp
 * ------------------------------------------------------------
 * [문제] 지하철 노선망 BFS (q3의 변형: farthest의 의미가 다름)
 *   - 명령은 q3와 동일하나, farthest s는 "가장 먼 거리"가 아니라
 *     그 최대 거리에 있는 역들 중 가장 작은 역 번호를 출력.
 * [핵심] BFS로 dist를 구한 뒤, 최대 거리 max를 찾고 dist==max인 정점 중 최소 vid 선택.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

class Graph {
private:
    vector<int> vids;
    vector<vector<pair<int, int>>> adj;  // adj[i] = {(상대 vid, eid), ...}
    vector<int> eids;
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

    vector<int> bfs(int s_idx) {
        vector<int> dist(vids.size(), -1);  // -1 = 미방문
        queue<int> q;
        dist[s_idx] = 0;
        q.push(s_idx);
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (auto& p : adj[cur]) {
                int next = vidx(p.first);  
                if (dist[next] == -1) {     
                    dist[next] = dist[cur] + 1;
                    q.push(next);
                }
            }
        }
        return dist;
    }
public:
    void openStation(int s) {
        if (vidx(s) >= 0) { cout << -1 << '\n'; return; }
        vids.push_back(s);
        adj.push_back({});
    }

    void connect(int u, int v, int r) {
        int i = vidx(u), j = vidx(v);
        if (i < 0 || j < 0 || eidx(r) >= 0) return;
        for (auto& p : adj[i])
            if (p.first == v) return;
        adj[i].push_back({ v, r });
        adj[j].push_back({ u, r });
        eids.push_back(r);
        edge_pair.push_back({ u, v });
    }

    void removeSection(int r) {
        int ei = eidx(r);
        if (ei < 0) { cout << -1 << '\n'; return; }
        int u = edge_pair[ei].first, v = edge_pair[ei].second;
        int i = vidx(u), j = vidx(v);
        for (int k = 0; k < adj[i].size(); k++)
            if (adj[i][k].second == r) { adj[i].erase(adj[i].begin() + k); break; }
        for (int k = 0; k < adj[j].size(); k++)
            if (adj[j][k].second == r) { adj[j].erase(adj[j].begin() + k); break; }
        eids.erase(eids.begin() + ei);
        edge_pair.erase(edge_pair.begin() + ei);
    }

    void closeStation(int s) {
        int vi = vidx(s);
        if (vi < 0) { cout << -1 << '\n'; return; }
        vector<int> to_erase;
        for (auto& p : adj[vi]) to_erase.push_back(p.second);
        for (int r : to_erase) removeSection(r);
        vi = vidx(s);
        adj.erase(adj.begin() + vi);
        vids.erase(vids.begin() + vi);
    }

    void distance(int u, int v) {
        int i = vidx(u), j = vidx(v);
        if (i < 0 || j < 0) { cout << -1 << '\n'; return; }
        if (u == v) { cout << 0 << '\n'; return; }
        vector<int> dist = bfs(i);
        cout << dist[j] << '\n';  // 도달 못하면 -1
    }

    void farthest(int s) {
        int si = vidx(s);
        if (si < 0) { cout << -1 << '\n'; return; }
        vector<int> dist = bfs(si);

        int mx = -1;
        for (int i = 0; i < dist.size(); i++) {
            if (i == si) continue;
            if (dist[i] > mx) mx = dist[i];
        }
        if (mx == -1) { cout << -1 << '\n'; return; }  
        
        int ans = 1e9;
        for (int i = 0; i < dist.size(); i++) {
            if (i == si) continue;
            if (dist[i] == mx && vids[i] < ans) ans = vids[i];
        }
        cout << ans << '\n';
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
        if (cmd == "open_station") {
            int s; cin >> s; g.openStation(s);
        }
        else if (cmd == "connect") {
            int u, v, r; cin >> u >> v >> r; g.connect(u, v, r);
        }
        else if (cmd == "close_station") {
            int s; cin >> s; g.closeStation(s);
        }
        else if (cmd == "remove_section") {
            int r; cin >> r; g.removeSection(r);
        }
        else if (cmd == "distance") {
            int u, v; cin >> u >> v; g.distance(u, v);
        }
        else if (cmd == "farthest") {
            int s; cin >> s; g.farthest(s);
        }
    }
    cout << flush;
}