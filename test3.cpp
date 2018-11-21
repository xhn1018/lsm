
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#include <iostream>

#include <cstdlib>
//#include <windows.h>
#include<thread>



//声
DWORD WINAPI Fun1Proc(LPVOID lpParameter);
void proc(LPVOID lpParameter)

{
	SOCKET clntSock = *(SOCKET*)lpParameter;
	//接收服务器传回的数据
	char szBuffer[MAXBYTE] = { 0 };
	recv(clntSock, szBuffer, MAXBYTE, NULL);
	//输出接收到的数据
	//printf("Message form client: %s\n", szBuffer);
	std::cout << "Message form client: " << szBuffer << std::endl;
	//strcat(szBuffer, "发送出去");
	//向客户端发送数据
	char *str = szBuffer;
	send(clntSock, str, strlen(str) + sizeof(char), NULL);
	//关闭套接字
	//closesocket(clntSock);
}
int main() {

	printf("start server\n");

	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET servSock = socket(PF_INET, SOCK_STREAM, 0);

	sockaddr_in sockAddr;

	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充

	sockAddr.sin_family = PF_INET;  //使用IPv4地址

	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址

	sockAddr.sin_port = htons(1234);  //端口

	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//进入监听状态

	listen(servSock, 20);

	//接收客户端请求

	//SOCKADDR clntAddr;

	SOCKADDR_IN clntAddr;



	int nSize = sizeof(SOCKADDR);

	while (true)

	{

		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		//if (clntSock == INVALID_SOCKET)
		//{
		//	//printf("无效socket\n");
		//	continue;
		//}
		//告诉用户谁上线

		char szIpAddress[16];

		strcpy_s(szIpAddress, sizeof(szIpAddress), inet_ntoa(clntAddr.sin_addr));

		std::cout << szIpAddress << "上线了" << std::endl;


		std::thread k(proc, (LPVOID)&clntSock);
		k.detach();
		/*HANDLE hThread_1 = CreateThread(NULL, 0, Fun1Proc, (LPVOID)&clntSock, 0, NULL);

		CloseHandle(hThread_1);*/

	}



	closesocket(servSock);

	//终止 DLL 的使用

	WSACleanup();

	printf("end server\n");

	system("pause");

	return 0;

}





DWORD WINAPI Fun1Proc(LPVOID lpParameter)

{

	SOCKET clntSock = *(SOCKET*)lpParameter;





	//接收服务器传回的数据

	char szBuffer[MAXBYTE] = { 0 };

	recv(clntSock, szBuffer, MAXBYTE, NULL);

	//输出接收到的数据

	//printf("Message form client: %s\n", szBuffer);

	std::cout << "Message form client: " << szBuffer <<std:: endl;



	//strcat(szBuffer, "发送出去");

	//向客户端发送数据

	char *str = szBuffer;

	send(clntSock, str, strlen(str) + sizeof(char), NULL);

	//关闭套接字

	//closesocket(clntSock);

	return 0;

}
