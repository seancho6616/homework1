#define _WINSOCK_DEPRECATED_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� ���ϰ��� ��� ���ÿ�
#define _CRT_SECURE_NO_WARNINGS 
#pragma comment(lib, "ws2_32")  //���־�Ʃ��� ȯ�濡�� ���߽� ���� ���̺귯�� ������

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

ST student;			// Ŭ���̾�Ʈ���� ����� ����ü
ST* stInfor=NULL;			// �������� ���� ���� ����

// �ؽ�Ʈ �� ���� �Լ�
void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}


// ��ġ �̵� �Լ�
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// IP�� Port��ȣ �ޱ� ���� �������̽� �Լ�
void ipInterface() {
	// �ܼ� â �����
	system("cls");
	// �������̽�
	gotoxy(3, 2);	printf("IP : \n");
	textcolor(YELLOW);		// ��� �ؽ�Ʈ �� ���� ( ��� )
	gotoxy(3, 3);	printf("Enter IP of server\n");
	textcolor(WHITE);		// ��� �ؽ�Ʈ �� ���� ( ��� )
	gotoxy(3, 5);	printf("Port : \n");
	textcolor(YELLOW);		// ��� �ؽ�Ʈ �� ���� ( ��� )
	gotoxy(3, 6);	printf("Enter Port of server\n");
	textcolor(WHITE);		// ��� �ؽ�Ʈ �� ���� ( ��� )

	// �Է� �޴� ������
	gotoxy(8, 2); gets(serverIp);
	gotoxy(10, 5); scanf("%d", &portNum);
}

// ���θ޴� �������̽� �Լ�
void mainMenuInterface() {	
	// �ܼ� â �����
	system("cls");
	// ���� �޴� �������̽�
	gotoxy(2, 1); printf("Searching to Students Information \n\n");
	for (int i = 0; i <= LINE; i++) {
		textcolor(GREEN);	// ��� �ؽ�Ʈ �� ���� ( �ʷ� )
		printf("=");
	}
	textcolor(WHITE);		// ��� �ؽ�Ʈ �� ���� ( ��� )
	gotoxy(2, 5);		printf("1. Search for a Name\n");
	gotoxy(2, 7);		printf("2. Search by Nation\n");
	gotoxy(2, 9);		printf("3. Search by Department\n");
	gotoxy(2, 11);	printf("4. Search by Age\n");
	gotoxy(2, 13);	printf("5. Add or Delet Information\n");
	gotoxy(2, 15);	printf("6. Close\n");
	searchingInterface();	//  �˻� �������̽� â���� �̵�
}

// �˻� �������̽� â �Լ�
void searchingInterface() {
	fflush(stdin);	// ���� �ʱ�ȭ
	gotoxy(3, 18);	printf(">  ");	scanf("%d", &num);	// ��� ����
	if (num == 6) {		// 6 ���ý� ����
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
			findName();		// �̸� �˻� �������̽��� �̵�
			system("pause");
			break;
		case 2:
			gotoxy(3, 20);	printf("Enter a nation >  "); gets(word);
			c = 'n';
			findNation();		// ���� �˻� �������̽��� �̵�
			system("pause");
			break;
		case 3:
			gotoxy(3, 20);	printf("Enter a depertment >  "); gets(word);
			c = 'd';
			findDepartment();	// ���� �˻� �������̽��� �̵�
			system("pause");
			break;
		case 4:
			gotoxy(3, 20);	printf("Enter an age >  "); scanf("%d", &num);
			c = 'a';
			findAge();				// ���� �˻� �������̽��� �̵�
			system("pause");
			break;
		case 5:
			information();			// ���� �߰� �Ǵ� ���� �������̽�
			system("pause");
			break;
		default:		// �߸� �Է��� ��
			textcolor(RED);
			printf("Enter again\n");
			textcolor(WHITE);
			system("pause");
			break;
	}
}

// ���� �߰� �Ǵ� ���� �������̽� �Լ�
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
			addInformation();	// ���� �߰� �������̽��� �̵�
			break;
		case 2:
			delInformation();	// ���� ���� �������̽��� �̵�
			break;
		default:		// �߸� �Է��� �� 
			gotoxy(7, 7);	textcolor(RED);
			printf("Wrong");
			textcolor(WHITE);
			break;
	}
}

// �̸� �˻� �������̽� �Լ�
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

// ���� �˻� �������̽� �Լ�
void findNation() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search by Nation +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	printf("\n\n");
}

// ���� �˻� �������̽� �Լ�
void findDepartment() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search by Department +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	printf("\n\n");
}

// ���� �˻� �������̽� �Լ�
void findAge() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1);	printf("+ Search by Age +\n");
	for (int i = 0; i <= LINE; i++) {
		printf("-");
	}
	printf("\n\n");
}

// ���� �߰� �������̽� �Լ�
void addInformation() {
	system("cls");
	fflush(stdin);
	gotoxy(2, 1); printf("+ Name : \n");
	gotoxy(2, 3); printf("+ Age : \n");
	gotoxy(2, 5); printf("+ Nation : \n");
	gotoxy(2, 7); printf("+ Department : \n");
	// �Է�
	gotoxy(11, 1); gets(student.name);
	gotoxy(10, 3); scanf("%d", &student.age);
	getchar();
	gotoxy(13, 5); gets(student.nation);
	gotoxy(17, 7); gets(student.depart);
	printf("\n");
	c = 'f';
}

// ���� ���� �������̽� �Լ�
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