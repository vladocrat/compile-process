#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "token.h"

class Lexer final
{
public:
    Lexer(const std::string& filePath);
    ~Lexer() noexcept;

    Token next();
    Token completeIdentifier(char lastChar);
    bool isSpace(char c);
    bool isKeyword(const std::string& identifier) const;
    //void parse TODO continously call next until file is read.

private:
    const std::vector<std::string> m_keywords = {
        "int", "bool", "char", "float", "double", "return", "false",
        "const", "noexcept", "final", "class", "struct", "true",
        "template", "private", "public", "protected", "std::string",
    };


    template<class T>
    [[nodiscard]] bool checkOpen(const T& stream) const;

    std::ifstream m_inputFileStream;
    std::fstream m_outputFileStream;
};

#endif // LEXER_H
