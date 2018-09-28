

#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <string>

using namespace std;

void ErrorHandling(string message);

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	char sendmsg[30];

	int strLen;

	if (argc != 3) {

		printf("Usage:%s <IP> <port>\n", argv[0]);
	//	exit(1);

	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //소켓 라이브러리를 초기화

		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성

	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);

	servAddr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //생성된 소켓을 바탕으로 서버에 연결을 요청
		ErrorHandling("connect() error!");
	while (strcmp(sendmsg, "exit\n")) {
		scanf("%s", sendmsg);
		strcat(sendmsg, "\n");
		send(hSocket, sendmsg, strlen(sendmsg), 0);

		strLen = recv(hSocket, message, sizeof(message) - 1, 0); //recv 함수 호출을 통해서 서버로부터 데이터를 수신
		message[strLen] = '\0';

		if (strLen == -1)
			ErrorHandling("read() error");

		printf("Message from server:%s\n", message);
	}
	closesocket(hSocket); //소켓 라이브러리 해제

	WSACleanup();

	return 0;

}

void ErrorHandling(string message) {

	cout << message << endl;
	exit(1);

}