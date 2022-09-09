#include <iostream>

#include "lexer.h"

int main()
{
    Lexer l("file.txt");
    l.parse();

    return 0;
}
