#include "EvalState.h"
#include "parser.h"
#include "scanner.h"
#include <iostream>

int main(int argc, char** argv)
{
    EvalState state;
    Scanner scanner;
    scanner.setSpaceOption(Scanner::SpaceOption::IgnoreSpace);
    while (true)
    {
        std::cout << "=> ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "quit")
        {
            break;
        }
        scanner.setInput(input);
        auto exp = ParseExp(scanner);
        std::cout << exp->eval(state) << std::endl;
        delete exp;
    }

    return 0;
}