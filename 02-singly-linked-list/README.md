# 02. Singly Linked List (단일 연결 리스트)

`head`/`tail` 포인터로 관리하는 단일 연결 리스트. 일부 문제는 **커서(cursor)** 노드를 두고 그 주변을 조작한다.

## 구현 기능
- `addFront` / `addBack` / `removeFront` — 앞·뒤 삽입, 앞 삭제
- `find` — 값으로 커서 노드 지정
- `insertPrev/Next`, `deletePrev/Next` — 커서 기준 앞·뒤 삽입/삭제

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| p1.cpp | 기본 리스트(`addFront/addBack/removeFront/print`) + **sum_even**: 짝수 노드 값의 합 |
| p2.cpp | 커서 기반 — `find`로 커서 지정 후 **insertPrev / deletePrev** (커서 앞에 삽입/삭제). prev 포인터가 없어 head부터 직전 노드 탐색 |
| p3.cpp | p1의 변형 — **sum_odd**: 홀수 노드 값의 합 |
| p4.cpp | 커서 기반 — **insertNext / deleteNext** (커서 뒤에 삽입/삭제). tail 경계 처리 |

## 주의 (예외 상황)
- 빈 리스트에서 `removeFront`/`print` → `-1` 출력
- 원소가 1개(`head == tail`)일 때 삭제 시 두 포인터 모두 `nullptr`로
- 커서가 `head`/`tail`일 때의 삽입·삭제 경계 처리
