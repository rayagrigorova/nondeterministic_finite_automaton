#include <iostream>

#include "../Constants/SymbolConstants.h"
#include "../NDFA/NDFA.h"
#include "../Program/Program.h"

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

