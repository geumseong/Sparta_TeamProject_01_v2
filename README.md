# Sparta_TeamProject_01_v2
- **프로젝트 소개**
    - 프로젝트 이름
        - Shadow of Dragon RPG
    - 프로젝트 개요
        - 텍스트 기반의 RPG 게임
        - 주요 컨텐츠 & 기능:
            - 직업 시스템
            - 전투 시스템 (스킬 구현)
            - 인벤토리 시스템
            - 아이템 관리 시스템
            - 상점 시스템
            - 제작 시스템 (재료 소진 시스템 구현)
            - 보스 전투 시스템
            - 레벨 시스템
    - 개발 관련 노트:
        - 기본적인 c++ 사용
        - nlohmann-json vcpkg 사용
        - 자체 제작 item DB의 json 파일 제작 후 사용
        - 한글 출력을 위해 windows.h 사용 및 UTF-8 엔코딩으로 저장

- **개발 환경**
    - 개발 언어 및 도구
        - IDE: Visual Studio 2022
        - Compiler: C++ 11 이상
        - niohmann-json vcpkh 사용
        - 자체 제작 itemDB.json 파일 사용

- **프로젝트 구조**
    main.cpp = 메인 함수 진입점
    GameManager.cpp(.h) = GameManager 싱글톤 구현
    Shop.cpp(.h) = 상점 시스템 구현
    Workshop.cpp(.h) = 제작소 시스템 구현
    Character.cpp(.h) = 플레이어 캐릭터 구현
      //character에서 상속받는 코드
      - Warrior.cpp(.h) = 전사 직업 구현
      - Archer.cpp(.h) = 궁수 직업 구현
      - Magician.cpp(.h) = 마법사 직업 구현
      - Thief.cpp(.h) = 도적 직업 구현
    Monster.cpp(.h) = 몬스터 구현
      - Goblin.cpp(.h) = 고블린 몬스터 구현
      - Orc.cpp(.h) = 오크 몬스터 구현
      - Dragon.cpp(.h) = 드래곤 보스 몬스터 구현
      //각종 주석처리 된 미구현 몬스터들 (주석처리 해제 시 사용 가능)
        - Imp.cpp(.h) = 임프 몬스터 구현
        - Kobold.cpp(.h) = 코볼트 몬스터 구현
        - Ogre.cpp(.h) = 오거 몬스터 구현
        - Slime.cpp(.h) = 슬라임 몬스터 구현
        - Succubus.cpp(.h) = 서큐버스 몬스터 구현
        - Troll.cpp(.h) = 트롤 몬스터 구현
    Inventory.cpp(.h) = 인벤토리 구현
    Item.cpp(.h) = 아이템 구현
    itemDB.h = itemDB.json 파일과 대조하여 아이템 타입을 분류하는 헤더
    ItemEffect.cpp(.h) = 아이템 효과 구현, 효과 값을 아이템에 연동
    UIManager.cpp(.h) = Ascii Art Graphics 출력 기능 구현
    AsciiArt.h = Ascii Art 크기/프레임 설정 헤더

- **핵심 로직/클래스 설명**
    - Main() -
        - GameManager State를 받아, State 상태에 따른 실행 코드 변화
    - GameManager 싱글톤 객체를 사용해 전반적인 게임 흐릅을 관리.
        - StateMachine을 사용해 게임 흐름을 제어함. (Start, Shopping, Crafting, Battle) (Resting은 주석 처리 됐지만 사용 가능)
          - (예: 전투 끝날 시 Shopping으로 State를 변환하여 상정 진입)
          - (예: 특정 라운드가 지나면 전투 끝날 시 상점이 아닌 제작소로 진입)
    - 플레이어의 Character가 인벤토리를 지니고 다니는게 아닌, 인벤토리 매니저를 생성해서 인벤토리를 관리 함.
        - 인벤토리 매니저는 상점과 제작소와 아이템 값을 주고 받을 때 중심이 되어줌. (캐릭터의 Gold도 보유함)
        - Monster 추상 클래스로 부터 다양한 몬스터들을 생성
          - Type 변수로 랜덤으로 다양한 객체의 같은 종류의 몬스터를 생성함 (예: 난폭한 고블린, 겁쟁이 고블린, etc.)
        - Character 추상 클래스를 기반으로, 직업을 지닌 캐릭터를 생성함 (바로 Warrior나 Magician 등 직업을 지닌 상태로 캐릭터를 생성)

- **과제 추가 구현 사항 (추가 구현을 했다면 필히 작성!)**
    - UI 인터페이스 구현
    - 제작소 (제작 재료 아이템 기반으로 작동함) 구현
        - 아이템 제작 시 인벤토리에서 제작 재료 아이템 소진
    - 장비 착용/해제 시스템

- **주의사항**
    - 만들어졌지만 주석처리 된 수 많은 몬스터들이 존재함. (주석 해제 후 조금의 편집을 통해 사용 가능)
    - UI interface 에서 텍스트 출력이 살짝 어긋나거나 살짝 미흡할 수 있음.
    - 아이템의 착용/사용과 장비 해제 시 스탯 업데이트가 간혹 적용되지 않을 수 도 있음.
    - 기능들을 짧은 시간 내에 시현 할 수 있게끔 제작 해, 게임 플레이 타임이 매우 짧을 수 있음.
