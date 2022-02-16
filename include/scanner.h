#pragma once
#include <string>
#include <fstream>
#include <vector>

class Scanner
{
public:
    enum class SpaceOption
    {
        PreserveSpace,
        IgnoreSpace
    };
    
    Scanner();
    ~Scanner();

    void setInput(const std::string& str);
    // void setInput(std::ifstream& fs);
    bool hasMoreTokens();
    std::string nextToken();
    void saveToken(const std::string& token);
    SpaceOption getSpaceOption();
    void setSpaceOption(SpaceOption);

private:
    void skipSpaces();
    int scanToIdentifierEnd();

    std::string mBuffer;
    int len;
    int cp{-1};
    SpaceOption mSpaceOption{SpaceOption::PreserveSpace};
    std::vector<std::string> mTokens;
};