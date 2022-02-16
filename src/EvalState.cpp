#include "EvalState.h"

EvalState::EvalState()
{

}

EvalState::~EvalState()
{

}

void EvalState::setValue(const std::string& var, int value)
{
    symbolTable[var] = value;
}

int EvalState::getValue(const std::string& var)
{
    if (!symbolTable.count(var))
    {
        return 0;
    }
    return symbolTable[var];
}

bool EvalState::isDefined(const std::string& var)
{
    return symbolTable.count(var);
}