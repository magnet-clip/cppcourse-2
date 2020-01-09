#include "builder.h"
#include <deque>
#include <string>

using namespace std;

template <typename RandomIt>
string join(RandomIt range_begin, RandomIt range_end) {
  string res;
  for (auto it = range_begin; it != range_end; it++) {
    res += *it;
  }
  return res;
}

string as_string(const OperationType &type) {
  switch (type) {
  case OperationType::add:
    return " + ";
  case OperationType::sub:
    return " - ";
  case OperationType::mul:
    return " * ";
  case OperationType::div:
    return " / ";
  }
}

void ExpressionBuilder::setSource(int source) { this->source = source; }

void ExpressionBuilder::setOperations(vector<Operation> operations) {
  this->operations = operations;
}

void ExpressionBuilder::addOperation(const Operation &op) {
  this->operations.push_back(op);
}

string ExpressionBuilder::build() const {
  deque<string> items;
  items.push_back(to_string(this->source));
  for (const auto &operation : this->operations) {
    items.push_front("(");
    items.push_back(")");
    items.push_back(as_string(operation.type));
    items.push_back(to_string(operation.value));
  }
  return join(items.begin(), items.end());
}