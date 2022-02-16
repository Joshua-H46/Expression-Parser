#pragma once

#include "exp.h"
#include "scanner.h"

Expression* ParseExp(Scanner& scanner);
Expression* ReadE(Scanner& scanner, int prec = 0);
Expression* ReadT(Scanner& scanner);

int Precedence(const std::string& token);