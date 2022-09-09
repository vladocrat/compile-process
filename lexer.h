#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>

#include "token.h"

class Lexer final
{
public:
    Lexer(const std::string& filePath);
    ~Lexer() noexcept;

    Token next();
    Token completeIdentifier();
    bool isSpace(char c);
    //check keyword from identifier;
    //void parse TODO continously call next until file is read.

private:
    template<class T>
    [[nodiscard]] bool checkOpen(const T& stream) const;

    std::ifstream m_inputFileStream;
    std::fstream m_outputFileStream;
};

#endif // LEXER_H
