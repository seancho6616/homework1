#pragma once
#define MAX 16
#define	NUM 4


typedef struct st {		// �л����� ����ü
	char name[MAX];	// �̸�
	int age;					// ����
	char nation[NUM];	// ����
	char depart[NUM];	// ����
	struct st* next;		
}ST;

ST* stInfor;			// �������� ���� ���� ����

char sc;
char word[MAX];
int num;

char serverIp[100];
int  portNum;

WSADATA wsaData;
SOCKET sock;
SOCKADDR_IN serverAddr;
HANDLE sendThread, recvThread;