#include <iostream>
#include "SymbolConstants.h"

#include "NDFA.h"

#include "Program.h"

int main() {
    //    (a.b)
    //    (a+b)
    //    ((a.b)+(b.a))

    //    (a.((((b.a)+b))*))
    //    (b.((a)*))

    //    (((a+b))*)

    //    (a+b)
    //    ((a.b)+a)

    Program::getInstance().run();
   
}

