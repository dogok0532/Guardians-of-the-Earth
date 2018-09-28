// Client.c: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorHandling(char *message);

int main(){

	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	char sendmsg[30];

	int strLen;

	char ip_addr[16];

	printf("IP Address : ");
	scanf("%s", ip_addr);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //소켓 라이브러리를 초기화

		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성

	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip_addr);
	servAddr.sin_port = htons(9511);
	
	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //생성된 소켓으로 연결 요청
		ErrorHandling("connect() error!");
	while (strcmp(sendmsg,"exit\n")) {
		printf("Send to server: ");
		scanf("%s", sendmsg);
		strcat(sendmsg, "\n");
		send(hSocket, sendmsg, strlen(sendmsg), 0);
	
		strLen = recv(hSocket, message, sizeof(message),0); //recv 함수 호출 서버로부터 데이터를 수신
		
		
		

		if (strLen != -1)
		{	message[strLen] = '\0';
			printf("Message from server:%s\n", message);
		}
		//	ErrorHandling("read() error");
	
	}
	closesocket(hSocket); //소켓 라이브러리 해제
	
	WSACleanup();

	return 0;

}



void ErrorHandling(char *message){

	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}
