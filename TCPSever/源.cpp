#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(lib,"ws2_32.lib")  或者工程->链接器->输入->ws2_32.lib
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
	int temp=WSAStartup(sockSever, &wsadata);
	if (temp!=0)
	{
		cout << "WSAStartup()error!" << endl;
		return 0;
	}
	//create socket        family     流         tcp   
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (slisten==INVALID_SOCKET)
	{
		cout << "slisten error" << endl;
		return 0;
	}

	/*int
		WSAAPI
		bind(
			_In_ SOCKET s,
			_In_reads_bytes_(namelen) const struct sockaddr FAR * name,
			_In_ int namelen
		);*/
	
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	//htons  转端口号
	sin.sin_port = htons(ADD1);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	//绑定端口号        sockaddr_in
	if (bind(slisten, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		cout << "bind()error" << endl;
	}
	
	//监听
	if (listen(slisten,5)==SOCKET_ERROR)
	{
		cout << "listen()error" << endl;
		return -1;
	}
	SOCKET sclient;
	sockaddr_in remoteAddr;	
	int nAddrlen = sizeof(remoteAddr);
	char recvData[255];
	const char  sendData[255] = "你好,客户!";
	while (true)
	{
		cout << "等待连接" << endl;

		//接收1个连接  用新的socket通信
		sclient = accept(slisten, (sockaddr*)&remoteAddr,&nAddrlen);
		if (sclient==INVALID_SOCKET)
		{
			cout << "accept()error" << endl;
			continue;
		}

		//inet_ntoa用法
		cout << "接收到一个连接" << inet_ntoa(remoteAddr.sin_addr) << endl;
		//接收到的客户信息
		int ret = recv(sclient, recvData, 255, 0);
		if (ret>0)
		{
			recvData[ret] = 0x00;
			cout << recvData;
		}
		
		//给客户发信息
		/*send(sclient, sendData, strlen(sendData), 0);
		closesocket(sclient);*/
		//给客户发信息
		char buff[255];
		strcpy(buff, "hello.....");
		send(sclient, buff, strlen(buff), 0);
		closesocket(sclient);
	}

	closesocket(slisten);
	WSACleanup();
	system("pause");

}