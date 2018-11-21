#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
using namespace std;
#pragma comment (lib, "ws2_32.lib") //加载 ws2_32.dll
#define BUF_SIZE 1024
int main() {
	char *filename = (char*)"D:\\rec.iso"; //文件名
	FILE *fp = fopen(filename, "rb"); //以二进制方式打开文件
	if (fp == NULL) {
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	cout<<listen(servSock, 20)<<endl;
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);cout << 1 << endl;
	char buffer[BUF_SIZE] = { 0 };
	int nCount;
	
	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
		if (send(clntSock, buffer, nCount, 0) == -1) {
			cout << "disconected" << endl;

		
		}
		
	}

	shutdown(clntSock, SD_SEND); //文件读取完毕，断开输出流，向客户端发送FIN包
	//recv(clntSock, buffer, BUF_SIZE, 0); //阻塞，等待客户端接收完毕
	fclose(fp);
	closesocket(clntSock);
	closesocket(servSock);
	WSACleanup();

	system("pause");
	return 0;
}
