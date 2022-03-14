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

 public:

  Relation(const string& name, const Scheme& scheme)
    : name(name), scheme(scheme) { }

    Relation(const Relation& relation);

  void addTuple(const Tuple& tuple);

  string toString() const;

  static bool joinable (const Scheme& leftScheme, const Scheme& rightScheme,
		       const Tuple& leftTuple, const Tuple& rightTuple);

  Relation select(int index, const string& value) const;
  Relation select(vector<int> positions) const;

  Relation project(vector<int> columns) const;
  Relation rename(vector<string> newNames) const;

  Relation join(const Relation& r);

  string getName() const;
  int size() const;
};