/*
* Filename: extra_udp.cpp
* Author: Zelin Liu
* Date: 2021/05/24
* Description:
* Instruction:
* Copyright (c). All rights reserved.
*/


#include "extra_udp.hpp"

#include <netinet/in.h>
ssize_t Extra_UDP::send(Node *dest, std::vector<unsigned char> *msg){
  if (msg->size() == 0){
    return 0;
  }
  if (dest->is_ipv6)
  {//ipv6
    struct sockaddr_in6 ipv6_addr;
    ipv6_addr.sin6_family = AF_INET6;
    ipv6_addr.sin6_port = dest->port;
    struct in6_addr ipv6_ip;
    std::copy(dest->host.begin(), dest->host.end(), ipv6_ip.s6_addr); // seems we have to copy
    ipv6_addr.sin6_addr = ipv6_ip;
    return ::sendto(this->sock, msg->data(), msg->size(), 0, (struct sockaddr *)&ipv6_addr, (socklen_t)sizeof(ipv6_addr));
  }
  else
  { //ipv4
    struct sockaddr_in ipv4_addr;
    ipv4_addr.sin_family = AF_INET;
    ipv4_addr.sin_port = dest->port;
    struct in_addr ipv4_ip;
    ipv4_ip.s_addr = (unsigned int)((unsigned char)(dest->host[0]) << 24 |
             (unsigned char)(dest->host[1]) << 16 |
             (unsigned char)(dest->host[2]) << 8 |
             (unsigned char)(dest->host[3]));
    return ::sendto(this->sock, msg->data(), msg->size(), 0, (struct sockaddr*)&ipv4_addr, (socklen_t)sizeof(ipv4_addr));
  }
  return -1;
}
