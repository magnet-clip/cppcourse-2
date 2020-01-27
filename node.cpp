#include "node.h"

using namespace std;

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
  return true;
}

bool LogicalOperationNode::Evaluate(const Date &date,
                                    const string &event) const {
  if (_op == LogicalOperation::And) {
    return _left->Evaluate(date, event) && _right->Evaluate(date, event);
  } else {
    return _left->Evaluate(date, event) || _right->Evaluate(date, event);
  }
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const {
  if (_cmp == Comparison::Equal) {
    return date == _date;
  } else if (_cmp == Comparison::Greater) {
    return date > _date;
  } else if (_cmp == Comparison::GreaterOrEqual) {
    return date >= _date;
  } else if (_cmp == Comparison::Less) {
    return date < _date;
  } else if (_cmp == Comparison::LessOrEqual) {
    return date <= _date;
  } else { // NotEqual
    return date != _date;
  }
}

bool EventComparisonNode::Evaluate(const Date &date,
                                   const string &event) const {
  if (_cmp == Comparison::Equal) {
    return event == _event;
  } else if (_cmp == Comparison::Greater) {
    return event > _event;
  } else if (_cmp == Comparison::GreaterOrEqual) {
    return event >= _event;
  } else if (_cmp == Comparison::Less) {
    return event < _event;
  } else if (_cmp == Comparison::LessOrEqual) {
    return event <= _event;
  } else { // NotEqual
    return event != _event;
  }
}