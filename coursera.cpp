#include "builder.h"
#include <iostream>

using namespace std;

OperationType from_char(char type) {
  if (type == '+') {
    return OperationType::add;
  } else if (type == '-') {
    return OperationType::sub;
  } else if (type == '*') {
    return OperationType::mul;
  } else if (type == '/') {
    return OperationType::div;
  }
}

int main() {
  ExpressionBuilder builder;
  int source;
  cin >> source;
  builder.setSource(source);
  int count;
  cin >> count;
  for (auto i = 0; i < count; i++) {
    char op;
    int value;
    cin >> op >> value;
    builder.addOperation({from_char(op), value});
  }
  cout << builder.build() << endl;
  return 0;
}