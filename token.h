#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

class Token final
{
public:
    enum class Kind {
        Idenrifier,
        Operator,
        Keyword,
        Parenthesis,
        Literal,
        Separator,
        Undentified,
    };

    Token() {}; //TODO deletelater
    Token(Kind kind, const std::string& lexeme);

    Kind kind()          const { return m_kind; }
    std::string lexeme() const { return m_lexeme; }

private:
    Kind m_kind { Kind::Undentified };
    std::string m_lexeme { "" };
};

#endif // TOKEN_H
