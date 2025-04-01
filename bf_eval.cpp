#include <assert.h>
#include <iostream>

#include "bf_ast.h"

using namespace std;

size_t g_mem_arr_size;
size_t g_ptr;

void
seq_node_t::eval(byte_mem_t* mem_arr) const
{
  size_t n = this->m_insts.size();
  for (size_t i = 0;i < n;i++) {
    auto const& node = this->m_insts.at(i);
    switch (node->get_node_kind()) {
      case node_kind::SEQ: {
        cout << "ERROR: Sequence inside a sequence node\n";
        assert(false);
        break;
      }
      case node_kind::LSHIFT: {
        auto lshift_node = dynamic_cast<lshift_node_t*>(node);
        assert(lshift_node);
        lshift_node->eval(mem_arr);
        break;
      }
      case node_kind::RSHIFT: {
        auto rshift_node = dynamic_cast<rshift_node_t*>(node);
        assert(rshift_node);
        rshift_node->eval(mem_arr);
        break;
      }
      case node_kind::LOOP: {
        auto loop_node = dynamic_cast<loop_node_t*>(node);
        assert(loop_node);
        loop_node->eval(mem_arr);
        break;
      }
      case node_kind::INC: {
        auto inc_node = dynamic_cast<inc_node_t*>(node);
        assert(inc_node);
        inc_node->eval(mem_arr);
        break;
      }
      case node_kind::DEC: {
        auto dec_node = dynamic_cast<dec_node_t*>(node);
        assert(dec_node);
        dec_node->eval(mem_arr);
        break;
      }
      case node_kind::IN: {
        auto in_node = dynamic_cast<in_node_t*>(node);
        assert(in_node);
        in_node->eval(mem_arr);
        break;
      }
      case node_kind::OUT: {
        auto out_node = dynamic_cast<out_node_t*>(node);
        assert(out_node);
        out_node->eval(mem_arr);
        break;
      }
    }
  }
}

void
lshift_node_t::eval(byte_mem_t* mem_arr) const
{
  g_ptr = (g_ptr + g_mem_arr_size - 1) % g_mem_arr_size;
}

void
rshift_node_t::eval(byte_mem_t* mem_arr) const
{
  g_ptr = (g_ptr + 1) % g_mem_arr_size;
}

void
loop_node_t::eval(byte_mem_t* mem_arr) const
{
  while (mem_arr[g_ptr] != 0) {
    this->m_seq_node->eval(mem_arr);
  }
}

void
inc_node_t::eval(byte_mem_t* mem_arr) const
{
  mem_arr[g_ptr]++;
}

void
dec_node_t::eval(byte_mem_t* mem_arr) const
{
  mem_arr[g_ptr]--;
}

void
in_node_t::eval(byte_mem_t* mem_arr) const
{
  byte_mem_t b;
  cin >> b;
  mem_arr[g_ptr] = b;
}

void
out_node_t::eval(byte_mem_t* mem_arr) const
{
  cout << mem_arr[g_ptr];
}

void
root_node_t::eval(byte_mem_t* mem_arr) const
{
  g_ptr = 0;
  g_mem_arr_size = this->m_mem_arr_size;
  this->seq_node_t::eval(mem_arr);
}

