#include <assert.h>
#include <iostream>
#include <string>

#include "bf_ast.h"

using namespace std;

string
seq_node_t::to_string(string prefix) const
{
  string ret = "";
  size_t n = this->m_insts.size();
  for (size_t i = 0;i < n;i++) {
    auto const& node = this->m_insts.at(i);
    string new_prefix_before = prefix + (i == n - 1 ? "`-" : "|-");
    string new_prefix_after = prefix + (i == n - 1 ? "  " : "| ");
    switch (node->get_node_kind()) {
      case node_kind::SEQ: {
        cout << "ERROR: Sequence inside a sequence node\n";
        assert(false);
        break;
      }
      case node_kind::LSHIFT: {
        auto lshift_node = dynamic_cast<lshift_node_t*>(node);
        assert(lshift_node);
        ret += new_prefix_before + lshift_node->to_string(new_prefix_after);
        break;
      }
      case node_kind::RSHIFT: {
        auto rshift_node = dynamic_cast<rshift_node_t*>(node);
        assert(rshift_node);
        ret += new_prefix_before + rshift_node->to_string(new_prefix_after);
        break;
      }
      case node_kind::LOOP: {
        auto loop_node = dynamic_cast<loop_node_t*>(node);
        assert(loop_node);
        ret += new_prefix_before + loop_node->to_string(new_prefix_after);
        break;
      }
      case node_kind::INC: {
        auto inc_node = dynamic_cast<inc_node_t*>(node);
        assert(inc_node);
        ret += new_prefix_before + inc_node->to_string(new_prefix_after);
        break;
      }
      case node_kind::DEC: {
        auto dec_node = dynamic_cast<dec_node_t*>(node);
        assert(dec_node);
        ret += new_prefix_before + dec_node->to_string(new_prefix_before);
        break;
      }
      case node_kind::IN: {
        auto in_node = dynamic_cast<in_node_t*>(node);
        assert(in_node);
        ret += new_prefix_before + in_node->to_string(new_prefix_after);
        break;
      }
      case node_kind::OUT: {
        auto out_node = dynamic_cast<out_node_t*>(node);
        assert(out_node);
        ret += new_prefix_before + out_node->to_string(new_prefix_after);
        break;
      }
    }
  }
  return ret;
}

string
lshift_node_t::to_string(string prefix) const
{
  string ret = "<\n";
  return ret;
}

string
rshift_node_t::to_string(string prefix) const
{
  string ret = ">\n";
  return ret;
}

string
loop_node_t::to_string(string prefix) const
{
  string ret = "loop\n";
  ret += this->m_seq_node->to_string(prefix + "  ");
  return ret;
}

string
inc_node_t::to_string(string prefix) const
{
  string ret = "+\n";
  return ret;
}

string
dec_node_t::to_string(string prefix) const
{
  string ret = "-\n";
  return ret;
}

string
in_node_t::to_string(string prefix) const
{
  string ret = ",\n";
  return ret;
}

string
out_node_t::to_string(string prefix) const
{
  string ret = ".\n";
  return ret;
}

string
root_node_t::to_string(string prefix) const
{
  string ret = "root\n";
  ret += this->seq_node_t::to_string(prefix) + "\n";
  return ret;
}

