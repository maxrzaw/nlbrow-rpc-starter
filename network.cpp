#include "network.h"

/**
 * @brief Send a uint64_t to sock.
 * 
 * @param sock the socket to send to
 * @param val the value to send
 */
void send_uint64_t(int sock, uint64_t val)
{
    val = htonl(val);
    send(sock, &val, sizeof(val), 0);
}

/**
 * @brief Receive a uint64_t from sock.
 * 
 * @param sock the socket to receive from
 * @param val the value to send
 */
uint64_t recv_uint64_t(int sock)
{
    uint64_t val;
    recv(sock, &val, sizeof(val), MSG_WAITALL);
    val = ntohl(val);
    return val;
}

/**
 * @brief Send list l to socket sock
 * 
 * @param sock 
 * @param l 
 */
void sendList(int sock, std::list<std::string> &l)
{
    // 1. uint64_t for the size of the list
    // 2. For each std::string:
    //   a) uint64_t str.size()
    //   b) str.c_str()

    uint64_t list_length = l.size();
    send_uint64_t(sock, list_length);
    for (const auto &str : l)
    {
        send_uint64_t(sock, str.size());
        send(sock, str.c_str(), str.size(), 0);
    }
}

std::list<std::string> recvList(int sock)
{
    // 1. uint64_t for the size of the list (# of strings)
    // 2. For each std::string:
    //   a) uint64_t str.size() (# of char bytes)
    //   b) str.c_str()

    uint64_t num_strs;

    num_strs = recv_uint64_t(sock);
    std::list<std::string> list;
    for (uint64_t i = 0; i < num_strs; ++i)
    {
        uint64_t len = recv_uint64_t(sock);
        std::string val;
        val.resize(len);
        recv(sock, (void *)val.c_str(), val.size(), MSG_WAITALL);
        list.push_back(std::move(val));
    }

    return list;
}
