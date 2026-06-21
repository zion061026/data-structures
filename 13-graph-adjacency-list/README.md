# 13. Graph — Adjacency List & Traversal (인접 리스트)

인접 리스트(`adj[i] = {(이웃 vid, eid), ...}`)로 표현한 무방향 그래프. 가중치가 없으므로 **BFS로 최단 거리**를 구한다(`queue` 사용).

## 구현 기능
- 인접 리스트 기반 정점/간선 삽입·삭제 (간선은 양쪽 리스트에 반영)
- `find_edge` / `edges` / `vertices`
- `bfs`로 최단 거리·도달성 계산 (q3, q4)

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| q1.cpp | 기본 인접 리스트 — `insert/erase_vertex/edge` + `find_edge` + `edges` / `vertices` |
| q2.cpp | q1의 변형 — `find_edge` / `edges` 위주 |
| q3.cpp | **지하철 노선망** — `open_station/connect/close_station/remove_section` + `distance u v`(BFS 최단 거리) + `farthest s`(가장 먼 거리) |
| q4.cpp | q3의 변형 — `farthest s`가 최대 거리에 있는 역들 중 **가장 작은 역 번호**를 출력 |
