#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <map>

class Token final
{
public:
    enum class Type {
        Identifier,
        Operator,
        Keyword,
        Literal,
        Separator,
        Undentified,
        Directive,
        Colon,
        SemiColon,
        OpenedBrace,
        ClosedBrace,
        OpenedCurlyBrace,
        ClosedCurlyBrace,
        OpenedSquareBrace,
        ClosedSquareBrace,
        EndOfFile
    };

    Token() {}; //TODO deletelater
    Token(Type kind, const std::string& lexeme);

    const Type kind()                 const  { return m_type; }
    const std::string lexeme()        const  { return m_lexeme; }
    const std::string kindStr()       const  { return m_kindStrings.find(m_type)->second; }

    bool operator==(const Token&);
    bool operator!=(const Token&);
    friend std::ostream& operator<<(std::ostream& os, const Token& token);

private:
    std::map<Type, std::string> m_kindStrings {
        { Type::Identifier, "Identifier" },               { Type::Operator, "Operator" },
        { Type::Keyword, "Keyword" },                     { Type::SemiColon, "Semicolon" },
        { Type::Literal, "Literal" },                     { Type::Separator, "Separator"},
        { Type::Undentified, "Undentified" },             { Type::EndOfFile, "EOF" },
        { Type::Directive, "Directive" },                 { Type::Colon, "Colon" },
        { Type::OpenedBrace, "OpenBrace" },               { Type::OpenedBrace, "OpenedBrace" },
        { Type::ClosedBrace, "ClosedBrace" },             { Type::ClosedBrace, "ClosedBrace" },
        { Type::OpenedCurlyBrace, "OpenedCurlyBrace" },   { Type::ClosedCurlyBrace, "ClosedCurlyBrace" },
        { Type::OpenedSquareBrace, "OpenedSquareBrace" }, { Type::ClosedSquareBrace, "ClosedSquareBrace" },
    };

    Type m_type          { Type::Undentified };
    std::string m_lexeme { "" };
};

#endif // TOKEN_H
