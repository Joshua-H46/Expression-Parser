#pragma once

#include "EvalState.h"
#include <string>

class Expression
{
public:
    enum class ExprType
    {
        ConstantType,
        IdentifierType,
        CompoundType
    };

    Expression() {};
    virtual ~Expression() {};
    virtual int eval(EvalState& state) = 0;
    virtual std::string toString() = 0;
    virtual ExprType type() = 0;
};

class ConstantExp : public Expression
{
public:
    ConstantExp(int val);
    virtual ~ConstantExp();
    virtual int eval(EvalState& state) override;
    virtual std::string toString() override;
    virtual ExprType type() override;

    int getValue();

private:
    int mVal;
};

class IdentifierExp : public Expression
{
public:
    IdentifierExp(const std::string& val);
    virtual ~IdentifierExp();
    virtual int eval(EvalState& state) override;
    virtual std::string toString() override;
    virtual ExprType type() override;

    std::string getName();

private:
    std::string mName;
};

class CompoundExp : public Expression
{
public:
    CompoundExp(char op, Expression* lhs, Expression* rhs);
    virtual ~CompoundExp();
    virtual int eval(EvalState& state) override;
    virtual std::string toString() override;
    virtual ExprType type() override;

    char getOp();
    Expression* getLhs();
    Expression* getRhs();

private:
    char mOp;
    Expression* mLhs{nullptr};
    Expression* mRhs{nullptr};
};