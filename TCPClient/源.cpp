#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS



#pragma comment(lib,"ws2_32.lib") // 或者工程->链接器->输入->ws2_32.lib
#include <stdlib.h>
#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <Windows.h>

using namespace std;
#define ADD1 8888
int main()
{
	WSADATA wsadata;
	WORD sockSever = MAKEWORD(2, 2);
	////int WSAAPI WSAStartup(
	//		_In_ WORD wVersionRequested,
	//		_Out_ LPWSADATA lpWSAData
	//	);
	//       调用socket 版本
	int temp = WSAStartup(sockSever, &wsadata);
	if (temp != 0)
	{
		cout << "WSAStartup()error!" << endl;
		return 0;
	}

	//create socket
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (slisten == INVALID_SOCKET)
	{
		cout << "slisten error" << endl;
		return 0;
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr= inet_addr("127.0.0.1");
	sin.sin_port = htons(ADD1);
	//连接主机
	int temp1=connect(slisten, (sockaddr*)&sin, sizeof(sin));
	/*if (sclient==SOCKET_ERROR)
	{
		cout << "connect() fail" << endl;
		WSACleanup();
		return -1;
	}*/
	while (1) {
		char buff[255];
		strcpy(buff, "hello.....");
		//发信息
		send(slisten, buff, strlen(buff), 0);

		char recvData[255];
		//接收信息
		int ret = recv(slisten, recvData, 255, 0);
		if (ret > 0)
		{

			recvData[ret] = 0x00;
			cout << recvData << "sdfsd" << endl;
		}

		
	}
	cout << "...." << endl;
	system("pause");
	closesocket(slisten);
	WSACleanup();
	return 0;
}