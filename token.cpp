#include "token.h"

#include <algorithm>
#include <iomanip>

Token::Token(Type type, const std::string& lexeme) : m_type(type), m_lexeme(lexeme)
{

}

bool Token::operator==(const Token& other)
{
    if (m_type != other.type()) return false;
    if (m_lexeme != other.lexeme()) return false;

    return true;
}

bool Token::operator!=(const Token& other)
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
    return os << token.typeStr() << std::setw(20 - token.typeStr().length()) << "|" << token.lexeme() << "|";
}
