# AGENTS.md

이 파일은 **Dual Mouse Lab(DML)** 저장소에서 작업하는 모든 AI 도구의 공통·표준 지침입니다.
Claude Code, ChatGPT, Codex 등 어떤 도구를 사용하더라도 먼저 이 문서를 읽고 따릅니다.

도구별 진입점인 `CLAUDE.md`, `CHATGPT.md`에는 해당 도구에만 필요한 차이만 적습니다.
공통 정책을 여러 파일에 복사하지 않습니다. 공통 규칙을 바꿀 때는 이 파일을 source of truth로 수정합니다.

현재 진행률, 다음 이슈 번호, 특정 실험의 성공 여부처럼 빨리 낡는 값은 이 파일에 고정하지 않습니다.
그런 정보는 `ROADMAP.md`, 열린 GitHub issue, 최근 PR, 실제 코드와 문서에서 다시 확인합니다.

## 프로젝트

- 프로젝트 이름: **Dual Mouse Lab**
- 프로젝트 아이디어 표기: **프로젝트 아이디어 No.98 - dual-mouse-lab (마우스 두 개·커서 두 개 연구·실험 저장소)**
- 핵심 모델:

  ```text
  Left hand  -> Physical Mouse A -> Cursor A
  Right hand -> Physical Mouse B -> Cursor B
  ```

- 핵심 목표는 하나의 완성형 상용 게임을 만드는 것이 아닙니다.
- 저장소의 중심은 다음 세 축입니다.
  1. dual-mouse / dual-cursor / multi-pointer / bimanual interaction 관련 자료 아카이브
  2. 재현 가능한 최소 reference implementation
  3. 입력 방식을 검증하는 작은 interaction/game demo
- 초기 구현 우선순위는 **OS 전체에 네이티브 커서 두 개를 만드는 것보다 애플리케이션 내부의 독립 virtual cursor 두 개**입니다.
- 공개 문서와 코드 문서는 영어를 기본으로 작성합니다.
- 한국어 안내가 필요한 경우 `README_KO.md` 또는 별도 `_KO` 문서를 사용합니다.
- maintainer용 AI workflow 문서는 한국어로 작성할 수 있습니다.

## Source of truth

작업 시작 전 최소한 다음을 실제로 확인합니다.

```text
AGENTS.md
README.md
README_KO.md
ROADMAP.md
관련 issue 본문 + 모든 댓글
최근 관련 PR / 현재 열린 PR
관련 docs / research 문서
관련 prototype / demo 코드
```

- 현재 DML에는 고정된 `version.py`가 없습니다. 존재하지 않는 버전 파일을 가정하지 않습니다.
- 버전·릴리스 체계가 생기기 전까지 특정 버전을 추측하거나 만들어내지 않습니다.
- 이전 대화, ZIP 요약, PR 본문의 "했다"는 설명보다 저장소의 실제 파일과 diff를 우선합니다.
- 닫힌 이슈는 사용자가 명시적으로 요구하거나 현재 작업의 역사적 맥락에 꼭 필요한 경우에만 근거로 사용합니다.

## AI 역할 분담

DML에서는 가능한 한 **구현과 독립 검증을 분리**합니다.

### Codex·Claude Code 등 코딩 에이전트

- 역할은 구현, 리팩터링, 테스트 코드 작성, 문서 갱신, Draft PR 생성까지입니다.
- 구현 전에 관련 issue, 댓글, 현재 코드와 문서를 읽고 변경 파일 계획을 확정합니다.
- 자신이 만든 변경의 결과를 독립 검증한 것처럼 표현하지 않습니다.
- 테스트 코드를 작성하거나 기존 테스트를 읽어 계약을 이해하는 것은 가능합니다.
- 사용자가 같은 작업에서 명시적으로 실행을 지시하지 않았다면, 자신이 만든 변경에 대한 build/runtime/hardware validation을 최종 증거로 제시하지 않습니다.
- 완료 보고에는 변경 파일, 구현 내용, 가정, 남은 위험, 필요한 검증 명령과 실기기 QA 항목을 남깁니다.
- `테스트 통과`, `실기기 검증 완료`, `머지 가능`, `릴리스 준비 완료`처럼 독립 검증이 필요한 결론을 임의로 내리지 않습니다.
- Draft PR까지만 만들고 자동 merge, tag, GitHub Release를 하지 않습니다.

### ChatGPT

- 역할은 계획, issue 분해, 연구자료 검증, PR/diff 독립 검토, 테스트 범위 결정, 결과 해석, 머지 판단입니다.
- 코딩 에이전트의 완료 보고를 검증 증거로 간주하지 않고 실제 파일, diff, CI, 빌드/실행 결과를 확인합니다.
- Windows 또는 실물 하드웨어에 접근할 수 없으면 해당 검증을 `실행하지 못함` 또는 `HARDWARE PENDING`으로 분리합니다.
- 사용자가 명시적으로 요청한 workflow 문서, 연구 아카이브, issue/PR 관리, 독립 검증 도구 작성은 직접 수행할 수 있습니다.
- 제품 코드 구현은 기본 역할이 아니며, 사용자가 같은 작업에서 명시적으로 요청한 경우에만 직접 수행합니다.

사용자가 같은 작업에서 명확하게 다른 역할 분담을 지시하면 그 지시를 우선합니다.

## 개발 환경

현재 기준 주요 개발 대상은 **Windows**입니다.

### Windows / C++ reference prototype

- 언어: C++17 이상
- 빌드: CMake
- 첫 플랫폼 API: Win32 Raw Input
- 이후 비교 경로: SDL3 등

권장 기본 명령 예시:

```powershell
cmake -S prototypes/00-device-inspector -B build/device-inspector
cmake --build build/device-inspector --config Release

cmake -S prototypes/01-dual-cursor-win32 -B build/dual-cursor
cmake --build build/dual-cursor --config Release
```

- 실제 경로와 generator는 사용자의 Visual Studio/CMake 환경을 확인한 뒤 조정합니다.
- Windows에서 실행하지 않은 코드를 `Windows에서 동작 확인됨`이라고 표현하지 않습니다.
- Linux/macOS 지원을 구현하지 않은 상태에서 cross-platform이라고 과장하지 않습니다.
- Raw Input, SDL, HID, driver, hook, injection 같은 용어를 서로 같은 것으로 취급하지 않습니다.

## DML에서 반드시 구분할 개념

다음 개념을 문서와 코드에서 섞어 쓰지 않습니다.

```text
physical mouse device
raw/device-specific input stream
native OS system cursor
application-local virtual cursor
reticle / game object
multi-user multi-mouse
single-user bimanual dual-mouse
```

특히:

- `마우스 두 개를 구분한다`와 `Windows 네이티브 시스템 커서가 두 개다`는 다른 주장입니다.
- 애플리케이션 내부에 virtual cursor 두 개를 그리는 것은 OS 전체 multi-cursor 구현과 다릅니다.
- 마우스 두 개가 있다고 해서 반드시 커서 두 개를 쓰는 게임은 아닙니다.
- 커서 두 개가 있다고 해서 반드시 물리 마우스 두 개를 사용하는 것은 아닙니다.

README와 연구 문서에서는 이 구분을 유지합니다.

## 사용자 요구 해석

- 사용자가 `예를 들어`라고 제시한 것은 예시이며, 동일 원인의 인접 문제까지 확인합니다.
- 다만 범위를 무제한으로 확장하지 않습니다. 같은 원인·같은 패턴까지를 기본 경계로 봅니다.
- 저장소 근거로 안전하게 결정할 수 있고 되돌릴 수 있는 작업은 불필요한 질문 없이 진행합니다.
- 다음 경우에는 구현 전에 사용자 확인을 받습니다.
  - 비밀값 또는 개인 데이터가 실제로 필요함
  - destructive action 또는 비가역 변경
  - 서로 배타적인 제품 방향 중 하나를 선택해야 함
  - 저장소 근거만으로 결과 차이가 큰 결정을 할 수 없음
- `다음 작업`, `계속`, `ㄱㄱ`는 현재 roadmap과 열린 issue에서 준비된 다음 논리적 작업을 계속하라는 뜻으로 해석합니다.
- PR 댓글의 `ㅇㅇ`는 기본적으로 **곧 머지하겠다**는 뜻으로 취급하며, 새 구현 작업을 시작하라는 신호로 해석하지 않습니다.

## 구현 계획 품질

구현 전에 가능한 범위에서 다음을 구체화합니다.

```text
정확한 파일
함수 / class / module
현재 문제
수정할 control flow
입력 데이터와 상태
오류 / disconnect / hot-plug 분기
테스트 계약
실물 마우스 QA 항목
문서 영향
```

자연어 요구를 반복하는 것만으로는 구현 계획이 아닙니다.

## 코드 변경 원칙

- 기존 구조와 네이밍을 우선 따릅니다.
- 불필요한 리팩터링과 범위 밖 변경을 피합니다.
- prototype은 최소 재현 가능성과 이해하기 쉬운 구조를 우선합니다.
- 실험 코드라도 장치 식별, cursor state, interaction logic을 가능한 한 분리합니다.
- 특정 하드웨어 이름이나 device handle을 코드에 영구 하드코딩하지 않습니다.
- 동일 정책을 여러 파일에 복사하지 않습니다.
- 외부 라이브러리나 엔진을 추가할 때는 왜 필요한지, 기존 Win32/SDL 경로와 어떤 관계인지 문서화합니다.

## 연구·백과사전 자료 규칙

`research/`는 DML의 핵심 산출물입니다.

- 가능한 한 **1차 출처(primary source)**를 우선합니다.
  - 공식 문서
  - 원 논문 / DOI / 학회 페이지
  - 개발자 공식 페이지
  - 공식 Steam/itch.io 페이지
  - 원 GitHub repository
  - Google Patents / 특허청 원문
- 블로그, Reddit, 영상 댓글 등 2차 출처는 발견 경로나 보조 맥락으로 사용할 수 있지만 핵심 사실은 1차 출처로 재확인합니다.
- 확인하지 못한 내용은 `unverified`, `needs verification`, `unclear` 등으로 명시합니다.
- `세계 최초`, `최초의 게임`, `유일한 구현` 같은 강한 신규성 주장은 충분한 선행조사 없이 사용하지 않습니다.
- 게임/도구/논문을 추가할 때 가능한 한 다음을 구분합니다.

  ```text
  physical mice: 1 / 2 / N / unclear
  independent cursors: yes / no / unclear
  users: 1 / 2 / N
  platform
  input model
  source URL
  verification status
  relevance to DML
  ```

- 저작권 있는 원문을 장문 복제하지 않습니다. 짧게 요약하고 원문 링크를 남깁니다.
- 링크가 죽었거나 날짜/저자가 불명확하면 사실처럼 단정하지 않습니다.

## 테스트와 검증 표현

검증 수준을 실제 수행 범위대로 구분합니다.

```text
source review
static analysis
CMake configure
compile/build
unit test
application runtime
single-mouse runtime
real two-mouse hardware
mixed-DPI two-mouse hardware
Bluetooth / touchpad / virtual-device behavior
hot-plug / reconnect
Windows version compatibility
```

- 소스 리뷰만 했으면 build 성공이라고 말하지 않습니다.
- build 성공을 실제 마우스 두 개 runtime 성공이라고 말하지 않습니다.
- mock/synthetic input 결과를 실제 Raw Input 장치 분리 성공으로 표현하지 않습니다.
- 실기기에서 `hDevice` 또는 장치 ID가 실제로 분리되는지 확인하기 전에는 해당 gate를 완료 처리하지 않습니다.
- 실행하지 못한 항목은 `실행하지 않음` 또는 `실행하지 못함`으로 명시합니다.

## 실물 하드웨어 QA 기본 항목

DML의 핵심 기능은 실물 장치 검증이 필요합니다.

최소 QA 후보:

```text
USB mouse A + USB mouse B
Mouse A moves only Cursor A
Mouse B moves only Cursor B
left/right/middle buttons per device
wheel per device
unplug/replug
focus lost / regained
window resize
mixed DPI / sensitivity
Bluetooth mouse if available
touchpad / virtual mouse interference
```

실물 장치가 필요한 항목은 repo-side 완료와 별도로 `HARDWARE PENDING`으로 남길 수 있습니다.

## 보안·개인정보·로컬 장치 정보

- 토큰, 비밀번호, 개인 설정, 계정 정보 등 비밀값을 커밋하지 않습니다.
- Raw Input device path, VID/PID, serial-like identifier, 사용자 PC 경로가 로그에 포함될 수 있으므로 공개 issue/README에 그대로 올리기 전에 민감도를 확인합니다.
- 실제 장치 로그를 예시로 문서화할 때는 개인 환경을 식별할 수 있는 값은 마스킹합니다.
- 입력 캡처 prototype을 키로거처럼 확장하거나 사용자의 요청 범위를 넘어 시스템 전체 입력을 수집하지 않습니다.

## GitHub write 안전 규칙

- **기본값은 branch + PR입니다. `main`에 직접 write하지 않습니다.**
- 사용자가 명시적으로 `main` 직접 수정을 요청한 경우를 제외하고 모든 파일 변경은 feature branch에서 합니다.
- 기존 파일 수정은 먼저 해당 파일을 읽고 최신 내용을 기준으로 작업합니다.
- write 후 변경 파일과 diff를 다시 확인합니다.
- accidental commit/file이 생기면 숨기지 않고 즉시 보고합니다.
- 이미 공유된 history를 없애기 위한 force push/reset은 사용자의 명시적 승인 없이는 하지 않습니다.
- issue 작업은 issue/comment 도구를 사용하고 placeholder 파일로 대신하지 않습니다.

## Git 원자성

DML은 KGA에서 사용하던 file-level atomicity를 유지합니다.

- **모든 PR에서 `changed files <= commits`를 만족해야 합니다.**
- 한 커밋은 정확히 파일 하나만 변경합니다.
- 같은 파일을 여러 커밋으로 나누는 것은 허용합니다.
- 추가, 수정, 삭제, rename을 모두 변경 파일로 계산합니다.
- `AGENTS.md`, `CLAUDE.md`, `CHATGPT.md`도 각각 별도 커밋으로 처리합니다.
- PR 생성 전에 변경 파일 수와 커밋 수를 확인합니다.
- 커밋 수를 억지로 줄이기 위해 이미 정상적인 history를 reset/rebase하지 않습니다.

## Issue와 PR

- 구현 또는 문서 작업은 가능한 한 관련 issue를 먼저 만들거나 기존 issue를 연결합니다.
- PR은 하나의 논리적 카테고리/목표 단위로 구성합니다.
- PR 본문에는 다음을 포함합니다.

  ```text
  관련 issue
  목적
  변경 파일
  구현/문서 변경 내용
  범위 밖 항목
  남은 위험
  검증 체크리스트
  실물 하드웨어 pending 여부
  ```

- 코딩 에이전트는 Draft PR까지만 만들고 독립 검토 전 merge하지 않습니다.
- ChatGPT가 직접 workflow/research 문서를 수정하는 경우에도 branch/PR을 기본으로 합니다.
- 자동 merge를 켜지 않습니다.
- 주기적 자동 재검증 task를 만들지 않습니다. 사용자가 요청할 때만 다시 확인합니다.

## 상태 표현

다음 상태를 섞어 쓰지 않습니다.

```text
ANALYZED          분석 완료
HANDOFF READY     구현 지시가 파일/함수/검증 수준까지 확정됨
PR OPEN           실제 PR 존재
VERIFIED          실행 가능한 독립 검증 완료
HARDWARE PENDING  repo-side는 진행됐지만 실물 마우스 gate가 남음
MERGE READY       diff + 검증 + 위험 검토 후 머지 승인 가능
DONE              해당 issue의 완료 조건 전체 충족
```

`HANDOFF READY`를 실제 구현 완료처럼 표현하지 않습니다.
`PR OPEN`을 `VERIFIED`와 같은 뜻으로 쓰지 않습니다.

## PR 독립 검증 기본 순서

1. PR 본문과 연결 issue의 본문/댓글 확인
2. changed filenames와 commit 수 확인
3. 각 commit이 한 파일만 변경하는지 확인
4. 전체 diff와 각 변경 파일 읽기
5. 요구 누락 / scope creep / 용어 혼동 확인
6. research 변경이면 primary source와 claims 확인
7. code 변경이면 가능한 build/static/unit gate 수행
8. 실물 장치가 필요한 항목을 별도 분리
9. CI가 있으면 local/independent 결과와 대조
10. `MERGE READY`, 재작업, 또는 `HARDWARE PENDING` 판정

CI green만으로 자동으로 merge-ready라고 판단하지 않습니다.

## 릴리스와 버전

현재 DML은 연구/초기 prototype 단계입니다.

- 사용자가 릴리스 작업을 명시하지 않은 이상 버전 파일을 새로 만들거나 버전을 올리지 않습니다.
- Git tag를 만들지 않습니다.
- GitHub Release를 발행하지 않습니다.
- 자동 merge하지 않습니다.
- 이후 버전 체계를 도입하면 Semantic Versioning을 기본 후보로 사용하되 실제 API/CLI/파일 형식의 호환성에 맞춰 판단합니다.
- 실제 Windows/실물 마우스 검증이 끝나지 않은 빌드를 `stable` 또는 `production ready`라고 부르지 않습니다.

## 완료 보고 기본 형식

필요에 따라 다음을 명확히 구분합니다.

```text
이번에 한 것:
검증한 것:
검증하지 못한 것:
열린 PR:
머지할 것:
머지 보류:
다음 작업:
사용자가 지금 할 것:
```

보고에서 추측과 사실을 섞지 않습니다.
