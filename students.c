#define _WINSOCK_DEPRECATED_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 소켓관련 경고 무시용
#define _CRT_SECURE_NO_WARNINGS 
#pragma comment(lib, "ws2_32")  //비주얼스튜디오 환경에서 개발시 소켓 라이브러리 지정용

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <time.h>
#include "students.h"

#define MAX 16
#define	NUM 4
#define LINE 50

char c1 = 'h';

ST student;			// 클라이언트에서 사용할 구조체
ST* stInfor=NULL;			// 서버에서 받은 정보 저장

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

//enum ColorType { RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14, WHITE = 15 }COLOR;

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ipInterface() {
	system("cls");
	gotoxy(3, 2);	printf("IP : ");
	textcolor(YELLOW);
	gotoxy(3, 3);	printf("Enter IP of server");
	textcolor(WHITE);
	gotoxy(3, 5);	printf("Port : ");
	textcolor(YELLOW);
	gotoxy(3, 6);	printf("Enter Port of server");
	textcolor(WHITE);

	gotoxy(8, 2); gets(serverIp);
	gotoxy(10, 5); scanf("%d", &portNum);
}

void mainMenuInterface() {
	system("cls");
	gotoxy(2, 1); printf("Searching to Students Information \n\n");
	for (int i = 0; i <= LINE; i++) {
		textcolor(GREEN);
		printf("=");
	}
	textcolor(WHITE);
	gotoxy(2, 5);		printf("1. Search for a Name\n");
	gotoxy(2, 7);		printf("2. Search by Nation\n");
	gotoxy(2, 9);		printf("3. Search by Department\n");
	gotoxy(2, 11);	printf("4. Search by Age\n");
	gotoxy(2, 13);	printf("5. Add or Delet Information\n");
	gotoxy(2, 15);	printf("6. Close\n");
	searchingInterface();
	//c1 = 'h';
}

void searchingInterface() {
	fflush(stdin);
	gotoxy(3, 18);	printf(">  ");	scanf("%d", &num);
	if (num == 6) {
		system("cls");
		gotoxy(8, 3);
		textcolor(YELLOW);	printf("END\n\n\n");	textcolor(WHITE);
		exit(0);
	}
	getchar();
	switch (num) {
		case 1:
			gotoxy(3, 20);	printf("Enter a name >  "); gets(word); 
			findName();
			system("pause");
			break;
		case 2:
			gotoxy(3, 20);	printf("Enter a nation >  "); gets(word);
			findNation();
			system("pause");
			break;
		case 3:
			gotoxy(3, 20);	printf("Enter a depertment >  "); gets(word);
			findDepartment();
			system("pause");
			break;
		case 4:
			gotoxy(3, 20);	printf("Enter an age >  "); scanf("%d", &num);
			findAge();
			system("pause");
			break;
		case 5:
			information();
			system("pause");
			break;
		default:
			printf("Enter again");
			system("pause");
			break;
	}
}

void information() {
	system("cls");
	fflush(stdin);
	gotoxy(3, 2);	printf("1. Add information  ");
	gotoxy(3, 4);	printf("2. Delet information  ");
	printf("\n");
	gotoxy(5, 6); printf(">  ");	 scanf("%d", &num);
}

void findName() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search for a name +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	gotoxy(3, 3);	printf("Name"); 
	gotoxy(10, 3);	printf("Age");
	gotoxy(16, 3);	printf("Nation");
	gotoxy(26, 3);	printf("Department\n");
}

void findNation() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search by Nation +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	printf("\n");
}

void findDepartment() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search by Department +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	printf("\n");
}

void findAge() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search by Age +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	printf("\n");
}

void addInformation() {
	gotoxy(2, 1); printf("Name : ");
	gotoxy(2, 3); printf("Age : ");
	gotoxy(2, 5); printf("Nation : ");
	gotoxy(2, 7); printf("Department : ");
	//gotoxy()

}