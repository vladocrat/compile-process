#include "lexer.h"

Lexer::Lexer(const std::string &filePath)
{
    m_inputFileStream.open(filePath);

    if (!checkOpen(m_inputFileStream))
    {
        //throw new runtime exception
    }
}

Lexer::~Lexer() noexcept
{
    if (!checkOpen(m_inputFileStream)) {
        //throw new runtime exception
    }

    m_inputFileStream.close();

    if (!checkOpen(m_outputFileStream))
    {
       //throw new runtime exception
    }

    m_outputFileStream.close();
}

Token Lexer::next()
{
    char c;

    while (m_inputFileStream.get(c))
    {
        switch (c)
        {
        case '\n':
            return Token(Token::Kind::Separator, "\n");
        case '\r':
            return Token(Token::Kind::Separator, "\r");
        case '\t':
            return Token(Token::Kind::Separator, "\t");
        case ' ':
            return Token(Token::Kind::Separator, " ");
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
            return completeIdentifier();
        }

    }

    return Token(Token::Kind::Undentified, "");
}

Token Lexer::completeIdentifier()
{
    auto charPointer = m_inputFileStream.tellg();
    auto finalString = "";

    while (!isSpace(m_inputFileStream.get()))
    {
        //finalString +=
    }

    return { };
}

bool Lexer::isSpace(char c)
{
    switch (c)
    {
    case '\n':
    case '\r':
    case '\t':
    case ' ':
        return true;
    }

    return false;
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
