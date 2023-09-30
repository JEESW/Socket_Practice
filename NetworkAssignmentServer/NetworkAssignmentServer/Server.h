#pragma once
#pragma comment(lib, "ws2_32")
#pragma warning(disable: 4996)

#include <iostream>
#include <WS2tcpip.h>
#include <Windows.h>
#include <vector>
#include <utility>
#include <tuple>
#include <thread>
#include <string.h>

#define PORT 8080
#define PACKETSIZE 1024

class CLIENT {
public:
	SOCKET client;
	SOCKADDR_IN clientaddr = { 0 };
	int clientsize = sizeof clientaddr;
	int num = -1;
	CLIENT() { }
};

typedef std::tuple<CLIENT, std::string, std::string, std::string> pil;

std::vector<pil> Client;