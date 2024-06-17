//참조: http://remocon33.tistory.com/465
//개발목적 : 온라인 학생정보 서비스 서버
#define _WINSOCK_DEPRECATED_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 소켓관련 경고 무시용
#define _CRT_SECURE_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 입력관련 경고 무시용
#pragma comment(lib, "ws2_32")  //비주얼스튜디오 환경에서 개발시 소켓 라이브러리 지정용

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <time.h>
#include "students.h"

#define BUF_SIZE 100 
#define MAX_CLNT 256
#define STD_MAX_NUM 100
#define WHITE 15
#define YELLOW 6
#define BLUE 9
#define MAX 16
#define	NUM 4

void setStudentData(FILE* fp);
void saveStudentData(FILE* fp);

unsigned WINAPI HandleClient(void* arg);//Thread for Each CLient
//void SendMsg(char* msg, int len);//Message Sending Function from server to client

int clientCount = 0;
SOCKET clientSocks[MAX_CLNT];// Array for sockets which are connected to clients
HANDLE hMutex;// Mudex Handle
ST* stInfor=NULL;			// 서버에서 받은 정보 저장

int std_cnt = 0;
char word[MAX] = "";

//void main() {
//	FILE* fpin;//파일포인터변수의선언
//	if ((fpin = fopen("students.txt", "r")) == NULL) {
//		printf("File open error...\n");
//		exit(-1);
//	}
//	setStudentData(fpin);
//	ST* temp = stInfor;
//	while (!temp == NULL) {
//		printf("%s\t%d\t%s\t%s\n\n", temp->name, temp->age, temp->nation, temp->depart);
//		temp = temp->next;
//		
//	}
//	printf("%d", std_cnt);
//}

int main(int argc, char* argv[]) {

	FILE* fpin;//파일포인터변수의선언
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	HANDLE hThread;
	int portNum;

	// Start of Students Information Loading form the file
	if ((fpin = fopen("students.txt", "r")) == NULL) {
		printf("File open error...\n");
		exit(-1);
	}
	setStudentData(fpin);
	// End of Students Information Load

	// Start of Server Socket Preparation
	printf("Server : Set Server Port number (Please use integer number between 49152 to 65535) : ");
	scanf("%d", &portNum);
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	hMutex = CreateMutex(NULL, FALSE, NULL);//하나의 뮤텍스를 생성한다.
	serverSock = socket(PF_INET, SOCK_STREAM, 0); //하나의 소켓을 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(portNum);
	bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	// End of Server Socket Preparation and Activation	

	listen(serverSock, 5);  // 5 refers the size of queue which is waiting area of connection requestion from client
	printf("Server : Ready to Client Connection\n");

	while (1) {
		clientAddrSize = sizeof(clientAddr);
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//서버에게 전달된 클라이언트 소켓을 clientSock에 전달
		WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
		clientSocks[clientCount++] = clientSock;//클라이언트 소켓배열에 방금 가져온 소켓 주소를 전달
		ReleaseMutex(hMutex);//뮤텍스 중지
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient 쓰레드 실행, clientSock을 매개변수로 전달
		// _beginthreadex함수는 세번째 파라메터가 스레드로서 실행될 함수명, 네번째 파라메터가 해당 함수 호출 시 필요한 매개변수임 
		printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
	}

	closesocket(serverSock);//생성한 소켓을 끈다.
	WSACleanup();//윈도우 소켓을 종료하겠다는 사실을 운영체제에 전달
	return 0;
}

unsigned WINAPI HandleClient(void* arg) {
	SOCKET clientSock = *((SOCKET*)arg); //매개변수로받은 클라이언트 소켓을 전달
	int strLen = 0, i=3;
	char msg[BUF_SIZE] = "";
	char result[BUF_SIZE] = "";
	char* w = NULL;

	while (1) { //클라이언트로부터 메시지를 받을때까지 기다린다.
		strcpy(msg, "");
		strLen = 0;
		strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
		msg[strLen] = '\0';
		printf("Server : Resieved Message -> %s\n", msg);  //확인용 
		if (!strcmp(msg, "q")) {
			send(clientSock, "q", 1, 0);
			break;
		}
		else {          //Client는 찾고자 하는 학생의 이름만 보낸다고 가정 
			w = strtok(msg, "/");
			sc = w[0];
			printf("%c\n", sc);
			ST* temp = stInfor;
			switch (sc) {
				case 'c':
					strcpy(word, strtok(NULL, "/"));
					printf("%s\n", word);
					while ((temp != NULL) && strcmp(temp->name, word)) {
						temp = temp->next;
					}
					if (temp == NULL) {
						printf("Send No Result Message\n");
						send(result, "x", 1, 0);
						strcpy(result, "");
					}
					else {
						sprintf(result, "%c/%s/%d/%s/%s", sc,
							temp->name, temp->age, temp->nation, temp->depart);
						send(clientSock, result, strlen(result), 0);
						printf("%s\n", result);
						printf("Send Result\n");
						strcpy(result, "");
					}
					sc = '\0';
					free(temp);
					break;
				case 'n':
					strcpy(word, strtok(NULL, "/"));
					while (temp !=NULL) {
						if (!strcmp(temp->nation, word)) {
							sprintf(result, "%c/%s", sc, temp->nation);
							send(clientSock, result, strlen(result), 0);
							strcpy(result, "");
						}
						else {
							printf("Send No Result Message\n");
							send(result, "x", 1, 0);
							strcpy(result, "");
						}
						temp = temp->next;
					}
					sc = '\0';
					free(temp);
					break;
				case 'd':
					strcpy(word, strtok(NULL, "/"));
					while (temp != NULL) {
						if (!strcmp(temp->depart, word)) {
							sprintf(result, "%c/%s", sc, temp->depart);
							send(clientSock, result, strlen(result), 0);
							strcpy(result, "");
						}
						else {
							printf("Send No Result Message\n");
							send(result, "x", 1, 0);
							strcpy(result, "");
						}
						temp = temp->next;
					}
					sc = '\0';
					free(temp);
					break;
				case 'a':
					num = atoi(strtok(NULL, "/"));
					while (temp != NULL) {
						if (num == temp->age) {
							sprintf(result, "%c/%d", sc, temp->age);
							send(clientSock, result, strlen(result), 0);
							strcpy(result, "");
						}
						else {
							printf("Send No Result Message\n");
							send(result, "x", 1, 0);
							strcpy(result, "");
						}
						temp = temp->next;
					}
					sc = '\0';
					free(temp);
					break;
				case 'f':
					printf("recve information\n");
					strcpy(temp->name, strtok(NULL, "/"));
					strcpy(temp->age, atoi(strtok(NULL, "/")));
					strcpy(temp->nation, strtok(NULL, "/"));
					strcpy(temp->depart, strtok(NULL, "/"));
					send(clientSock, sc, 1, 0);
					sc = '\0';
					break;
				case 'o':
					strcpy(word, strtok(NULL, "/"));
					ST *current=NULL;
					while ((temp != NULL) && (temp->name) != word) {
						current->next = temp;
						temp = temp->next;
					}
					current->next = NULL;
					sc = '\0';
					free(temp);
					break;
			}
			
			
		}
	}

	printf("client left the Server\n");
	//이 줄을 실행한다는 것은 해당 클라이언트가 나갔다는 사실임 따라서 해당 클라이언트를 배열에서 제거해줘야함
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	clientCount--;//클라이언트 개수 하나 감소
	ReleaseMutex(hMutex);//뮤텍스 중지
	closesocket(clientSock);//소켓을 종료한다.
	return 0;
}


void setStudentData(FILE* fp) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	printf("Server : Initiation of Data Load \n");
	while (!feof(fp)) {
		ST* current = (ST*)malloc(sizeof(ST));
		fscanf(fp, "%s\t%d\t%s\t%s", current->name, &current->age, current->nation, current->depart); //파일로부터읽기
		//	printf("%s\t%d\t%s\t%s\n",students[std_cnt].name,students[std_cnt].age, students[std_cnt].nation, students[std_cnt].depart); 
		std_cnt++;
		current->next = stInfor;
		stInfor = current;
	}
	printf("Server : End of Data Loading \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void saveStudentData(FILE* fp) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	printf("Server : saveing of Data Load \n");
	ST* current = stInfor;
	while (current != NULL) {
		fprintf(fp, "%s\t%d\t%s\t%s\n", current->name, current->age, current->nation, current->depart);
		current->next = stInfor;
	}
	printf("Server : End of Data Loading \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}