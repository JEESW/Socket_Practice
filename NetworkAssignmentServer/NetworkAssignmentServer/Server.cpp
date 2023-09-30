#include "Server.h"

void recvData(SOCKET s, int num) {
    char name[PACKETSIZE] = { 0 };
    char password[PACKETSIZE] = { 0 };
    char mode[PACKETSIZE] = { 0 };

    recv(s, mode, sizeof(mode), 0);
    std::get<3>(Client[num]) = mode;

    if (!std::strcmp(std::get<3>(Client[num]).c_str(), "/sign_mode")) {
        ZeroMemory(name, sizeof(name));
        ZeroMemory(password, sizeof(password));
        ZeroMemory(mode, sizeof(mode));

        recv(s, name, sizeof(name), 0);
        recv(s, password, sizeof(password), 0);
        recv(s, mode, sizeof(mode), 0);

        std::get<1>(Client[num]) = name;
        std::get<2>(Client[num]) = password;
        std::get<3>(Client[num]) = mode;
    }

    recv(s, mode, sizeof(mode), 0);
    std::get<3>(Client[num]) = mode;

    if (!std::strcmp(std::get<3>(Client[num]).c_str(), "/login_mode")) {
        ZeroMemory(name, sizeof(name));
        ZeroMemory(password, sizeof(password));
        ZeroMemory(mode, sizeof(mode));

        recv(s, name, sizeof(name), 0);
        recv(s, password, sizeof(password), 0);
        recv(s, mode, sizeof(mode), 0);

        std::get<1>(Client[num]) = name;
        std::get<2>(Client[num]) = password;
        std::get<3>(Client[num]) = mode;
    }

    recv(s, mode, sizeof(mode), 0);
    std::get<3>(Client[num]) = mode;

    if (!std::strcmp(std::get<3>(Client[num]).c_str(), "/chat_mode")) {
        recv(s, name, sizeof(name), 0);
        std::get<1>(Client[num]) = name;

        while (TRUE) {
            ZeroMemory(name, sizeof(name));
            recv(s, name, sizeof(name), 0);

            if (!std::strcmp(name, "")) {
                std::cout << std::get<1>(Client[num]).c_str() << "님이 퇴장하였습니다!" << std::endl;
                break;
            }

            else if (!std::strcmp(name, "/quit")) {
                std::cout << std::get<1>(Client[num]).c_str() << "님이 퇴장하였습니다!" << std::endl;
                break;
            }

            else if (!std::strcmp(name, "/deleteID")) {

                std::cout << std::get<1>(Client[num]).c_str() << "님의 회원 정보가 삭제되었습니다!" << std::endl;

                std::get<1>(Client[num]) = { 0 };
                std::get<2>(Client[num]) = { 0 };
                std::get<3>(Client[num]) = { 0 };
                break;
            }

            std::cout << std::get<1>(Client[num]) << " : " << name << std::endl;
        }
    }
}

void ACCEPT(SOCKET& s)
{
    int cnt = 0;
    while (TRUE) {
        Client.push_back(pil(CLIENT(), "", "", ""));
        std::get<0>(Client[cnt]).client = accept(s, (SOCKADDR*)&std::get<0>(Client[cnt]).clientaddr, &std::get<0>(Client[cnt]).clientsize);
        std::get<0>(Client[cnt]).num = cnt;
        std::thread(recvData, std::get<0>(Client[cnt]).client, cnt).detach();
        cnt += 1;
    }
}

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET server;
    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = (PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);


    bind(server, (SOCKADDR*)&addr, sizeof(addr));
    listen(server, SOMAXCONN);

    std::thread(ACCEPT, std::ref(server)).detach();
    
    char name[PACKETSIZE];
    char key[PACKETSIZE];

    char namedb[100][PACKETSIZE], passworddb[100][PACKETSIZE], modedb[100][PACKETSIZE];

    for (int i = 0; i < 100; i++) {
        ZeroMemory(namedb[i], sizeof(namedb[i]));
        ZeroMemory(passworddb[i], sizeof(passworddb[i]));
        ZeroMemory(modedb[i], sizeof(modedb[i]));
    }

    while (TRUE) {
        ZeroMemory(name, sizeof(name));
        ZeroMemory(key, sizeof(key));
        std::cin >> name;
        for (int i = 0; i < Client.size(); i++) {
            if (!strcmp(std::get<1>(Client[i]).c_str(), name)) {
                if (!std::strcmp(std::get<3>(Client[i]).c_str(), "/sign_mode")) {
                    std::strcpy(namedb[i], std::get<1>(Client[i]).c_str());
                    std::strcpy(passworddb[i], std::get<2>(Client[i]).c_str());

                    std::strcpy(key, "0");
                    send(std::get<0>(Client[i]).client, key, sizeof(key), 0);
                }

                else if (!std::strcmp(std::get<3>(Client[i]).c_str(), "/login_mode")) {
                    for (int j = 0; j < 100; j++) {
                        if (!std::strcmp(name, namedb[j])) {
                            if (!std::strcmp(std::get<2>(Client[i]).c_str(), passworddb[j])) {
                                std::strcpy(key, "1");
                                std::cout << std::get<1>(Client[i]).c_str() << "님이 입장하였습니다!" << std::endl;
                                break;
                            }
                        }
                    }

                    send(std::get<0>(Client[i]).client, key, sizeof(key), 0);
                }

                else if (!std::strcmp(std::get<3>(Client[i]).c_str(), "/chat_mode")) {

                }
            }
        }
    }

    closesocket(server);
    WSACleanup();
}