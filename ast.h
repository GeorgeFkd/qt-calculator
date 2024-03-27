#pragma once

#include <memory>
#include <variant>

struct NumericNode {
    double value;
    double compute() {
        return value;
    }
};

struct BasicOperationNode;

using Expression = std::variant<
    NumericNode,
    std::unique_ptr<BasicOperationNode>>;

struct BasicOperationNode {
    enum Type {
        None,
        Plus,
        Minus,
        Times,
        Div
    };
    ~BasicOperationNode();

    Expression m_left;
    Expression m_right;
    Type m_type;

    BasicOperationNode(Expression left,Expression right,Type type)
        : m_left(std::move(left)),
                 m_right(std::move(right)),
          m_type(type){}
};

double compute(Expression& expr);
double compute(NumericNode& expr);
double compute(BasicOperationNode& expr);


