
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include<thread>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll
#include <iostream>
using namespace std;


int main() {

	//��ʼ��DLL
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = NULL;

	while (true)
	{
		//�����׽���

		sock = socket(PF_INET, SOCK_STREAM,0);

		//���������������

		sockaddr_in sockAddr;

		memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���

		sockAddr.sin_family = PF_INET;

		sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		sockAddr.sin_port = htons(1234);
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		cout << "Please input :";

		char sendString[500];

		cin >> sendString;



		strcat(sendString, "\n");

		//�����˶˷�������

		char *sendStr = sendString;

		send(sock, sendStr, strlen(sendStr) + sizeof(char), NULL);



		cout << sendString << endl;



		//���շ��������ص�����

		char szBuffer[MAXBYTE] = { 0 };

		recv(sock, szBuffer, MAXBYTE, NULL);

		//������յ�������

		//	printf("Message form server: %s\n", szBuffer);

		cout << "Message form server:" << szBuffer << endl;

		//�ر��׽���
		closesocket(sock);

	}
	//��ֹʹ�� DLL

	WSACleanup();

	system("pause");

	return 0;

}