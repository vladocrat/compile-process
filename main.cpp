#include <iostream>

#include "lexer.h"

int main()
{
    Lexer l("file.txt");

    //while (l.next() == Token(Token::Kind::EndOfFile, ""))
    //{
        std::cout << l.next() << std::endl;
    //}

    return 0;
}
