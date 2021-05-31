/*
* Filename: extra_udp.hpp
* Author: Zelin Liu
* Date: 2021/05/24
* Description:
* Instruction:
* Copyright (c). All rights reserved.
*/


#ifndef _EXTRA_UDP_EXTRA_UDP_HPP_
#define _EXTRA_UDP_EXTRA_UDP_HPP_
#include "node.hpp"
#include <vector>
class Extra_UDP{
public:
  Extra_UDP(Node & mynode);
  ssize_t send(Node *dest, std::vector<unsigned char> *msg);
  ssize_t recv(Node *src, std::vector<unsigned char> *msg);
private:
  int sock;
};
#endif
