#pragma once

#include <unordered_map>

class EvalState
{
public:
    EvalState();
    ~EvalState();
    void setValue(const std::string& var, int value);
    int getValue(const std::string& var);
    bool isDefined(const std::string& var);

private:
    std::unordered_map<std::string, int> symbolTable;
};