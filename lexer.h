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

    void parse();

private:
    Token next();
    Token completeIdentifier(char lastChar);
    Token completeNumber(char lastNumber);
    Token commentToSpace();
    Token completeDirective(char lastChar);
    bool isSpace(char c) const;
    bool isKeyword(const std::string& identifier) const;
    bool isNumber(char c) const;
    bool isChar(char c) const;

    template<class T>
    [[nodiscard]] bool checkOpen(const T& stream) const;

    const std::vector<std::string> m_keywords = {
        "int", "bool", "char", "float", "double", "return", "false",
        "const", "noexcept", "final", "class", "struct", "true",
        "template", "private", "public", "protected", "std::string",
        "std::cout", "std::endl"
    };

    std::ifstream m_inputFileStream;
    std::fstream m_outputFileStream;
};

#endif // LEXER_H
