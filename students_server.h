#pragma once
#define MAX 16
#define	NUM 4


typedef struct st {		// 학생정보 구조체
	char name[MAX];	// 이름
	int age;					// 나이
	char nation[NUM];	// 나라
	char depart[NUM];	// 전공
	struct st* next;		
}ST;

ST* stInfor;			// 서버에서 받은 정보 저장

char sc;
char word[MAX];
int num;

char serverIp[100];
int  portNum;

WSADATA wsaData;
SOCKET sock;
SOCKADDR_IN serverAddr;
HANDLE sendThread, recvThread;

void gotoxy(int x, int y);		// 위치 이동


enum ColorType { RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14, WHITE = 15 }COLOR;
