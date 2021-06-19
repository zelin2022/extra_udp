#include "node.hpp"
#include "extra_udp.hpp"
#include <chrono>
#include <thread>
#include <cstring>
#include <vector>

void print_consts(){
  printf("checking constants...\n");
  printf("M_packet_original_size: %d\n", Extra_UDP::M_packet_original_size);
  printf("M_packet_meta_size: %d\n", Extra_UDP::M_packet_meta_size);
  printf("M_packet_data_size: %d\n", Extra_UDP::M_packet_data_size);
}

int main(){
  print_consts();
  printf("starting server 1\n");
  Node my_addr;
  my_addr.host = std::string("127.0.0.1");
  my_addr.port = 22000;
  my_addr.is_ipv6 = false;
  Extra_UDP my_pc(my_addr);
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2000ms);
  //send(Node *dest, std::vector<unsigned char> *msg);
  Node server2_addr;
  server2_addr.host = std::string("127.0.0.1");
  server2_addr.port = 22001;
  server2_addr.is_ipv6 = false;
  std::vector<std::string> test_cases {
    std::string("There is nothing,"),
    std::string("To be scared of."),
    std::string("Because there is nothing,"),
    std::string("that you would not lose eventually."),
    std::string("the end."),
  };


  // bench_mark
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;

  auto t1 = high_resolution_clock::now();
  ///////////////


  for (auto &i : test_cases){
    int a = my_pc.send(&server2_addr, (void *)i.c_str(), i.size());
    printf("sent %d\n", a);
  }

  std::vector<std::string> received_cases;

  while(true){
    Node* recv_info = nullptr;
    char* buffer = nullptr;
    ssize_t count = my_pc.recv(recv_info, true, buffer);
    if (count > 0){
      printf("sv1 received: %s\n", buffer);
      received_cases.push_back(std::string(buffer, count));
      if(!strcmp("the end.", buffer)){
        break;
      }
    }
    delete (recv_info);
    free(buffer);
  }

  ////////////////////
  auto t2 = high_resolution_clock::now();

  /* Getting number of milliseconds as an integer. */
  auto ms_int = duration_cast<milliseconds>(t2 - t1);

  /* Getting number of milliseconds as a double. */
  duration<double, std::milli> ms_double = t2 - t1;

  printf("Message_return: %ld ms\n", ms_int.count());
  printf("Message_return: %f ms\n", ms_double.count());
  ///////////////////

  for (int i = 0; i < test_cases.size(); ++i){
    bool failed = false;
    if (received_cases[i] != test_cases[i]){
      printf("mismatched test case and return case:\ntest:%s\nrecv:%s\n", received_cases[i].c_str(), test_cases[i].c_str());
      failed = true;
    }
    if(failed){
      return 1;
    }
  }

  printf("Server 1 close \n");
  return 0;
}
