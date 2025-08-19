//
// Created by kWX1055060 on 2025/8/18.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/sendfile.h>
#include <sys/wait.h>

using namespace std;
#define PORT 8001

int main()
{
    struct sockaddr_in server_address;
    int client_sock_fd;
    int count = 0;

    //创建套接字
    client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock_fd < 0) {
        cout << "create client socket error, line " << __LINE__ <<endl;
        ::exit(-1);
    }
    memset(&server_address,0,sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        cout << "set ip error, line " << __LINE__ << endl;
        ::exit(-1);
    }

    int ret = connect(client_sock_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (ret) {
        cout << "conn to server error, line " << __LINE__ << endl;
        ::exit(-1);
    }
    cout << "connected to server successfully.\n";

    while (count < 10) {
        cout << "Enter message: ";
        string message;
        getline(cin, message);
        // send message to server
        send(client_sock_fd, message.c_str(), message.length(), 0);
        count++;
    }
    close(client_sock_fd);
    return 0;
}