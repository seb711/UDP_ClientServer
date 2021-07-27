// UDP_Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "Data.cpp"

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

void main(int argc, char* argv[]) { //We can pass in a commandline Option
	//Startup Winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "Cant start winsock" << wsOk;
		return;
	}

	//Create a hint structure for the server
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);

	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
	//Socket creation 
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
	//Write out to that socket
	string s(argv[1]);


	for (int i = 0; i <= 5; i++) {
		DataObject* obj = new DataObject(11, 3.2);
		int n = 0;    // n is the number of bytes of 'buf' after converting the integer to 'buf'
		char buf[1024];
		ZeroMemory(buf, 1024);

		n = sprintf_s(buf, "%d", obj->getNumber());
		if (sendto(out, buf, 1024, 0, (sockaddr*)&server, sizeof(server)) == -1)
			cout << "ERROR: Problem sending data";

		n = sprintf_s(buf, "%d", obj->getGpa());
		if (sendto(out, buf, 1024, 0, (sockaddr*)&server, sizeof(server)) == -1)
			cout << "ERROR: Problem sending data";
	}


	/*int sendOk = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));

	if (sendOk == SOCKET_ERROR)
	{
		cout << "That didnt work" << WSAGetLastError() << endl;
	}*/
	//Close the socket
	closesocket(out);

	// CLose down Winsock
	WSACleanup();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
