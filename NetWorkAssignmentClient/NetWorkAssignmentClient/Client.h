#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <iostream>
#include <WS2tcpip.h>
#include <Windows.h>
#include <tuple>
#include <thread>
#include <cstdlib>
#include <string>

#define PORT 8080
#define PACKETSIZE 1024
#define IP "127.0.0.1" // ���� ��ÿ��� ������ ip�� ������ ���� ����� �־� �ٲ㼭 �����մϴ�.