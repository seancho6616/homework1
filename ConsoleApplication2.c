//참조: http://remocon33.tistory.com/465
//개발목적 : 온라인 학생정보 서비스 클라이언트
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

#define MAX 16
#define	NUM 4
#define LINE 50
#define BUF_SIZE 100

unsigned WINAPI SendMsg(void* arg);//쓰레드 전송함수
unsigned WINAPI RecvMsg(void* arg);//쓰레드 수신함수

int main(int argc, char* argv[]) {
	
	ipInterface();

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(serverIp);
	serverAddr.sin_port = htons(portNum);

	connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	//접속에 성공하면 이 줄 아래가 실행된다.

	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);//메시지 전송용 쓰레드가 실행된다.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//메시지 수신용 쓰레드가 실행된다.
	while (1) {
		mainMenuInterface();
	}

	

	WaitForSingleObject(sendThread, INFINITE);//전송용 쓰레드가 중지될때까지 기다린다./
	WaitForSingleObject(recvThread, INFINITE);//수신용 쓰레드가 중지될때까지 기다린다.
	//클라이언트가 종료를 시도한다면 이줄 아래가 실행된다.
	closesocket(sock);//소켓을 종료한다.
	WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.

	return 0;
}

unsigned WINAPI SendMsg(void* arg) {//전송용 쓰레드함수
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char msg[BUF_SIZE] = "";
	while (1) {//반복
		switch (c) {
			case 'c':		// 이름 검색
			case 'n':		// 나라로 검색
			case 'd':		// 전공으로 검색
			case 'o':		// 정보 삭제
				sprintf(msg, "%c/%s", c, word);
				send(sock, msg, strlen(msg), 0);
				strcpy(msg, "");
				c = '\0';
				break;
			case 'a':		// 나이로 검색
				sprintf(msg, "%c/%d", c, num);
				send(sock, msg, strlen(msg), 0);
				strcpy(msg, "");
				c = '\0';
				break;
			case 'f':		// 정보 추가
				sprintf(msg, "%s/%d/%s/%s",
					student.name, student.age, student.nation, student.depart);
				send(sock, msg, strlen(msg), 0);
				strcpy(msg, "");
				c = '\0';
				break;
			case 'q':		// 프로그램 종료
				send(sock, "q", 1, 0);
				strcpy(msg, "");
				break;
		}
	}
	return 0;
}

unsigned WINAPI RecvMsg(void* arg) {
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char msg[BUF_SIZE] = "";
	int strLen;
	int i=3;
	char* w = NULL;
	while (1) {//반복
		strLen = recv(sock, msg, BUF_SIZE - 1, 0);//서버로부터 메시지를 수신한다.
		if (strLen == -1)
			return -1;
		msg[strLen] = '\0';//문자열의 끝을 알리기 위해 설정
		if (!strcmp(msg, "q")) {	// 프로그램 종료
			printf("Client : Disconnection\n");
			closesocket(sock);
			exit(0);
		}
		else {
			w = strtok(msg, "/");
			if (w != NULL) {
				sc = w[0];
				switch (sc) {
				case 'c':		// 이름  검색 결과 출력
					gotoxy(3, 4); printf("%s\n", strtok(NULL, "/"));
					gotoxy(13, 4); printf("%d\n", atoi(strtok(NULL, "/")));
					gotoxy(23, 4); printf("%s\n", strtok(NULL, "/"));
					gotoxy(33, 4); printf("%s\n", strtok(NULL, "/"));
					/*while (w != NULL) {
						gotoxy(i, 4); printf("%s\n", w);
						w = strtok(NULL, "/");
						i += 10;
					}*/
					strcpy(msg, "");
					break;
				case 'n':		// 나라로 검색한 결과 출력
				case 'd':		// 전공으로 검색한 결과 출력
				case 'a':		// 나이로 검색한 결과 출력
					while (w != NULL) {
						gotoxy(3, ++i); printf("%s\n", w);
						w = strtok(NULL, "/");
						i++;
					}
					break;
				case 'f':		// 정보 추가 확인 출력
					textcolor(YELLOW);
					gotoxy(9, 10);	printf("Add Information\n");
					textcolor(WHITE);
					break;
				case 'o':		// 정보 삭제 확인 출력
					textcolor(YELLOW);
					gotoxy(8, 5);	printf("+Delete +\n");
					textcolor(WHITE);
					break;
				}
			}
		}
		strcpy(msg, "");
	}
	return 0;
}


//void main() {
//	while (1) {
//		mainMenuInterface();
//	}
//}