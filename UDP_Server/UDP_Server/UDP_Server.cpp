#include <iostream>
#include <WS2tcpip.h>
#include "DataObject.cpp"

#pragma comment (lib, "ws2_32.lib")

using namespace std; //saves us from typing std::cout << etc. etc. etc.

class data
{
private:
	int number;
	float gpa;
public:
	data(int number, float gpa) {
		this->number = number;
	}
	void print() {
		cout << "number : " << number << "gpa : " << gpa;
	}
	int getNumber() {
		return this->number;
	}
	int getGpa() {
		return this->number;
	}
};

void main() {
	//Startup Winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "Cant start winsock" << wsOk;
		return;
	}
	//Bind socket to ip address to port
	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(54000); //Convert from litte to big endian

	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "cant bind socket!" << WSAGetLastError() << endl;
	}

	sockaddr_in client;
	int clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);

	char buf[1024];

	//Enter a loop
	while (true)
	{
		ZeroMemory(buf, 1024);

		////Wait for message
		//int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
		//if (bytesIn == SOCKET_ERROR)
		//{
		//	cout << "Error reveriving from client" << WSAGetLastError() << endl;
		//	continue;
		//}
		
		DataObject* obj;
		int number = 0;
		float gpa = 0.0;

		if (recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength) == -1)
			cout << "ERROR: recvfrom()";
		number = atoi(buf);

		if (recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength) == -1)
			cout << "ERROR: recvfrom()";
		gpa = atoi(buf);

		obj = new DataObject(number, gpa);

		cout << "\nRECEIVED from Client : ";
		obj->print();
		cout << "\n\n";

		// Display message and client info
		char clientIp[256];
		ZeroMemory(clientIp, 256);

		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

		cout << "Message recv from " << clientIp << " : " << buf << endl;
	}


	//Close socket
	closesocket(in);

	//Shutdown winsock
	WSACleanup();
}