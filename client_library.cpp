#include "client_library.h"

void printList(std::list<std::string> &l)
{
    for (std::string s : l)
    {
        std::cout << s << std::endl;
    }
}

// RPC which returns a list with char c appended to each string in the
// input list.
std::list<std::string> client_append(int port, std::list<std::string> &l, char c)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("error in socket!");
        throw std::runtime_error("Couldn't make a socket");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    struct hostent *host = gethostbyname("localhost");
    memcpy(&(addr.sin_addr), host->h_addr, host->h_length);
    addr.sin_port = htons(port);

    if (connect(sockfd, (sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("error in connect!");
        throw std::runtime_error("error in connect!");
    }

    // CONNECTED TO SERVER.

    // (1) Send the char to append.
    send(sockfd, &c, sizeof(c), 0);

    // (2) Send the list.
    sendList(sockfd, l);

    // (3) Receive the list back from the server.
    std::list<std::string> mylist = recvList(sockfd);

    // (4) Close the socket.
    close(sockfd);

    return mylist;
}
