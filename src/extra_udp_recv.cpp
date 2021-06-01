/*
* Filename: extra_udp.cpp
* Author: Zelin Liu
* Date: 2021/05/27
* Description:
* Instruction:
* Copyright (c). All rights reserved.
*/
#include "extra_udp.hpp"
#include <netinet/in.h>
ssize_t Extra_UDP::recv(Node *src, void* store_location){
  //
  // char * MetaData = malloc(2 * sizeof(unsigned char));
  // struct sockaddr_storage addr;
  // socklen_t addr_len = sizeof(addr);
  // ssize_t received_size = ::recvfrom(this->sock, size_bytes, 2, MSG_PEEK, (struct sockaddr*)&addr, &addr_len);
  //
  // return -1;
}
