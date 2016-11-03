/*******************************************************************

 Module: C Test Case Generator

 Author: Thomas Kiley, thomas@diffblue.com

\*******************************************************************/

#ifndef C_TEST_CASE_GENERATOR_H_
#define C_TEST_CASE_GENERATOR_H_

#include <functional>
#include <string>

#include <util/message.h>

// This is the full original function type that we're working towards
/*typedef std::function<
  std::string(const class symbol_tablet &, const irep_idt &,
              bool, const class inputst &,
              const class interpretert::list_input_varst&,
              const class interpretert::input_var_functionst&,
              const class interpretert::dynamic_typest&,
              const std::string &,
              const class interpretert::side_effects_differencet &,
              const class exprt &,
              bool,
              bool,
              bool,
              const class optionst::value_listt&,
              const class optionst::value_listt&,
              const std::vector<std::string>&,
              const std::string&)> test_case_generatort;*/

typedef std::function<std::string(const class symbol_tablet &)> test_case_generatort;

class c_test_case_generatort : public messaget
{
public:
  c_test_case_generatort(message_handlert & _message_handler):
    messaget(_message_handler)
{
}

  /**
   * @brief
   *
   * @details
   *
   * @param options
   * @param st
   * @param gf
   * @param bmc
   */
  std::string generate_tests(const class optionst &options,
                      const class symbol_tablet &st,
                      const class goto_functionst &gf,
                      const class goto_tracet &trace,
                      const size_t test_idx,
                      const std::vector<std::string> &goals);

  /**
   * @brief Get the name for a specific function test
   *
   * @details
   *
   * @param st
   * @param gf
   * @param test_idx
   *
   * @return The name of the test
   */
  const std::string get_test_function_name(const class symbol_tablet &st,
                                           const class goto_functionst &gf,
                                           size_t test_idx);


private:
  std::string generate_tests_with_generator(const class optionst &options,
                                     const class symbol_tablet &st,
                                     const class goto_functionst &gf,
                                     const class goto_tracet &trace,
                                     const test_case_generatort generator,
                                     size_t test_idx,
                                     std::vector<std::string> goals_reached);

  const irep_idt get_entry_function_id(const class goto_functionst& gf);

  const irep_idt get_calling_function_name(
      const class code_function_callt & function_call_instruction);

  std::string sanitise_function_name(const std::string called_function_name);

};

#endif
