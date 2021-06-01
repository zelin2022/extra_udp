/*
* Filename: extra_udp.cpp
* Author: Zelin Liu
* Date: 2021/05/24
* Description:
* Instruction:
* Copyright (c). All rights reserved.
*/

#include "extra_udp.hpp"


#include <unistd.h>
#include <string.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
#include <netdb.h>
#include <system_error>

Extra_UDP::Extra_UDP(Node &mynode){
  this->init_sock(mynode);
  this->meta_buffer = (char*)malloc(sizeof(char)*1);
}

Extra_UDP::~Extra_UDP(){
  free(this->meta_buffer);
  close(this->sock);
}

void Extra_UDP::init_sock(Node &mynode){
  int sockfd;
  int rv;
  struct addrinfo hints, *my_info;
  memset(&hints, 0, sizeof hints);
  if (mynode.is_ipv6) {
    hints.ai_family = AF_INET6;
  }
  else{
    hints.ai_family = AF_INET;
  }

  hints.ai_socktype = SOCK_DGRAM;

  if ((rv = getaddrinfo(mynode.host.c_str(), mynode.port_string().c_str(), &hints, &my_info)) != 0) {
    throw std::system_error(errno, std::generic_category(), std::string("getaddrinfo() failed") + gai_strerror(rv));
  }
  auto p = my_info;
  for(; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("listener: socket");
      continue;
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("listener: bind");
      continue;
    }
    break;
  }
  freeaddrinfo(my_info);
  if (p == NULL) {
    throw std::system_error(errno, std::generic_category(), "failed to create/bind socket");
  }
  this->sock = sockfd;
}
