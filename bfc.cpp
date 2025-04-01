#include <iostream>
#include <fstream>

#include "bf_ast.h"
using namespace std;

int main(int argc, char** argv)
{
  if(argc < 2) {
    cout << "Usage: bfc <filename>\n";
    exit(1);
  }
  ifstream in(argv[1]);
  if (!in) {
    cout << "Error in opening file\n";
    exit(1);
  }
  root_node_t* root = root_node_t::parse_bf(in);
  if (root == nullptr) {
    cout << "Error in parsing string\n";
    exit(1);
  }
  int mem_arr_size = 30000;
  byte_mem_t* mem_arr = new byte_mem_t[mem_arr_size];
  root->set_mem_arr_size(mem_arr_size);
  root->eval(mem_arr);
  return 0;
}
