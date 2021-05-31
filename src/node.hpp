/*
* Filename: node.hpp
* Author: Zelin Liu
* Date: 2021/05/24
* Description:
* Instruction:
* Copyright (c). All rights reserved.
*/

#ifndef _EXTRA_UDP_NODE_HPP_
#define _EXTRA_UDP_NODE_HPP_
#include <string>
struct Node{
public:
  std::string host;
  uint16_t port;
  bool is_ipv6;
  std::string port_string();
};
#endif
