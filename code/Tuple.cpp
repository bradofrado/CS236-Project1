#include <vector>
#include <string>
#include "Tuple.h"
#include <sstream>

using namespace std;

string Tuple::toString(const Scheme& scheme) const
{
    stringstream out;
    for (unsigned i = 0; i < size(); i++) {
      if (i > 0)
	out << ", ";
      const string& name = scheme.at(i);
      const string& value = at(i);
      out << name << "=" << value;
    }
    return out.str();
}