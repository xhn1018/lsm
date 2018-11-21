#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include <WinSock2.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#define BUF_SIZE 1024
int main() {
	//先输入文件名，看文件是否能创建成功
	char filename[100] = { 0 };  //文件名
	/*printf("Input filename to save: ");
	fgets(filename,10,stdin);*/
	FILE *fp = fopen("E:\\rec.iso", "wb");  //以二进制方式打开（创建）文件

	if (fp == NULL) {
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	int k = 1;
	while (k)
	{
		k = connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	}

	//循环接收数据，直到文件传输完毕
	char buffer[BUF_SIZE] = { 0 };  //文件缓冲区
	int nCount;
	while ((nCount = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
		fwrite(buffer, nCount, 1, fp);
	}
	puts("File transfer success!");

	//文件接收完毕后直接关闭套接字，无需调用shutdown()
	fclose(fp);
	closesocket(sock);
	WSACleanup();
	system("pause");
	return 0;
}