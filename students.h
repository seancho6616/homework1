#pragma once
#define MAX 16
#define	NUM 4
#define LINE 50


typedef struct st {		// �л����� ����ü
	char name[MAX];	// �̸�
	int age;					// ����
	char nation[NUM];	// ����
	char depart[NUM];	// ����
	struct st* next;		
}ST;

ST student;			// Ŭ���̾�Ʈ���� ����� ����ü
ST* stInfor;			// �������� ���� ���� ����

char c;					// �������� �з��ϱ� ���� ����ڵ�
char sc;					// �������� ���� ������ �з��ϱ� ���� ����ڵ�
char word[MAX];		// Ŭ���̾�Ʈ���� ������ ���� ����
int num;					// ��� ���� �� ����� ����

char serverIp[100];
int  portNum;

WSADATA wsaData;
SOCKET sock;
SOCKADDR_IN serverAddr;
HANDLE sendThread, recvThread;

void gotoxy(int x, int y);			// ��ġ �̵�

void ipInterface();					// ip �������̽�

void mainMenuInterface();		// ���θ޴� �������̽�

void searchingInterface();		// �˻�â �������̽�

void information();					// ���� �߰� ���� �������̽�

void addInformation();			// ���� �߰�

void delInformation();				// ���� ����

void findName();						// �̸� �˻�

void findNation();					// ���� �˻�
void findDepartment();			// ���� �˻�
void findAge();						// ���� �˻�

void textcolor(int colorNum);	// �ؽ�Ʈ �� ����

enum ColorType { RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14, WHITE = 15 }COLOR;
