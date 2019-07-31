## 프로젝트명
미니 크레이지 아케이드 (개인 프로젝트)
## 사용언어
C
## 개발기간
2014.08 ~ 2014.11
## 프로젝트 소개
C언어로 구현한 콘솔창에서 동작하는 '크레이지 아케이드'의 미니 버전 구현
![image1](images/image1.jpeg)
*****

## 실행화면
![image01](images/image01.png)  
게임이 시작하였습니다. 제 캐릭터(○)와 적 캐릭터(@)가 생성되었습니다.

![image02](images/image02.png)  
스페이스바를 누르면 사용자 캐릭터가 있던 자리에 물풍선(⊙)이 생깁니다.

![image03](images/image03.png)  
일정 시간이 지나면 물풍선이 터집니다. 이때 물줄기에 맞은 벽돌들은 사라집니다.

![image04](images/image04.png)  
사용자 캐릭터가 물줄기에 맞거나 적에게 닿으면 게임이 종료됩니다.

![screenshot](images/screenshot.gif)  
*****

```c
while (difftime(last, current) < WATER_BOMB_DELAY) {

  ...

}

water_attack(pos_a_x, pos_a_y);
```
과거 시간과 현재 시간의 틱을 계산하여 지정된 시간이 지나면 물풍선이 터짐.

```c
	show_character(remove_character(move_character(_getch())));
```
방향키의 입력에 따라 사용자 캐릭터를 이동시키고 화면에 보여줌

```c
do {
  i = rand() % MONSTERS;
} while ( mob[i].life == false );

j = rand() % 4;

switch (j) {
  case 0: ...
  case 1: ...
  case 2: ...
  case 3: ...
}
```
몬스터는 난수를 받아 랜덤한 방향으로 이동

```c
if (MAP[pos_y][pos_x] == WATER_ATTACK)
  life = false;
```
맵의 좌표는 2차원 배열을 이용해 구현하였으며, 물줄기가 뻗어나갈때  
해당 배열의 값은 특정값(WATER_ATTACK)이 되는데 사용자 캐릭터가 이곳에 있으면 게임이 종료됨

```c
void gotoxy(int x, int y) {

	COORD Pos = { x*2  , y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}
```
게임의 그래픽 효과를 위해 화면 전체를 지우고 새로 그리는 과정에서 화면이 깜빡이는 현상이 발생,  
콘솔에 지정한 위치에만 문자를 쓰고 지우기 위해 gotoxy()라는 함수를 사용
*****
## 개발후기
JAVA 등의 객체 지향 언어와 달리 객체라는 개념이 없어서 각 캐릭터들을 제어하는 것이 힘들어, 몬스터들을 구조체를 이용하여 관리함.  
캐릭터들의 움직임, 물줄기가 뻗어나가는 것을 구현하기 위해 화면이 역동적으로 변해야 할 필요가 있었는데, 윈도우에서 콘솔을 클리어하는 명령어인 "cls"를 통해 화면을 클리어한 후 새로 그리는 과정에서 화면이 깜빡이는 현상이 발생.  
지정한 위치에만 문자를 쓰고 지우는 방법을 모색하여 적용.  
예를들어 물폭탄을 화면의 가장자리에 설치한 경우 물줄기가 뻗어나가면서 배열의 범위를 벗어나는 오류가 발생,
물줄기가 뻗어나가는 방향이 배열의 범위 내인지 사전에 검사하는 방법으로 해결.  
