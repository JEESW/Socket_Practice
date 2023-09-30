#include "Client.h"

int main()
{
    int step;
    char name[PACKETSIZE];
    char password[PACKETSIZE];
    char buffer[PACKETSIZE];
    char mode[PACKETSIZE];
    char quit_message[PACKETSIZE] = "/quit";
    char delete_message[PACKETSIZE] = "/deleteID";

    ZeroMemory(name, sizeof(name));
    ZeroMemory(password, sizeof(password));
    ZeroMemory(buffer, sizeof(buffer));
    ZeroMemory(mode, sizeof(mode));
    
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    SOCKET client;
    client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_port = (PORT);
    inet_pton(AF_INET, IP, &(addr.sin_addr));

    while (connect(client, (SOCKADDR*)&addr, sizeof(addr)));

    std::cout << "------------------------------" << std::endl;
    std::cout << "| 1. ȸ������                |" << std::endl;
    std::cout << "| 2. �α���                  |" << std::endl;
    std::cout << "------------------------------" << std::endl;
    
    while (TRUE) {
        std::cin >> step;

        if (step == 1) {
            std::strcpy(mode, "/sign_mode");
            break;
        }

        else if (step == 2) {
            std::strcpy(mode, "/login_mode");
            break;
        }
    }

    if (!std::strcmp(mode, "/sign_mode")) {
        std::cout << std::endl;
        std::cout << "<<ȸ������>>" << std::endl;
        std::cout << "���̵�(�г���)�� �Է��ϼ��� : ";
        std::cin >> name;
        std::cout << "�н����带 �Է��ϼ��� : ";
        std::cin >> password;

        send(client, mode, sizeof(mode), 0);
        send(client, name, sizeof(name), 0);
        send(client, password, sizeof(password), 0);
        send(client, mode, sizeof(mode), 0);
        recv(client, buffer, sizeof(buffer), 0);

        if (!std::strcmp(buffer, "0")) {
            std::cout << std::endl;
            std::cout << "ȸ�������� �Ϸ� �Ǿ����ϴ�!" << std::endl;
            std::cout << std::endl;
            std::strcpy(mode, "/login_mode");
        }

        else
        {
            std::cout << std::endl;
            std::cout << "ȸ�����Կ� �����Ͽ����ϴ�!" << std::endl;
            std::cout << std::endl;

            closesocket(client);
            WSACleanup();
        }

        ZeroMemory(name, sizeof(name));
        ZeroMemory(password, sizeof(password));
        ZeroMemory(buffer, sizeof(buffer));
    }

    if (!std::strcmp(mode, "/login_mode")) {
        std::cout << std::endl;
        std::cout << "<<�α���>>" << std::endl;
        std::cout << "���̵�(�г���)�� �Է��ϼ��� : ";
        std::cin >> name;
        std::cout << "�н����带 �Է��ϼ��� : ";
        std::cin >> password;

        send(client, mode, sizeof(mode), 0);
        send(client, name, sizeof(name), 0);
        send(client, password, sizeof(password), 0);
        send(client, mode, sizeof(mode), 0);
        recv(client, buffer, sizeof(buffer), 0);

        if (!std::strcmp(buffer, "1")) {
            std::cout << std::endl;
            std::cout << "�α����� �Ϸ� �Ǿ����ϴ�!" << std::endl;
            std::cout << std::endl;
            std::strcpy(mode, "/chat_mode");
        }

        else
        {
            std::cout << std::endl;
            std::cout << "ȸ�� ������ ��ġ���� �ʽ��ϴ�!" << std::endl;
            std::cout << std::endl;

            closesocket(client);
            WSACleanup();
        }

        ZeroMemory(password, sizeof(password));
        ZeroMemory(buffer, sizeof(buffer));
    }

    if (!std::strcmp(mode, "/chat_mode")) {
        std::cout << std::endl;
        std::cout << "�������! ä�ü����� �����ϼ̽��ϴ�." << std::endl;
        std::cout << std::endl;

        send(client, mode, sizeof(mode), 0);
        send(client, name, sizeof(name), 0);
        
        std::cin.ignore(10, '\n');

        while (TRUE)
        {
            ZeroMemory(name, sizeof(name));
            std::cout << "�޼����� �Է��ϼ���: ";
            std::cin.getline(name, sizeof(name), '\n');
            
            if (!std::strcmp(name, "/quit")) {
                send(client, quit_message, sizeof(quit_message), 0);
                closesocket(client);
                WSACleanup();
                break;
            }

            else if (!std::strcmp(name, "/deleteID")) {
                send(client, delete_message, sizeof(delete_message), 0);
                closesocket(client);
                WSACleanup();
                break;
            }

            send(client, name, sizeof name, 0);
        }
    }

    else
    {
        std::cout << "Error!" << std::endl;
        closesocket(client);
        WSACleanup();
    }
}