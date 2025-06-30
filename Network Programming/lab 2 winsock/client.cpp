//For Client
#include<WinSock2.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")
# pragma warning(disable:4996)
using namespace std;
int main()
{


	cout << "\t\t------TCP Client-------" << endl;
	cout << endl;
	WSADATA Winsockdata;
	int iWsaStartup;
	int iWsaCleanup;

	SOCKET TCPClientSocket;
	int iCloseSocket;
	struct sockaddr_in TCPServerAdd;
	int iConnect;

	int iSend;
	char SenderBuffer[512] = "Hello from client";
	int iSenderBuffer = strlen(SenderBuffer) + 1;
	int iRecv;
	char RecvBuffer[512];
	int iRecvBuffer = strlen(RecvBuffer) + 1;

	//Step-1 WSAStartup Fun------------------------------------

	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
	if (iWsaStartup != 0)
	{
		cout << "WSAStartup Failed" << endl;
	}
	cout << "WSAStartup Success" << endl;

	//Step -2 Socket Creation------------------------------------

	TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TCPClientSocket == INVALID_SOCKET)
	{
		cout << "TCP Client Socket Creation failed" << WSAGetLastError() << endl;
	}
	cout << "TCP client socket creation success";
	// STEP -3 Fill the structure-------------------------------

	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	TCPServerAdd.sin_port = htons(8000);

	// STEP-4 Connect fun---------------------------------------------

	iConnect = connect(TCPClientSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (iConnect == SOCKET_ERROR)
	{
		cout << "Connection failed & Error No ->" << WSAGetLastError() << endl;
	}
	cout << "Connection success" << endl;

	// STEP -5 Recv Data from Server

	iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
	if (iRecv == SOCKET_ERROR)
	{
		cout << "Receiving Failed & Error No->" << WSAGetLastError() << endl;
	}
	cout << "Receive fun success" << endl;
	cout << "Data Received -> " << RecvBuffer << endl;

	// STEP-6 Send Data to the server

	iSend = send(TCPClientSocket, SenderBuffer, iSenderBuffer, 0);
	if (iSend == SOCKET_ERROR)
	{
		cout << "Sending Failed & Error No->" << WSAGetLastError() << endl;
	}
	cout << "Data sending success" << endl;

	//STEP - 7 Close Socket

		iCloseSocket = closesocket(TCPClientSocket);
	if (iCloseSocket == SOCKET_ERROR)
	{
		cout << "Closing Failed & Error No->" << WSAGetLastError() << endl;
	}
	cout << "Closing Socket success" << endl;


system("PAUSE");
return 0;
}