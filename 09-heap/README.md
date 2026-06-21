# 09. Heap (이진 힙)

`vector` 기반 완전 이진 힙. `elements[0]`은 비워두고 1번부터 사용해 부모 `i/2`, 자식 `2i`/`2i+1`로 계산. `compare` functor의 부등호만 바꾸면 min/max 힙이 전환된다.

## 구현 기능
- `push` → `upheap`(상향 재정렬) / `pop` → `downheap`(하향 재정렬) — O(log n)
- 값으로 임의 원소 `cancel`(삭제) · `update`(값 변경) 후 양방향 재정렬

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| q1.cpp | **최대 힙** — `push/pop/top/size/print` |
| q2.cpp | **최소 힙** — q1과 동일 명령, 비교 방향만 반대 |
| q3.cpp | **최대 힙 스케줄러** — `submit/execute/peek/count` + `cancel p`(값으로 삭제, 없으면 `not_found`) + `update p q`(값 변경). 빈 힙은 `idle` |
| q4.cpp | q3의 **최소 힙** 버전 |

> `cancel`/`update`는 힙 성질이 위·아래 어느 쪽으로 깨질지 모르므로 `upheap`과 `downheap`을 둘 다 호출해 복구한다.
