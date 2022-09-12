#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "token.h"

class Lexer final
{
public:
    Lexer(const std::string& filePath, const std::string& writeFilePath);
    ~Lexer() noexcept;

    void parse();

private:
    Token next();
    Token completeIdentifier(char lastChar);
    Token completeNumber(char lastNumber);
    Token commentToSpace();
    Token completeDirective(char lastChar);
    Token completeAngledBrace(char lastChar);
    Token completeStringLiteral(char lastChar);
    Token completeCharLiteral(char lastChar);
    inline bool isSpace(char c) const;
    inline bool isKeyword(const std::string& identifier) const;
    inline bool isNumber(char c) const;
    inline bool isChar(char c) const;
    inline bool isDoubleAngledBrace(char currentChar, char nextChar) const;
    void setUpString(char c);
    void getLastCharAndAppend();

    template<class T>
    [[nodiscard]] bool checkOpen(const T& stream) const;
    bool initialize(const std::string& filePath, const std::string& writeFilePath);

    const std::vector<std::string> m_keywords = {
        "int", "bool", "char", "float", "double", "return", "false",
        "const", "noexcept", "final", "class", "struct", "true",
        "template", "private", "public", "protected", "string",
        "cout", "endl", "std", "if", "while", "switch", "do", "ostream",
        "fstream", "ifstream", "operator", "nodiscard", "throw", "new",
        "runtime_error",
    };

    const std::vector<char> m_chars = {
        '_', 'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h', 'i',
        'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's',
        't', 'u', 'v', 'w', 'x',
        'y', 'z', 'A', 'B', 'C',
        'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W',
        'X', 'Y', 'Z',
    };

    const std::vector<char> m_numbers = {
        '0', '1', '2',
        '3', '4', '5',
        '6', '7', '8',
        '9',
    };

    const std::vector<char> m_spaceChars = {
        '\n', '\r',
        '\t', ' ',
    };

    std::ifstream m_inputFileStream;
    std::ofstream m_outputFileStream;
    std::string m_finalString { "" };
    char m_detectedChar       { ' ' };
};

#endif // LEXER_H
