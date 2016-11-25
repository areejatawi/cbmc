/*******************************************************************

 Module: C Test Case Generator

 Author: Thomas Kiley, thomas@diffblue.com

\*******************************************************************/

#ifndef CPROVER_FUNCTION_RETURN_BUILDER_H
#define CPROVER_FUNCTION_RETURN_BUILDER_H

#include <goto-programs/interpreter_class.h>

class function_return_buildert
{
public:
  function_return_buildert(const interpretert::input_varst &all_inputs,
    const irep_idt &function_id,
    class expr2cleanct &e2c_converter);

  bool get_function_has_return() const;
  std::string get_return_declaration() const;
  std::string get_return_variable_name() const;
  std::vector<std::string> get_assertion_lines();

private:
  void set_return_variable_name(const irep_idt &function_id);

  void add_assertions_for_expression(const exprt &correct_expression,
    std::string ret_value_var);

  void add_assertions_for_struct_expression(const exprt &correct_expression,
    std::string ret_value_var);

  void add_assertions_for_simple_expression(const exprt &correct_expression,
    std::string return_value_var);

  class expr2cleanct &e2c;
  bool has_return;
  interpretert::input_entryt return_entry;
  std::string return_var_name;

  std::vector<std::string> assertions;
};

#endif // CPROVER_FUNCTION_RETURN_BUILDERT_H
