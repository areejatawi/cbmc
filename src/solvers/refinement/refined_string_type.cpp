/********************************************************************\

Module: Type for string expressions used by the string solver.
        These string expressions contain a field `length`, of type
        `index_type`, a field `content` of type `content_type`.
        This module also defines functions to recognise the C and java
        string types.

Author: Romain Brenguier, romain.brenguier@diffblue.com

\*******************************************************************/

/// \file
/// Type for string expressions used by the string solver. These string
///   expressions contain a field `length`, of type `index_type`, a field
///   `content` of type `content_type`. This module also defines functions to
///   recognise the C and java string types.

#include <util/cprover_prefix.h>

#include "refined_string_type.h"

refined_string_typet::refined_string_typet(
  const typet &index_type, const typet &char_type)
{
  infinity_exprt infinite_index(index_type);
  array_typet char_array(char_type, infinite_index);
  components().emplace_back("length", index_type);
  components().emplace_back("content", char_array);
}

/// \par parameters: a type
/// \return Boolean telling whether the type is that of C strings
bool refined_string_typet::is_c_string_type(const typet &type)
{
  return
    type.id()==ID_struct &&
    to_struct_type(type).get_tag()==CPROVER_PREFIX"string";
}

/// \par parameters: a type
/// \return Boolean telling whether the type is that of java string pointers
bool refined_string_typet::is_java_string_pointer_type(const typet &type)
{
  if(type.id()==ID_pointer)
  {
    const pointer_typet &pt=to_pointer_type(type);
    const typet &subtype=pt.subtype();
    return is_java_string_type(subtype);
  }
  return false;
}

/// \par parameters: a type
/// \return Boolean telling whether the type is that of java string
bool refined_string_typet::is_java_string_type(const typet &type)
{
  if(type.id()==ID_symbol)
  {
    irep_idt tag=to_symbol_type(type).get_identifier();
    return tag=="java::java.lang.String";
  }
  else if(type.id()==ID_struct)
  {
    irep_idt tag=to_struct_type(type).get_tag();
    return tag=="java.lang.String";
  }
  return false;
}

/// \par parameters: a type
/// \return Boolean telling whether the type is that of java string builder
bool refined_string_typet::is_java_string_builder_type(const typet &type)
{
  if(type.id()==ID_pointer)
  {
    const pointer_typet &pt=to_pointer_type(type);
    const typet &subtype=pt.subtype();
    if(subtype.id()==ID_struct)
    {
      irep_idt tag=to_struct_type(subtype).get_tag();
      return tag=="java.lang.StringBuilder";
    }
  }
  return false;
}

/// \par parameters: a type
/// \return Boolean telling whether the type is that of java char sequence
bool refined_string_typet::is_java_char_sequence_type(const typet &type)
{
  if(type.id()==ID_pointer)
  {
    const pointer_typet &pt=to_pointer_type(type);
    const typet &subtype=pt.subtype();
    if(subtype.id()==ID_struct)
    {
      const irep_idt &tag=to_struct_type(subtype).get_tag();
      return tag=="java.lang.CharSequence";
    }
  }
  return false;
}
