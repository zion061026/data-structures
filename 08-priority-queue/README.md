# 08. Priority Queue (우선순위 큐)

`list` 기반 우선순위 큐. `compare` functor로 정렬 기준을 주입한다. 정렬 안 한 리스트(선형 탐색)와 정렬 삽입 두 방식을 모두 다룬다.

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| q1.cpp | **정렬 X 리스트** PQ — `Push / Top(최댓값) / Pop / Print_Bottom k(작은 k개) / Print_Med(중앙값) / Sum_Under`. 통계는 버블 정렬로 계산 |
| q2.cpp | **정렬 삽입** PQ — `Push`(제자리 삽입) / `Pop`(최솟값) / `Top` / `Print_Top k` / `Print_Med` / `Sum_Over` |
| q3.cpp | **부호 기반 게임** — 양수: 같은 값이 있으면 제거+`v*2` 병합(2048식), 없으면 정렬 삽입 / 음수: `|v|`에 가장 가까운 값 제거 / 0: 전체 출력 |
| q4.cpp | q3의 변형 — 일반 삽입을 정렬하지 않고 `push_back` |
