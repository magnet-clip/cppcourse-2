#pragma once

#include <string>
#include <vector>

enum class OperaionType { add, sub, mul, div };

struct Operation {
  OperaionType type;
  int value;
};

class ExpressionBuilder {
private:
  int source;
  std::vector<Operation> operations;

public:
  ExpressionBuilder(int s, const std::vector<Operation> &ops)
      : source(s), operations(ops) {}
  std::string build() const;
};
