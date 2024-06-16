#pragma once
#define MAX 16
#define	NUM 4
#define LINE 50


typedef struct st {		// 학생정보 구조체
	char name[MAX];	// 이름
	int age;					// 나이
	char nation[NUM];	// 나라
	char depart[NUM];	// 전공
	struct st* next;		
}ST;

ST student;			// 클라이언트에서 사용할 구조체
ST* stInfor;			// 서버에서 받은 정보 저장

char c;					// 서버에서 분류하기 위한 목록코드
char sc;					// 서버에서 받은 정보를 분류하기 위한 목록코드
char word[MAX];		// 클라이언트에서 정보를 받을 변수
int num;					// 목록 선택 시 사용할 변수

char serverIp[100];
int  portNum;

WSADATA wsaData;
SOCKET sock;
SOCKADDR_IN serverAddr;
HANDLE sendThread, recvThread;

void gotoxy(int x, int y);			// 위치 이동

void ipInterface();					// ip 인터페이스

void mainMenuInterface();		// 메인메뉴 인터페이스

void searchingInterface();		// 검색창 인터페이스

void information();					// 정보 추가 삭제 인터페이스

void addInformation();			// 정보 추가

void delInformation();				// 정보 삭제

void findName();						// 이름 검색

void findNation();					// 나라 검색
void findDepartment();			// 전공 검색
void findAge();						// 나이 검색

void textcolor(int colorNum);	// 텍스트 색 변경

enum ColorType { RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14, WHITE = 15 }COLOR;
