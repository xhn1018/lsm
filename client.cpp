
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include<thread>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#include <iostream>
using namespace std;


int main() {

	//初始化DLL
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = NULL;

	while (true)
	{
		//创建套接字

		sock = socket(PF_INET, SOCK_STREAM,0);

		//向服务器发起请求

		sockaddr_in sockAddr;

		memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充

		sockAddr.sin_family = PF_INET;

		sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		sockAddr.sin_port = htons(1234);
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		cout << "Please input :";

		char sendString[500];

		cin >> sendString;



		strcat(sendString, "\n");

		//向服务端端发送数据

		char *sendStr = sendString;

		send(sock, sendStr, strlen(sendStr) + sizeof(char), NULL);



		cout << sendString << endl;



		//接收服务器传回的数据

		char szBuffer[MAXBYTE] = { 0 };

		recv(sock, szBuffer, MAXBYTE, NULL);

		//输出接收到的数据

		//	printf("Message form server: %s\n", szBuffer);

		cout << "Message form server:" << szBuffer << endl;

		//关闭套接字
		closesocket(sock);

	}
	//终止使用 DLL

	WSACleanup();

	system("pause");

	return 0;

}
