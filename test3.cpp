
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
#include <iostream>

#include <cstdlib>
//#include <windows.h>
#include<thread>



//��
DWORD WINAPI Fun1Proc(LPVOID lpParameter);
void proc(LPVOID lpParameter)

{
	SOCKET clntSock = *(SOCKET*)lpParameter;
	//���շ��������ص�����
	char szBuffer[MAXBYTE] = { 0 };
	recv(clntSock, szBuffer, MAXBYTE, NULL);
	//������յ�������
	//printf("Message form client: %s\n", szBuffer);
	std::cout << "Message form client: " << szBuffer << std::endl;
	//strcat(szBuffer, "���ͳ�ȥ");
	//��ͻ��˷�������
	char *str = szBuffer;
	send(clntSock, str, strlen(str) + sizeof(char), NULL);
	//�ر��׽���
	//closesocket(clntSock);
}
int main() {

	printf("start server\n");

	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET servSock = socket(PF_INET, SOCK_STREAM, 0);

	sockaddr_in sockAddr;

	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���

	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ

	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ

	sockAddr.sin_port = htons(1234);  //�˿�

	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//�������״̬

	listen(servSock, 20);

	//���տͻ�������

	//SOCKADDR clntAddr;

	SOCKADDR_IN clntAddr;



	int nSize = sizeof(SOCKADDR);

	while (true)

	{

		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		//if (clntSock == INVALID_SOCKET)
		//{
		//	//printf("��Чsocket\n");
		//	continue;
		//}
		//�����û�˭����

		char szIpAddress[16];

		strcpy_s(szIpAddress, sizeof(szIpAddress), inet_ntoa(clntAddr.sin_addr));

		std::cout << szIpAddress << "������" << std::endl;


		std::thread k(proc, (LPVOID)&clntSock);
		k.detach();
		/*HANDLE hThread_1 = CreateThread(NULL, 0, Fun1Proc, (LPVOID)&clntSock, 0, NULL);

		CloseHandle(hThread_1);*/

	}



	closesocket(servSock);

	//��ֹ DLL ��ʹ��

	WSACleanup();

	printf("end server\n");

	system("pause");

	return 0;

}





DWORD WINAPI Fun1Proc(LPVOID lpParameter)

{

	SOCKET clntSock = *(SOCKET*)lpParameter;





	//���շ��������ص�����

	char szBuffer[MAXBYTE] = { 0 };

	recv(clntSock, szBuffer, MAXBYTE, NULL);

	//������յ�������

	//printf("Message form client: %s\n", szBuffer);

	std::cout << "Message form client: " << szBuffer <<std:: endl;



	//strcat(szBuffer, "���ͳ�ȥ");

	//��ͻ��˷�������

	char *str = szBuffer;

	send(clntSock, str, strlen(str) + sizeof(char), NULL);

	//�ر��׽���

	//closesocket(clntSock);

	return 0;

}