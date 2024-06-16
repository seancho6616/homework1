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

// 텍스트 색 변경 함수
void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}


// 위치 이동 함수
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// IP와 Port번호 받기 위한 인터페이스 함수
void ipInterface() {
	// 콘솔 창 지우기
	system("cls");
	// 인터페이스
	gotoxy(3, 2);	printf("IP : \n");
	textcolor(YELLOW);		// 출력 텍스트 색 변경 ( 노랑 )
	gotoxy(3, 3);	printf("Enter IP of server\n");
	textcolor(WHITE);		// 출력 텍스트 색 변경 ( 흰색 )
	gotoxy(3, 5);	printf("Port : \n");
	textcolor(YELLOW);		// 출력 텍스트 색 변경 ( 노랑 )
	gotoxy(3, 6);	printf("Enter Port of server\n");
	textcolor(WHITE);		// 출력 텍스트 색 변경 ( 흰색 )

	// 입력 받는 변수들
	gotoxy(8, 2); gets(serverIp);
	gotoxy(10, 5); scanf("%d", &portNum);
}

// 메인메뉴 인터페이스 함수
void mainMenuInterface() {	
	// 콘솔 창 지우기
	system("cls");
	// 메인 메뉴 인터페이스
	gotoxy(2, 1); printf("Searching to Students Information \n\n");
	for (int i = 0; i <= LINE; i++) {
		textcolor(GREEN);	// 출력 텍스트 색 변경 ( 초록 )
		printf("=");
	}
	textcolor(WHITE);		// 출력 텍스트 색 변경 ( 흰색 )
	gotoxy(2, 5);		printf("1. Search for a Name\n");
	gotoxy(2, 7);		printf("2. Search by Nation\n");
	gotoxy(2, 9);		printf("3. Search by Department\n");
	gotoxy(2, 11);	printf("4. Search by Age\n");
	gotoxy(2, 13);	printf("5. Add or Delet Information\n");
	gotoxy(2, 15);	printf("6. Close\n");
	searchingInterface();	//  검색 인터페이스 창으로 이동
}

// 검색 인터페이스 창 함수
void searchingInterface() {
	fflush(stdin);	// 버퍼 초기화
	gotoxy(3, 18);	printf(">  ");	scanf("%d", &num);	// 목록 선택
	if (num == 6) {		// 6 선택시 종료
		c = 'q';
		system("cls");
		gotoxy(8, 3);
		textcolor(YELLOW);	printf("END\n\n\n");	textcolor(WHITE);
		exit(0);
	}
	getchar();
	switch (num) {
		case 1:
			gotoxy(3, 20);	printf("Enter a name >  "); gets(word); 
			c = 'c';
			findName();		// 이름 검색 인터페이스로 이동
			system("pause");
			break;
		case 2:
			gotoxy(3, 20);	printf("Enter a nation >  "); gets(word);
			c = 'n';
			findNation();		// 나라 검색 인터페이스로 이동
			system("pause");
			break;
		case 3:
			gotoxy(3, 20);	printf("Enter a depertment >  "); gets(word);
			c = 'd';
			findDepartment();	// 전공 검색 인터페이스로 이동
			system("pause");
			break;
		case 4:
			gotoxy(3, 20);	printf("Enter an age >  "); scanf("%d", &num);
			c = 'a';
			findAge();				// 나이 검색 인터페이스로 이동
			system("pause");
			break;
		case 5:
			information();			// 정보 추가 또는 제거 인터페이스
			system("pause");
			break;
		default:		// 잘못 입력할 시
			textcolor(RED);
			printf("Enter again\n");
			textcolor(WHITE);
			system("pause");
			break;
	}
}

// 정보 추가 또는 제거 인터페이스 함수
void information() {
	system("cls");
	fflush(stdin);
	gotoxy(3, 2);	printf("1. Add information  \n");
	gotoxy(3, 4);	printf("2. Delet information  \n");
	printf("\n");
	gotoxy(5, 6); printf(">  ");	 scanf("%d", &num);
	getchar();
	switch (num) {
		case 1:
			addInformation();	// 정보 추가 인터페이스로 이동
			break;
		case 2:
			delInformation();	// 정보 삭제 인터페이스로 이동
			break;
		default:		// 잘못 입력할 시 
			gotoxy(7, 7);	textcolor(RED);
			printf("Wrong");
			textcolor(WHITE);
			break;
	}
}

// 이름 검색 인터페이스 함수
void findName() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search for a name +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	gotoxy(3, 3);	printf("Name\n"); 
	gotoxy(10, 3);	printf("Age\n");
	gotoxy(16, 3);	printf("Nation\n");
	gotoxy(26, 3);	printf("Department\n");
	printf("\n");
}

// 나라 검색 인터페이스 함수
void findNation() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search by Nation +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	printf("\n\n");
}

// 전공 검색 인터페이스 함수
void findDepartment() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search by Department +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	printf("\n\n");
}

// 나이 검색 인터페이스 함수
void findAge() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search by Age +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	printf("\n\n");
}

// 정보 추가 인터페이스 함수
void addInformation() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1); printf("+ Name : \n");
	gotoxy(2, 3); printf("+ Age : \n");
	gotoxy(2, 5); printf("+ Nation : \n");
	gotoxy(2, 7); printf("+ Department : \n");
	// 입력
	gotoxy(11, 1); gets(student.name);
	gotoxy(10, 3); scanf("%d", &student.age);
	getchar();
	gotoxy(13, 5); gets(student.nation);
	gotoxy(17, 7); gets(student.depart);
	printf("\n");
	c = 'f';
}

// 정보 삭제 인터페이스 함수
void delInformation() {
	system("cls");
	fflush(stdin); 
	gotoxy(2, 1);	printf("Enter a name to delete\n");
	gotoxy(3, 3);	printf(">  ");	gets(word);
	textcolor(YELLOW);
	gotoxy(8, 5);	printf("+ Delete +\n");
	textcolor(WHITE);
	printf("\n");
	c = 'o';
}