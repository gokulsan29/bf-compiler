#pragma once
#include <string>
#include <vector>

using namespace std;

class node_t;
using inst_seq_t = vector<node_t*>;
using byte_mem_t = unsigned char;

enum class node_kind
{
  SEQ,
  LSHIFT,
  RSHIFT,
  LOOP,
  INC,
  DEC,
  IN,
  OUT
};

class node_t
{
public:
  node_t(node_kind nk) : m_nk(nk) {}
  string to_string(string prefix = "") const { return prefix; }
  void eval(byte_mem_t* mem_arr) const {}
  node_kind const get_node_kind() { return m_nk; }

  virtual ~node_t() {}
private:
  node_kind const m_nk;
};

class seq_node_t : public node_t
{
public:
  seq_node_t(inst_seq_t insts) : node_t(node_kind::SEQ), m_insts(insts) {}
  string to_string(string prefix = "") const;
  void eval(byte_mem_t* mem_arr) const;
private:
  inst_seq_t m_insts;
};

class lshift_node_t : public node_t
{
public:
  lshift_node_t() : node_t(node_kind::LSHIFT) {}
  string to_string(string prefix = "") const;
  void eval(byte_mem_t* mem_arr) const;
};

class rshift_node_t : public node_t
{
public:
  rshift_node_t() : node_t(node_kind::RSHIFT) {}
  string to_string(string prefix = "") const;
  void eval(byte_mem_t* mem_arr) const;
};

class loop_node_t : public node_t
{
public:
  loop_node_t(seq_node_t* seq_node) : node_t(node_kind::LOOP), m_seq_node(seq_node) {}
  string to_string(string prefix = "") const;
  void eval(byte_mem_t* mem_arr) const;
private:
  seq_node_t* m_seq_node;
};

class inc_node_t : public node_t
{
public:
  inc_node_t() : node_t(node_kind::INC) {}
  string to_string(string prefix = "") const;
  void eval(byte_mem_t* mem_arr) const;
};

class dec_node_t : public node_t
{
public:
  dec_node_t() : node_t(node_kind::DEC) {}
  string to_string(string prefix = "") const;
  void eval(byte_mem_t* mem_arr) const;
};

class in_node_t : public node_t
{
public:
  in_node_t() : node_t(node_kind::IN) {}
  string to_string(string prefix = "") const;
  void eval(byte_mem_t* mem_arr) const;
};

class out_node_t : public node_t
{
public:
  out_node_t() : node_t(node_kind::OUT) {}
  string to_string(string prefix = "") const;
  void eval(byte_mem_t* mem_arr) const;
};

class root_node_t : public seq_node_t
{
public:
  root_node_t(inst_seq_t insts) : seq_node_t(insts) {}
  string to_string(string prefix = "") const;
  void eval(byte_mem_t* mem_arr) const;
  static root_node_t* parse_bf(istream& in);
  void set_mem_arr_size(size_t mem_arr_size) { m_mem_arr_size = mem_arr_size; }
private:
  size_t m_mem_arr_size;
};

