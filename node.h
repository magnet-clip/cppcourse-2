#pragma once
#include <memory>
#include <string>
#include "date.h"

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum class LogicalOperation { And, Or };

// Logical expression evaluation abstract base class
class Node {
 public:
  virtual bool Evaluate(const Date &date, const std::string &event) const = 0;
};

// Empty expression
class EmptyNode : public Node {
  virtual bool Evaluate(const Date &date,
                        const std::string &event) const override;
};

// Expression containing date comparison
class DateComparisonNode : public Node {
 public:
  DateComparisonNode(const Comparison &cmp, const Date &date)
      : _cmp(cmp), _date(date) {}
  virtual bool Evaluate(const Date &date,
                        const std::string &event) const override;

 private:
  Comparison _cmp;
  Date _date;
};

// Expression containing string comparison
class EventComparisonNode : public Node {
 public:
  EventComparisonNode(const Comparison &cmp, const std::string &event)
      : _event(event), _cmp(cmp) {}
  virtual bool Evaluate(const Date &date,
                        const std::string &event) const override;

 private:
  Comparison _cmp;
  const std::string _event;
};

// Expression which combines result of two nodes evaluation
class LogicalOperationNode : public Node {
 public:
  LogicalOperationNode(const LogicalOperation &op,
                       const std::shared_ptr<Node> &left,
                       const std::shared_ptr<Node> &right)
      : _op(op), _left(left), _right(right) {}

  virtual bool Evaluate(const Date &date,
                        const std::string &event) const override;

 private:
  const std::shared_ptr<Node> _left, _right;
  const LogicalOperation _op;
};