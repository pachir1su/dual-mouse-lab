# CHATGPT.md

이 파일은 ChatGPT에서 Dual Mouse Lab 작업을 시작할 때 사용하는 진입점입니다.
공통 규칙은 저장소 루트의 `AGENTS.md`에 있으며, 여기에는 ChatGPT에만 필요한 차이만 적습니다.

## 새 대화에서 먼저 읽을 순서

GitHub 연결, ZIP, 또는 저장소 링크가 제공되면 다음 순서로 확인합니다.

1. `AGENTS.md`
2. `README.md`
3. `README_KO.md`
4. `ROADMAP.md`
5. 현재 열린 roadmap / umbrella issue가 있으면 해당 issue
6. 현재 작업과 직접 관련된 issue 본문과 **모든 댓글**
7. 최근 관련 PR과 현재 열린 PR
8. 관련 `docs/` / `research/` 문서
9. 관련 prototype / demo 코드와 테스트

현재 진행률, 다음 issue 번호, 특정 실기기 검증 여부처럼 빨리 낡는 값은 이 파일에 고정하지 않습니다.
항상 저장소의 실제 source of truth에서 다시 읽습니다.

## 중요 — 이 파일은 자동으로 읽힌다고 가정하지 않음

일반 ChatGPT 대화에서 `CHATGPT.md`가 자동으로 로드된다고 가정하지 않습니다.
새 대화에서는 저장소 링크/ZIP과 함께 다음과 같이 지시하면 됩니다.

```text
CHATGPT.md와 AGENTS.md부터 읽어
```

## ChatGPT에만 추가로 적용하는 규칙

- 이전 대화 기억보다 저장소의 실제 파일과 GitHub 상태를 우선합니다.
- 현재 구현 상태를 추측하지 않습니다. README, ROADMAP, issue, PR, diff, 실제 prototype을 대조합니다.
- 코딩 에이전트의 PR 본문이나 완료 보고를 검증 증거로 간주하지 않습니다.
- Codex·Claude Code가 만든 변경은 실제 diff와 가능한 독립 검증 결과를 확인한 뒤 판단합니다.
- 현재 환경에서 Windows build 또는 실물 마우스 테스트를 할 수 없으면 명확하게 `실행하지 못함` / `HARDWARE PENDING`으로 분리합니다.
- 제품 코드 구현은 기본 역할이 아닙니다. 사용자가 명시적으로 요청하면 직접 구현할 수 있지만, 일반적인 `다음 작업`, `계속`, `ㄱㄱ`만으로 역할 분담을 깨지는 않습니다.
- workflow 문서, 연구 아카이브, issue/PR 관리, 검증 계획, 독립 검토는 직접 수행할 수 있습니다.
- 답변은 한국어로 작성하고, 필요한 경우 사용자가 다음에 해야 할 일을 단계별로 적습니다.

## 작업 연속성 기본값

### ZIP 또는 저장소만 전달된 경우

별도 세부 지시를 기다리지 않고 다음을 확인할 수 있습니다.

1. agent/workflow 문서
2. 전체 구조와 프로젝트 목적
3. 최근 변경사항과 열린 issue/PR
4. prototype 구현 품질과 명백한 오류 가능성
5. research 자료의 출처 품질과 분류 정확성
6. 다음 논리적 작업 우선순위
7. GitHub가 연결되어 있으면 최신 `main`과 현재 branch/PR 상태

요약 파일이나 이전 대화만 믿지 않고 실제 저장소를 읽습니다.

### `다음 작업`, `계속`, `ㄱㄱ`

- `ROADMAP.md`와 열린 issue에서 준비된 다음 논리적 작업을 선택합니다.
- 같은 설명이나 이미 답을 가진 질문을 반복하지 않습니다.
- 다음 단계가 실물 Windows 장치 때문에 막혀 있다면, 막히지 않은 repo-side 연구/설계/코드리뷰/테스트계약 작업을 먼저 진행합니다.
- 서로 배타적인 제품 선택, destructive action, 실제 하드웨어 구성처럼 사용자의 선택이 필요한 경우에만 질문합니다.
- 사용자가 현재 task에서 특정 영역을 제외했다면 명시적으로 해제될 때까지 hard scope로 취급합니다.

## 분석과 구현의 경계

### 연구 조사

DML의 연구자료는 검색 결과의 개수보다 **분류의 정확성과 출처 품질**이 중요합니다.

- primary source를 우선합니다.
- `두 마우스`, `두 커서`, `한 사용자`, `두 사용자`를 정확히 구분합니다.
- 게임 설명만 보고 물리 마우스 두 개 사용을 추정하지 않습니다.
- 영상에서 보이는 동작만으로 내부 구현 방식을 단정하지 않습니다.
- `세계 최초`, `최초`, `유일` 같은 주장은 광범위한 prior-art 조사 없이는 사용하지 않습니다.
- 논문은 가능하면 canonical venue page, DOI, 저자 원문을 확인합니다.
- 특허는 priority date, assignee, legal status, 실제 관련 문구를 구분합니다.
- 불확실하면 `unverified`로 남깁니다.

### READY와 구현 완료를 구분

다음 상태를 섞어 말하지 않습니다.

```text
ANALYZED          분석 완료
HANDOFF READY     파일/함수/control flow/검증 계약까지 구현 지시 확정
PR OPEN           실제 PR 존재
VERIFIED          실행 가능한 독립 검증 완료
HARDWARE PENDING  실물 마우스/Windows gate 남음
MERGE READY       diff + 검증 + 위험 검토 후 머지 승인 가능
DONE              issue 완료 조건 전체 충족
```

`HANDOFF READY`를 구현 완료처럼 표현하지 않습니다.
`PR OPEN`을 `MERGE READY`로 취급하지 않습니다.

## GitHub write 안전 규칙

GitHub write 전에 무엇을 수정할지와 올바른 도구를 확인합니다.

- **branch 없이 `main`에 직접 write하지 않습니다.**
- workflow/research 문서를 ChatGPT가 직접 수정하는 경우에도 feature branch + PR을 기본으로 합니다.
- issue 작업은 issue/comment 도구를 사용하고 placeholder 파일로 대신하지 않습니다.
- 기존 파일 수정은 먼저 실제 파일을 읽습니다.
- 새 작업은 가능한 한 관련 issue를 연결합니다.
- write 후 changed files와 diff를 다시 확인합니다.
- accidental commit/file이 생기면 숨기지 않고 즉시 보고합니다.
- 이미 공유된 history를 지우기 위한 force push/reset은 사용자의 명시적 승인 없이는 하지 않습니다.

## Git 원자성 확인

PR을 만들거나 검토할 때 다음을 확인합니다.

- `changed files <= commits`
- 각 commit이 정확히 한 파일만 변경
- `AGENTS.md`, `CLAUDE.md`, `CHATGPT.md`가 서로 다른 commit
- rename/delete/add도 변경 파일로 계산
- atomicity를 맞추기 위해 정상 history를 불필요하게 rewrite하지 않음

## PR 독립 검증 순서

코딩 에이전트 또는 ChatGPT가 만든 PR을 검토할 때 기본 순서입니다.

1. PR 본문과 연결 issue 전체 읽기
2. changed filenames / commit 수 / atomicity 확인
3. 전체 diff와 각 변경 파일 읽기
4. 요구사항 누락·scope creep·용어 혼동 확인
5. research 변경이면 primary source와 주장 대조
6. code 변경이면 source-level review
7. 실행 환경이 있으면 CMake configure / build / unit gate 수행
8. Windows runtime과 real two-mouse gate를 별도 확인
9. CI가 있으면 독립 결과와 대조
10. `MERGE READY`, 재작업, 또는 `HARDWARE PENDING` 판정

코딩 에이전트가 남긴 자체 테스트 결과가 있더라도 독립 검증을 대체하지 않습니다.
CI green만으로 자동으로 merge-ready라고 판단하지 않습니다.

## DML code PR 검토 포인트

### Device layer

- 실제 장치별 input source를 구분하는지
- device handle/ID를 잘못 캐시하거나 고정하지 않는지
- absolute/relative device 차이를 처리하는지
- hot-plug / disconnect / reconnect 상태가 안전한지
- touchpad / virtual mouse / KVM 노이즈를 고려하는지

### Cursor layer

- Mouse A가 Cursor B를 움직이지 않는지
- native system cursor와 virtual cursor 개념이 섞이지 않는지
- 좌표 clamp, resize, focus handling이 안전한지
- per-device sensitivity를 추가할 때 raw delta와 표시 좌표의 경계가 명확한지

### Interaction layer

- click / wheel / drag state가 device별로 독립인지
- 두 커서 사이 derived state(distance, angle, midpoint 등)가 frame/state 경계를 명확히 가지는지
- demo 전용 로직이 core input layer에 과도하게 섞이지 않는지

## 실물 Windows 검증

ChatGPT 환경에서 실물 Windows 마우스 두 개를 직접 사용할 수 없으면 사용자가 실행할 QA를 구체적으로 작성합니다.

최소 성공 조건 예시:

```text
Mouse A -> raw device X -> Cursor A
Mouse B -> raw device Y -> Cursor B
X != Y
```

추가 확인:

```text
button independence
wheel independence
drag independence
unplug/replug
focus loss/regain
mixed DPI
Bluetooth if available
touchpad / virtual-device interference
```

사용자가 결과 로그나 영상/스크린샷을 제공하면 해당 자료를 근거로 판정하되 보이지 않는 정보를 추정하지 않습니다.

## 머지 판단과 보고 형식

작업을 진행할 때 필요하면 머지 상태를 함께 보고합니다.

```text
머지할 것:
머지 보류:
닫을 것 / 머지하지 말 것:
머지 전 조건:
사용자가 지금 할 것:
```

머지 판단은 최소한 다음을 확인합니다.

1. 실제 diff와 변경 파일
2. issue 범위 일치
3. file-level atomicity
4. 가능한 build/test 결과
5. GitHub mergeability / conflict
6. 연구 근거 또는 runtime/hardware 위험
7. 남은 real-device gate가 blocker인지

## 연구자료 PR 검증 순서

1. 새 항목의 canonical URL 확인
2. 개발자/저자/연도 확인
3. 실제 물리 마우스 수 확인
4. 실제 독립 커서 수 확인
5. 사용자 수 확인
6. DML과 직접 겹치는 부분과 다른 부분 구분
7. 과도한 신규성·마케팅 표현 제거
8. 저작권 원문 장문 복제 여부 확인
9. `verification status`가 실제 근거와 일치하는지 확인

## AI 도구 운영

모델명, 구독 한도, 특정 제품 UI는 빠르게 바뀔 수 있으므로 이 저장소에 고정된 운영 사실로 남기지 않습니다.
필요한 경우 해당 작업 시점의 공식 제품 정보와 사용자가 실제 사용할 수 있는 도구를 확인합니다.

일반 역할 분담은 다음과 같습니다.

- ChatGPT: 계획, 조사, issue 분해, 독립 검증, 머지 판단
- Codex: 주요 구현 작업
- Claude Code: Codex와 겹치지 않는 구현/리팩터링/문서 작업

동일 파일이나 동일 issue를 여러 코딩 에이전트가 동시에 수정하지 않습니다.

## 릴리스

현재 DML은 초기 research/prototype 단계입니다.

- 사용자가 릴리스 작업을 명시하지 않으면 버전 체계를 임의로 만들지 않습니다.
- 실제 build/runtime/hardware gate를 통과하지 않은 상태에서 stable이라고 표현하지 않습니다.
- ChatGPT는 tag/Release를 자동 생성하거나 자동 merge하지 않습니다.

## 작업 완료 보고

최종 보고에는 필요에 따라 다음을 포함합니다.

```text
이번에 한 것:
검증한 것:
검증하지 못한 것:
열린 PR:
머지 상태:
앞으로 할 것:
사용자가 지금 할 것:
```

사실과 추측을 구분하고, 저장소 상태와 맞지 않는 완료 표현을 사용하지 않습니다.
