#include <iostream>
#include <stack>

#include "bf_ast.h"

using namespace std;

root_node_t*
root_node_t::parse_bf(istream& in)
{
  stack<inst_seq_t> inst_st;
  inst_st.push({});

  char c;
  while (in.get(c)) {
    switch (c) {
      case '<': { inst_st.top().push_back(new lshift_node_t()); break; }
      case '>': { inst_st.top().push_back(new rshift_node_t()); break; }
      case '+': { inst_st.top().push_back(new inc_node_t()); break; }
      case '-': { inst_st.top().push_back(new dec_node_t()); break; }
      case '.': { inst_st.top().push_back(new out_node_t()); break; }
      case ',': { inst_st.top().push_back(new in_node_t()); break; }
      case '[': { inst_st.push({}); break; }
      case ']': {
        if (inst_st.size() <= 1) {
          cout << "Unmatched \"]\"\n";
          return nullptr;
        }
        inst_seq_t insts = inst_st.top();
        seq_node_t* seq_node = new seq_node_t(insts);
        loop_node_t* loop_node = new loop_node_t(seq_node);
        inst_st.pop();
        inst_st.top().push_back(loop_node);
        break;
      }
      default: { break; }
    }
  }

  if (inst_st.size() > 1) {
    cout << "Unmatched \"[ \"";
    return nullptr;
  }
  return new root_node_t(inst_st.top());
}

