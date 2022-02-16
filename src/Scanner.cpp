#include "scanner.h"
#include <cassert>

Scanner::Scanner()
{}

Scanner::~Scanner()
{}

void Scanner::setInput(const std::string& str)
{
    mBuffer = str;
    len = mBuffer.length();
    cp = 0;
}

// void Scanner::setInput(std::ifstream& fs)
// {

// }

bool Scanner::hasMoreTokens()
{
    if (cp == -1)
    {
        assert(false && "Input has not been set");
        return false;
    }
    if (mSpaceOption == SpaceOption::IgnoreSpace)
    {
        skipSpaces();
    }
    return cp < len;
}

std::string Scanner::nextToken()
{
    if (cp == -1)
    {
        assert(false && "Input has not been set");
    }
    
    if (mSpaceOption == SpaceOption::IgnoreSpace)
    {
        skipSpaces();
    }
    int start = cp;
    if (start >= len)
    {
        return "";
    }
    if (isalnum(mBuffer[start]))
    {
        auto end = scanToIdentifierEnd();
        return mBuffer.substr(start, end - start);
    }
    cp++;
    return mBuffer.substr(start, 1);
}

void Scanner::saveToken(const std::string& token)
{
    cp -= token.size();
}

Scanner::SpaceOption Scanner::getSpaceOption()
{
    return mSpaceOption;
}

void Scanner::setSpaceOption(Scanner::SpaceOption op)
{
    mSpaceOption = op;
}

int Scanner::scanToIdentifierEnd()
{
    // auto checker = isalpha(mBuffer[cp]) ? isalpha : isdigit;
    while (cp < len && isalnum(mBuffer[cp]))
    {
        cp++;
    }
    return cp;
}

void Scanner::skipSpaces()
{
    while (cp < len && isspace(mBuffer[cp]))
    {
        cp++;
    }
}