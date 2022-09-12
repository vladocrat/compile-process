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
    } while (t != Token(Token::Type::EndOfFile, ""));
}

Token Lexer::next()
{
    char c = ' ';

    while (m_inputFileStream.get(c) && !m_inputFileStream.eof())
    {
        if (isChar(c))
        {
            return completeIdentifier(c);
        }

        if (isNumber(c))
        {
            return completeNumber(c);
        }

        switch (c)
        {
        case '\n':
            return Token(Token::Type::Separator, "\\n");
        case '\r':
            return Token(Token::Type::Separator, "\\r");
        case '\t':
            return Token(Token::Type::Separator, "\\t");
        case ' ':
            return Token(Token::Type::Separator, "\' \'");
        case '/':
            return commentToSpace();
        case '#':
            return completeDirective(c);
        case ';':
            return Token(Token::Type::SemiColon, ";");
        case ':':
            return Token(Token::Type::Colon, ":");
        case '(':
            return Token(Token::Type::OpenedBrace, "(");
        case ')':
            return Token(Token::Type::ClosedBrace, ")");
        case '<':
            return completeAngledBrace(c);
        case '>':
            return completeAngledBrace(c);
        case '{':
            return Token(Token::Type::OpenedCurlyBrace, "{");
        case '}':
            return Token(Token::Type::ClosedCurlyBrace, "}");
        case '\"':
            return completeStringLiteral(c);
        case '=':
            return Token(Token::Type::Operator, "=");
        case '*':
            return Token(Token::Type::Operator, "*");
        case '+':
            return Token(Token::Type::Operator, "+");
        case '-':
            return Token(Token::Type::Operator, "-");
        case '!':
            return Token(Token::Type::Operator, "!");
        case '&':
            return Token(Token::Type::Operator, "&");
        case '.':
            return Token(Token::Type::Operator, ".");
        case ',':
            return Token(Token::Type::Operator, ",");
        case '[':
            return Token(Token::Type::OpenedSquareBrace, "[");
        case ']':
            return Token(Token::Type::ClosedSquareBrace, "]");
        case '\'':
            return completeCharLiteral(c);
        }
    }

    return Token(Token::Type::EndOfFile, "");
}

Token Lexer::completeIdentifier(char lastChar)
{
    setUpString(lastChar);

    while ((isChar(m_detectedChar)) && isChar(m_inputFileStream.peek()))
    {
        getLastCharAndAppend();
    }

    if (isKeyword(m_finalString))
    {
        return Token(Token::Type::Keyword, m_finalString);
    }

    return Token(Token::Type::Identifier, m_finalString);
}

Token Lexer::completeNumber(char lastNumber)
{
    setUpString(lastNumber);

    while (isNumber(m_detectedChar) && isNumber(m_inputFileStream.peek()))
    {
        getLastCharAndAppend();
    }

    getLastCharAndAppend();

    if (isKeyword(m_finalString))
    {
        return Token(Token::Type::Keyword, m_finalString);
    }

    return Token(Token::Type::Literal, m_finalString);
}

Token Lexer::commentToSpace()
{
    char c = ' ';

    while (m_inputFileStream.peek() != '\n')
    {
        m_inputFileStream.get(c);
    }

    m_inputFileStream.get(c);

    return Token(Token::Type::Separator, "\\n");
}

Token Lexer::completeDirective(char lastChar)
{
    setUpString(lastChar);

    while ((!m_inputFileStream.get(m_detectedChar) || !isSpace(m_detectedChar)) && isChar(m_detectedChar))
    {
        m_finalString += m_detectedChar;
    }

    return Token(Token::Type::Directive, m_finalString);
}

Token Lexer::completeAngledBrace(char lastChar)
{
    setUpString(lastChar);

    if (isDoubleAngledBrace(lastChar, m_inputFileStream.peek()))
    {
        getLastCharAndAppend();

        return Token(Token::Type::Operator, m_finalString);
    }

    return Token(Token::Type::Operator, m_finalString);
}

Token Lexer::completeStringLiteral(char lastChar)
{
    setUpString(lastChar);

    while (m_inputFileStream.peek() != '\"')
    {
        getLastCharAndAppend();
    }

    getLastCharAndAppend();

    return Token(Token::Type::Literal, m_finalString);
}

Token Lexer::completeCharLiteral(char lastChar)
{
    setUpString(lastChar);

    while (m_inputFileStream.peek() != '\'')
    {
        getLastCharAndAppend();
    }

    getLastCharAndAppend();

    return Token(Token::Type::Literal, m_finalString);
}

void Lexer::setUpString(char c)
{
    m_finalString = "";
    m_finalString += c;
    m_detectedChar = c;
}

void Lexer::getLastCharAndAppend()
{
    m_inputFileStream.get(m_detectedChar);
    m_finalString += m_detectedChar;
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
