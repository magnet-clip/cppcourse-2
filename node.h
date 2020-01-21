#pragma once
#include "date.h"
#include <memory>
#include <string>

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum class LogicalOperation { And, Or };
class Node {
public:
  bool Evaluate(const Date &date, const std::string &event);
};

class EmptyNode : public Node {};
class DateComparisonNode : public Node {
public:
  DateComparisonNode(Date);
  DateComparisonNode(Comparison &, Date);
};
class EventComparisonNode : public Node {
public:
  EventComparisonNode(const std::string &);
  EventComparisonNode(Comparison &, const std::string &);
};
class LogicalOperationNode : public Node {
public:
  LogicalOperationNode(std::shared_ptr<Node>);
  LogicalOperationNode(const LogicalOperation &, std::shared_ptr<Node> &,
                       std::shared_ptr<Node>);
};