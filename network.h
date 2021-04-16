#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <list>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>

/*
 * PROTOCOL:
 *
 * std::string:
 * Header [string bytes]
 * 
 * Header:
 * how long the following thing is
 * uint64_t
 * 
 * 
 * std::list<std::string>:
 * Header [list of strings following above format]
 * 
 * Header:
 * uint64_t # of strings
 */

/*
 * Need to do four things:
 * 1) Need to definine a network protocol: How to represent a std::list<std::string> in send() and recv() calls.
 *    For fun, allow the std::strings to contain null characters (i.e. they were constructed from a std::string(char_ptr, size) call)
 * 2) Use this to write sendList and recvList.
 * 3) Finish the client and server stub functions that use sendList and recvList
 * 4) Profit.
 */

// Sends any information necessary to reconstruct the list.
void sendList(int sock, std::list<std::string> &l);

// Receives information describing a list and returns a reconstructed list.
std::list<std::string> recvList(int sock);

#endif
