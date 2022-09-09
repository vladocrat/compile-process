#include <iostream>

#include "lexer.h"

int main()
{
    Lexer l("token.h", "newFile.txt");
    l.parse();

    return 0;
}
