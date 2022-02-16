#include "exp.h"
#include <numeric>
#include <iostream>
#include <cassert>
#include <sstream>

ConstantExp::ConstantExp(int val)
    : Expression()
    , mVal(val)
{
}

ConstantExp::~ConstantExp()
{}

int ConstantExp::eval(EvalState& state)
{
    return mVal;
}

std::string ConstantExp::toString()
{
    return std::to_string(mVal);
}

Expression::ExprType ConstantExp::type()
{
    return ExprType::ConstantType;
}

int ConstantExp::getValue()
{
    return mVal;
}

IdentifierExp::IdentifierExp(const std::string& val)
    : Expression()
    , mName(val)
{}

IdentifierExp::~IdentifierExp()
{}

int IdentifierExp::eval(EvalState& state)
{
    return state.getValue(mName);
}

std::string IdentifierExp::toString()
{
    return mName;
}

Expression::ExprType IdentifierExp::type()
{
    return ExprType::IdentifierType;
}

std::string IdentifierExp::getName()
{
    return mName;
}

CompoundExp::CompoundExp(char op, Expression* lhs, Expression* rhs)
    : Expression()
    , mOp(op)
    , mLhs(lhs)
    , mRhs(rhs)
{}

CompoundExp::~CompoundExp()
{
    delete mLhs;
    mLhs = nullptr;
    delete mRhs;
    mRhs = nullptr;
}

int CompoundExp::eval(EvalState& state)
{
    assert(mLhs != nullptr && mRhs != nullptr);

    if (mOp == '=')
    {
        assert(mLhs->type() == ExprType::IdentifierType);
        auto val = mRhs->eval(state);
        state.setValue(dynamic_cast<IdentifierExp*>(mLhs)->getName(), val);
        return val;
    }
    else if (mOp == '+')
    {
        return mLhs->eval(state) + mRhs->eval(state);
    }
    else if (mOp == '-')
    {
        return mLhs->eval(state) - mRhs->eval(state);
    }
    else if (mOp == '*')
    {
        return mLhs->eval(state) * mRhs->eval(state);
    }
    else if (mOp == '/')
    {
        return mLhs->eval(state) / mRhs->eval(state);
    }
    else
    {
        assert(false && "Invalid operator");
    }
    return 0;
}

std::string CompoundExp::toString()
{
    std::stringstream ss;
    ss << '(' << mLhs->toString() << ' ' << mOp << ' ' << mRhs->toString() << ')';
    return ss.str();
}

Expression::ExprType CompoundExp::type()
{
    return ExprType::CompoundType;
}

char CompoundExp::getOp()
{
    return mOp;
}

Expression* CompoundExp::getLhs()
{
    return mLhs;
}

Expression* CompoundExp::getRhs()
{
    return mRhs;
}