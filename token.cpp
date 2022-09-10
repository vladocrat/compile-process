#include "token.h"

#include <algorithm>
#include <iomanip>

Token::Token(Type kind, const std::string& lexeme) : m_type(kind), m_lexeme(lexeme)
{

}

bool Token::operator==(const Token& other)
{
    if (m_type != other.kind()) return false;
    if (m_lexeme != other.lexeme()) return false;

    return true;
}

bool Token::operator!=(const Token& other)
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
    return os << token.kindStr() << std::setw(20 - token.kindStr().length()) << "|" << token.lexeme() << "|";
}
