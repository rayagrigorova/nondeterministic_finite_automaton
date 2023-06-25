#include <iostream>
#include "SymbolConstants.h"

#include "NDFA.h"

#include "Program.h"

int main() {
    //    Example regular expressions: 
    //    (a.b)
    //    ((a.b)+(b.a))

    //    (a.((((b.a)+b))*))
    //    (b.((a)*))

    //    (a+b)
    //    ((a.b)+a)

    // (((a+b))*)

    // (((a.b))*)

    Program::getInstance().run();
}

