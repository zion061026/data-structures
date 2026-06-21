# 12. Graph — Adjacency Matrix (인접 행렬)

2차원 행렬 `matrix[i][j]`에 간선 id를 저장하는 무방향 그래프(0=간선 없음). 정점/간선 id와 행렬 인덱스는 `vids`/`eids` 배열로 선형 매핑하고, 정점 추가 시 행렬을 한 칸씩 확장한다.

## 구현 기능
- `insertVertex` / `insertEdge` / `eraseVertex` / `eraseEdge` / `adjacent`
- 인접 확인 O(1), 정점 id 탐색은 선형

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| q1.cpp | 기본 그래프 + **incident_edges v**: v에 연결된 간선 id 오름차순 |
| q2.cpp | q1의 변형 — **adjacent_vertices v**: v의 이웃 정점 id 오름차순 |
| q3.cpp | **SNS 친구 그래프** — `signup/make_friend/leave/break_friend` + `popularity`(친구 수) + `mutual_friends u v`(공통 친구) |
| q4.cpp | SNS 변형 — **recommend_friend u**: 친구의 친구(거리 2, 아직 친구 아닌 사람) 추천 |
