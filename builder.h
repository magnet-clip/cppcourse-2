#pragma once

#include <string>
#include <vector>

enum class OperationType { add, sub, mul, div };

struct Operation {
  OperationType type;
  int value;
};

class ExpressionBuilder {
private:
  int source;
  std::vector<Operation> operations;

public:
  ExpressionBuilder(int s, const std::vector<Operation> &ops)
      : source(s), operations(ops) {}
  ExpressionBuilder() : source(0), operations({}) {}
  void setSource(int source);
  void setOperations(std::vector<Operation> operations);
  void addOperation(const Operation &op);
  std::string build() const;
};
