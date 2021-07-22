/*
* Filename: node.cpp
* Author: Zelin Liu
* Date: 2021/05/24
* Description:
* Instruction:
* Copyright (c). All rights reserved.
*/
#include "extra_udp.hpp"
std::string Node::port_string(){
  return std::to_string(this->port);
}

std::string Node::get_str(){
  return this->host + ":" + this->port_string();
}

std::size_t Node::get_hash(){
  return std::hash<std::string>{}(this->get_str());
}
