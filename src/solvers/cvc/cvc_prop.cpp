/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/


#include <cassert>
#include <set>


#include "cvc_prop.h"

explicit cvc_propt::cvc_propt(std::ostream &_out):out(_out)
{
  _no_variables=0;
}

cvc_propt::~cvc_propt()
{
}

void cvc_propt::land(literalt a, literalt b, literalt o)
{
  out << "%% land\n";
  out << "ASSERT (" << cvc_literal(a) << " AND "
      << cvc_literal(b) << ") <=> " << cvc_literal(o)
      << ";\n\n";
}

void cvc_propt::lor(literalt a, literalt b, literalt o)
{
  out << "%% lor\n";
  out << "ASSERT (" << cvc_literal(a) << " OR "
      << cvc_literal(b) << ") <=> " << cvc_literal(o)
      << ";\n\n";
}

void cvc_propt::lxor(literalt a, literalt b, literalt o)
{
  out << "%% lxor\n";
  out << "ASSERT (" << cvc_literal(a) << " XOR "
      << cvc_literal(b) << ") <=> " << cvc_literal(o)
      << ";\n\n";
}

void cvc_propt::lnand(literalt a, literalt b, literalt o)
{
  out << "%% lnand\n";
  out << "ASSERT (NOT (" << cvc_literal(a) << " AND "
      << cvc_literal(b) << ")) <=> " << cvc_literal(o)
      << ";\n\n";
}

void cvc_propt::lnor(literalt a, literalt b, literalt o)
{
  out << "%% lnor\n";
  out << "ASSERT (NOT (" << cvc_literal(a) << " OR "
      << cvc_literal(b) << ")) <=> " << cvc_literal(o)
      << ";\n\n";
}

void cvc_propt::lequal(literalt a, literalt b, literalt o)
{
  out << "%% lequal\n";
  out << "ASSERT (" << cvc_literal(a) << " <=> "
      << cvc_literal(b) << ") <=> " << cvc_literal(o)
      << ";\n\n";
}

void cvc_propt::limplies(literalt a, literalt b, literalt o)
{
  out << "%% limplies\n";
  out << "ASSERT (" << cvc_literal(a) << " => "
      << cvc_literal(b) << ") <=> " << cvc_literal(o)
      << ";\n\n";
}

literalt cvc_propt::land(const bvt &bv)
{
  out << "%% land\n";

  literalt literal=def_cvc_literal();

  forall_literals(it, bv)
  {
    if(it!=bv.begin())
      out << " AND ";
    out << cvc_literal(*it);
  }

  out << ";\n\n";

  return literal;
}

literalt cvc_propt::lor(const bvt &bv)
{
  out << "%% lor\n";

  literalt literal=def_cvc_literal();

  forall_literals(it, bv)
  {
    if(it!=bv.begin())
      out << " OR ";
    out << cvc_literal(*it);
  }

  out << ";\n\n";

  return literal;
}

literalt cvc_propt::lxor(const bvt &bv)
{
  if(bv.empty())
    return const_literal(false);
  if(bv.size()==1)
    return bv[0];
  if(bv.size()==2)
    return lxor(bv[0], bv[1]);

  literalt literal=const_literal(false);

  forall_literals(it, bv)
    literal=lxor(*it, literal);

  return literal;
}

literalt cvc_propt::land(literalt a, literalt b)
{
  if(a==const_literal(true))
    return b;
  if(b==const_literal(true))
    return a;
  if(a==const_literal(false))
    return const_literal(false);
  if(b==const_literal(false))
    return const_literal(false);
  if(a==b)
    return a;

  out << "%% land\n";

  literalt o=def_cvc_literal();

  out << cvc_literal(a) << " AND " << cvc_literal(b) << ";\n\n";

  return o;
}

literalt cvc_propt::lor(literalt a, literalt b)
{
  if(a==const_literal(false))
    return b;
  if(b==const_literal(false))
    return a;
  if(a==const_literal(true))
    return const_literal(true);
  if(b==const_literal(true))
    return const_literal(true);
  if(a==b)
    return a;

  out << "%% lor\n";

  literalt o=def_cvc_literal();

  out << cvc_literal(a) << " OR " << cvc_literal(b) << ";\n\n";

  return o;
}

literalt cvc_propt::lxor(literalt a, literalt b)
{
  if(a==const_literal(false))
    return b;
  if(b==const_literal(false))
    return a;
  if(a==const_literal(true))
    return !b;
  if(b==const_literal(true))
    return !a;

  out << "%% lxor\n";

  literalt o=def_cvc_literal();

  out << cvc_literal(a) << " XOR " << cvc_literal(b) << ";\n\n";

  return o;
}

literalt cvc_propt::lnand(literalt a, literalt b)
{
  return !land(a, b);
}

literalt cvc_propt::lnor(literalt a, literalt b)
{
  return !lor(a, b);
}

literalt cvc_propt::lequal(literalt a, literalt b)
{
  return !lxor(a, b);
}

literalt cvc_propt::limplies(literalt a, literalt b)
{
  return lor(!a, b);
}

literalt cvc_propt::lselect(literalt a, literalt b, literalt c)
{
  if(a==const_literal(true))
    return b;
  if(a==const_literal(false))
    return c;
  if(b==c)
    return b;

  out << "%% lselect\n";

  literalt o=def_cvc_literal();

  out << "IF " << cvc_literal(a) << " THEN "
      << cvc_literal(b) << " ELSE "
      << cvc_literal(c) << " ENDIF;\n\n";

  return o;
}

literalt cvc_propt::new_variable()
{
  out << "l" << _no_variables << ": BOOLEAN;\n";
  literalt l;
  l.set(_no_variables, false);
  _no_variables++;
  return l;
}

literalt cvc_propt::def_cvc_literal()
{
  out << "l" << _no_variables << ": BOOLEAN = ";
  literalt l;
  l.set(_no_variables, false);
  _no_variables++;
  return l;
}

void cvc_propt::lcnf(const bvt &bv)
{
  if(bv.empty())
    return;
  bvt new_bv;

  std::set<literalt> s;

  new_bv.reserve(bv.size());

  for(bvt::const_iterator it=bv.begin(); it!=bv.end(); it++)
  {
    if(s.insert(*it).second)
      new_bv.push_back(*it);

    if(s.find(!*it)!=s.end())
      return; // clause satisfied

    assert(it->var_no()<_no_variables);
  }

  assert(!new_bv.empty());

  out << "%% lcnf\n";
  out << "ASSERT ";

  for(bvt::const_iterator it=new_bv.begin(); it!=new_bv.end(); it++)
  {
    if(it!=new_bv.begin())
      out << " OR ";
    out << cvc_literal(*it);
  }

  out << ";\n\n";
}

std::string cvc_propt::cvc_literal(literalt l)
{
  if(l==const_literal(false))
    return "FALSE";
  else if(l==const_literal(true))
    return "TRUE";

  if(l.sign())
    return "(NOT l"+std::to_string(l.var_no())+")";

  return "l"+std::to_string(l.var_no());
}

propt::resultt cvc_propt::prop_solve()
{
  out << "QUERY FALSE;\n";
  return P_ERROR;
}
