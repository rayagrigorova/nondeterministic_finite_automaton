#include <iostream>
#include "SymbolConstants.h"

#include "NDFA.h"

int main() {
    //NDFA a("(a.b)");
    //NDFA a("(a+b)");
    NDFA a("((a)*)");

    std::cout << a.accept(&EPSILON);
    //std::cout << a.accept("baa");
}

