#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation {

 private:

  string name;
  Scheme scheme;
  set<Tuple> tuples;

  static bool joinable (const Scheme& leftScheme, const Scheme& rightScheme,
		       const Tuple& leftTuple, const Tuple& rightTuple);

  Tuple joinTuples(const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple);
  Scheme joinSchemes(const Scheme& leftScheme, const Scheme& rightScheme);

 public:

  Relation(const string& name, const Scheme& scheme)
    : name(name), scheme(scheme) { }

    Relation(const string& name, const Scheme& scheme, set<Tuple> tuples);

  void addTuple(const Tuple& tuple);

  string toString() const;

  Relation select(int index, const string& value) const;
  Relation select(vector<int> positions) const;

  Relation project(vector<int> columns) const;
  Relation project(vector<string> columns) const;

  Relation rename(vector<string> newNames) const;

  Relation join(const Relation& r);
  Relation Union(const Relation& r);

  Relation diff(const Relation& r);

  string getName() const;
  vector<string> getSchemeNames() const;

  void setName(string name);
  int size() const;
};