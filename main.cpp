#include <iostream>

#include "lexer.h"

int main()
{
    Lexer l("lexer.h", "newFile.txt");
    l.parse();

    return 0;
}
