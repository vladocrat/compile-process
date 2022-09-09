#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <map>

class Token final
{
public:
    enum class Kind {
        Identifier,
        Operator,
        Keyword,
        Parenthesis,
        Literal,
        Separator,
        Undentified,
        EndOfFile
    };

    Token() {}; //TODO deletelater
    Token(Kind kind, const std::string& lexeme);

    const Kind kind()                 const  { return m_kind; }
    const std::string lexeme()        const  { return m_lexeme; }
    const std::string kindStr()       const  { return m_kindStrings.find(m_kind)->second; }

    bool operator==(const Token&);
    bool operator!=(const Token&);
    friend std::ostream& operator<<(std::ostream& os, const Token& token);

private:
    std::map<Kind, std::string> m_kindStrings {
        { Kind::Identifier, "Identifier" }, { Kind::Operator, "Operator" },
        { Kind::Keyword, "Keyword" }, { Kind::Parenthesis, "Parenthesis" },
        { Kind::Literal, "Literal" }, { Kind::Separator, "Separator"},
        { Kind::Undentified, "Undentified" }, { Kind::EndOfFile, "EOF" }
    };

    Kind m_kind { Kind::Undentified };
    std::string m_lexeme { "" };
};

#endif // TOKEN_H
