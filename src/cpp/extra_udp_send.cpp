/*
* Filename: extra_udp.cpp
* Author: Zelin Liu
* Date: 2021/05/24
* Description:
* Instruction:
* Copyright (c). All rights reserved.
*/


#include "extra_udp.hpp"
#include <arpa/inet.h>
#include <netinet/in.h>
ssize_t Extra_UDP::send(Node *dest, void *msg, int32_t size){
  if (size <= 0){
    return 0;
  }
  if (dest->is_ipv6)
  {//ipv6
    struct sockaddr_in6 ipv6_addr;
    ipv6_addr.sin6_family = AF_INET6;
    ipv6_addr.sin6_port = htons(dest->port);
    ::inet_pton(AF_INET6, dest->host.c_str(), &(ipv6_addr.sin6_addr));
    return ::sendto(this->sock, msg, size, 0, (struct sockaddr *)&ipv6_addr, sizeof(ipv6_addr));
  }
  else
  { //ipv4
    struct sockaddr_in ipv4_addr;
    ipv4_addr.sin_family = AF_INET;
    ipv4_addr.sin_port = htons(dest->port);
    ::inet_pton(AF_INET, dest->host.c_str(), &(ipv4_addr.sin_addr));
    return ::sendto(this->sock, msg, size, 0, (struct sockaddr*)&ipv4_addr, sizeof(ipv4_addr));
  }
  return -1;
}
