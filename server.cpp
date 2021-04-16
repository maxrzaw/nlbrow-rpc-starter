// Credit to Brendan Campbell for original server.cpp code.
// Modified by vhao.
// Modified by nlbrow.

#include "server.h"

#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "ERROR: Usage is './server <port>'" << endl;
        return 0;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int yesval = 1;
    int port = atoi(argv[1]);

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yesval, sizeof(yesval));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (::bind(sockfd, (sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("Error in bind!");
        return -1;
    }

    socklen_t length = sizeof(addr);
    if (getsockname(sockfd, (sockaddr *)&addr, &length) == -1)
    {
        perror("Error getting port of socket");
        return -1;
    }
    port = ntohs(addr.sin_port);

    std::cout << "server listening on port: " << port << std::endl;

    listen(sockfd, 5);

    while (true)
    {
        int connectionfd = accept(sockfd, 0, 0);
        if (connectionfd == -1)
        {
            perror("Error accepting connection");
            return -1;
        }
        thread(server_append, connectionfd).detach();
    }
}

void append(char c, std::list<std::string> &list)
{
    for (std::string &s : list)
    {
        s.push_back(c);
    }
}

void server_append(int sock)
{
    // Remember: recv(socket_fd, var_receiving_into, sizeof_var, MSG_WAITALL)
    // Use your network protocol to decode the character to append and the list to append it to
    // Do the append
    // Send the new list back
    // Close the socket!
    char c;
    recv(sock, &c, sizeof(c), MSG_WAITALL);
    std::list<std::string> l = recvList(sock);
    append(c, l);
    sendList(sock, l);
    close(sock);
}
