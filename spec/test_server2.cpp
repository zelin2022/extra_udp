#include "node.hpp"
#include "extra_udp.hpp"
#include <chrono>
#include <thread>
#include <cstring>
#include <iostream>
int main(){
  printf("starting server 2\n");
  Node my_addr;
  my_addr.host = std::string("127.0.0.1");
  my_addr.port = 22001;
  my_addr.is_ipv6 = false;
  Extra_UDP my_pc(my_addr);
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1000ms);
  //ssize_t recv(Node *src, bool want_sender_info, void* store_location);
  while(true){
    Node* recv_info = nullptr;
    char* buffer = nullptr;
    ssize_t count = my_pc.recv(recv_info, true, buffer);
    if (count > 0){
      printf("sv2 received from %s:%d: %s\n", recv_info->host.c_str(), recv_info->port, buffer);
      int a = my_pc.send(recv_info, buffer, count);
      if(!strcmp("the end.", buffer)){
        break;
      }
    }

    delete (recv_info);
    free(buffer);
  }
  printf("Server 2 close \n");
}
