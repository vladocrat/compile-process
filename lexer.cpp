#include "lexer.h"

#include <algorithm>
#include <exception>

Lexer::Lexer(const std::string& filePath, const std::string& writeFilePath)
{
    if (!initialize(filePath, writeFilePath))
    {
        throw new std::runtime_error("Failed to initialize lexer");
    }
}

Lexer::~Lexer() noexcept
{
    m_inputFileStream.close();
    m_outputFileStream.close();
}

void Lexer::parse()
{
    Token t;

    do {
        t = next();
        //std::cout << t << std::endl;
        m_outputFileStream << t << "\n";
    } while (t != Token(Token:: Type::EndOfFile, ""));
}

Token Lexer::next()
{
    char c;

    while (m_inputFileStream.get(c) && !m_inputFileStream.eof())
    {
        switch (c)
        {
        case '\n':
            return Token(Token:: Type::Separator, "\\n");
        case '\r':
            return Token(Token:: Type::Separator, "\\r");
        case '\t':
            return Token(Token:: Type::Separator, "\\t");
        case ' ':
            return Token(Token:: Type::Separator, "\' \'");
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            return completeIdentifier(c);
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return completeNumber(c);
        case '/':
            return commentToSpace();
        case '#':
            return completeDirective(c);
        case ';':
            return Token(Token:: Type::SemiColon, ";");
        case ':':
            return Token(Token:: Type::Colon, ":");
        case '(':
            return Token(Token:: Type::OpenedBrace, "(");
        case ')':
            return Token(Token:: Type::ClosedBrace, ")");
        case '<':
            return completeAngledBrace(c);
        case '>':
            return completeAngledBrace(c);
        case '{':
            return Token(Token:: Type::OpenedCurlyBrace, "{");
        case '}':
            return Token(Token:: Type::ClosedCurlyBrace, "}");
        case '\"':
            return completeStringLiteral(c);
        case '=':
            return Token(Token:: Type::Operator, "=");
        case '*':
            return Token(Token:: Type::Operator, "*");
        case '+':
            return Token(Token:: Type::Operator, "+");
        case '-':
            return Token(Token:: Type::Operator, "-");
        case '!':
            return Token(Token:: Type::Operator, "!");
        case '&':
            return Token(Token:: Type::Operator, "&");
        case '.':
            return Token(Token:: Type::Operator, ".");
        case ',':
            return Token(Token:: Type::Operator, ",");
        case '[':
            return Token(Token:: Type::OpenedSquareBrace, "[");
        case ']':
            return Token(Token:: Type::ClosedSquareBrace, "]");
        case '\'':
            return completeCharLiteral(c);
        }
    }

    return Token(Token:: Type::EndOfFile, "");
}

Token Lexer::completeIdentifier(char lastChar)
{
    std::string finalString = "";
    finalString += lastChar;
    char c = lastChar;

    while ((isChar(c)) && isChar(m_inputFileStream.peek()))
    {
        m_inputFileStream.get(c);
        finalString += c;
    }

    if (isKeyword(finalString))
    {
        return Token(Token:: Type::Keyword, finalString);
    }

    return Token(Token:: Type::Identifier, finalString);
}

Token Lexer::completeNumber(char lastNumber)
{
    std::string finalString = "";
    finalString += lastNumber;
    char c = ' ';

    while (isNumber(c) && isNumber(m_inputFileStream.peek()))
    {
        m_inputFileStream.get(c);
        finalString += c;
    }

    m_inputFileStream.get(c);
    finalString += c;

    if (isKeyword(finalString))
    {
        return Token(Token:: Type::Keyword, finalString);
    }

    return Token(Token:: Type::Literal, finalString);
}

Token Lexer::commentToSpace()
{
    char c = ' ';

    while (m_inputFileStream.peek() != '\n')
    {
        m_inputFileStream.get(c);
    }

    m_inputFileStream.get(c);

    return Token(Token:: Type::Separator, "\\n");
}

Token Lexer::completeDirective(char lastChar)
{
    std::string finalString = "";
    finalString += lastChar;
    char c = ' ';

    while ((!m_inputFileStream.get(c) || !isSpace(c)) && isChar(c))
    {
        finalString += c;
    }

    return Token(Token:: Type::Directive, finalString);
}

Token Lexer::completeAngledBrace(char lastChar)
{
    std::string finalString = "";
    finalString += lastChar;
    char c = ' ';

    if (isDoubleAngledBrace(lastChar, m_inputFileStream.peek()))
    {
        m_inputFileStream.get(c);
        finalString += c;

        return Token(Token:: Type::Operator, finalString);
    }

    return Token(Token:: Type::Operator, finalString);
}

Token Lexer::completeStringLiteral(char lastChar)
{
    std::string finalString = "";
    finalString += lastChar;
    char c = ' ';

    while (m_inputFileStream.peek() != '\"')
    {
        m_inputFileStream.get(c);
        finalString += c;
    }

    m_inputFileStream.get(c);
    finalString += c;

    return Token(Token:: Type::Literal, finalString);
}

Token Lexer::completeCharLiteral(char lastChar)
{
    std::string finalString = "";
    finalString += lastChar;
    char c = ' ';

    while (m_inputFileStream.peek() != '\'')
    {
        m_inputFileStream.get(c);
        finalString += c;
    }

    m_inputFileStream.get(c);
    finalString += c;

    return Token(Token:: Type::Literal, finalString);
}

bool Lexer::isSpace(char c) const
{
    return std::find(begin(m_spaceChars), end(m_spaceChars), c) != end(m_spaceChars);
}

bool Lexer::isKeyword(const std::string& identifier) const
{
    return std::find(begin(m_keywords), end(m_keywords), identifier) != end(m_keywords);
}

bool Lexer::isNumber(char c) const
{
    return std::find(begin(m_numbers), end(m_numbers), c) != end(m_numbers);
}

bool Lexer::isChar(char c) const
{
    return std::find(begin(m_chars), end(m_chars), c) != end(m_chars);
}

bool Lexer::isDoubleAngledBrace(char currentChar, char nextChar) const
{
    return currentChar == nextChar;
}

bool Lexer::initialize(const std::string& filePath, const std::string& writeFilePath)
{
    m_inputFileStream.open(filePath);

    if (!checkOpen(m_inputFileStream))
    {
        return false;
    }

    m_outputFileStream.open(writeFilePath);

    if (!checkOpen(m_outputFileStream))
    {
        return false;
    }

    return true;
}

template<class T>
bool Lexer::checkOpen(const T& stream) const
{
    if (!stream.is_open())
    {
        std::cout << "ERROR::FAILED_TO_OPEN_FILE" << std::endl;
        return false;
    }

    return true;
}
