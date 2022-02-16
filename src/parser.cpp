#include "parser.h"
#include <cassert>

Expression* ParseExp(Scanner& scanner)
{
    scanner.setSpaceOption(Scanner::SpaceOption::IgnoreSpace);
    auto exp = ReadE(scanner, 0);
    if (scanner.hasMoreTokens())
    {
        assert(false && "Invalid input");
        return nullptr;
    }
    return exp;
}

Expression* ReadE(Scanner& scanner, int prec)
{
    auto exp = ReadT(scanner);
    while (true)
    {
        auto op = scanner.nextToken();
        auto newPrec = Precedence(op);
        if (newPrec <= prec)
        {
            scanner.saveToken(op);
            break;
        }
        auto rhs = ReadE(scanner, newPrec);
        exp = new CompoundExp(op[0], exp, rhs);
    }
    return exp;
}

Expression* ReadT(Scanner& scanner)
{
    if (!scanner.hasMoreTokens())
    {
        return nullptr;
    }
    
    Expression* exp = nullptr;
    auto token = scanner.nextToken();
    if (isdigit(token[0]))
    {
        exp = new ConstantExp(std::stoi(token));
    }
    else if (isalpha(token[0]))
    {
        exp = new IdentifierExp(token);
    }
    else if (token[0] == '(')
    {
        exp = ReadE(scanner, 0);
        if (scanner.nextToken() != ")")
        {
            return nullptr;
        }
    }
    else
    {
        assert(false);
        return nullptr;
    }

    return exp;
}

int Precedence(const std::string& token)
{
    if (token.size() > 1)
    {
        return 0;
    }

    switch (token[0])
    {
    case '=':
        return 1;
        break;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    default:
        return 0;
    }
}