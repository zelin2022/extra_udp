/*
* Filename: extra_udp.cpp
* Author: Zelin Liu
* Date: 2021/05/27
* Description:
* Instruction:
* Copyright (c). All rights reserved.
*/
#include "extra_udp.hpp"
ssize_t recv(Node *src, std::vector<unsigned char> *msg){
  src = new Node();
  msg = new std::vector<unsigned char>();
  ssize_t received_size = ::recvfrom(this->sock, msg->data(), this->CONFIG_STANDARD_UDP_PACKET_MAX_SIZE, 0, (struct sockaddr*)&addr, &addr_len);

  return -1;
}
