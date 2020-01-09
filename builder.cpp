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

int p(const OperationType &t) {
  switch (t) {
  case OperationType::add:
  case OperationType::sub:
    return 1;
  case OperationType::mul:
  case OperationType::div:
    return 2;
  }
}

bool priority(const OperationType &newOp, const OperationType *oldOp) {
  if (oldOp == nullptr) {
    return false;
  }
  return p(newOp) > p(*oldOp);
}

string ExpressionBuilder::build() const {
  deque<string> items;
  items.push_back(to_string(this->source));
  const OperationType *prev = nullptr;
  for (const auto &operation : this->operations) {
    if (priority(operation.type, prev)) {
      items.push_front("(");
      items.push_back(")");
    }
    items.push_back(as_string(operation.type));
    items.push_back(to_string(operation.value));
    prev = &(operation.type);
  }
  return join(items.begin(), items.end());
}