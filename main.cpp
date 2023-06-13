#include <iostream>
#include "SymbolConstants.h"

#include "NDFA.h"

int main() {
    //NDFA a("(a.b)");
    //NDFA a("(a+b)");
    NDFA a("((a.b)+(b.a))");

    std::cout << a.isEmptyLanguage() << std::endl;
    std::cout << a.accept("ba") << std::endl;
    std::cout << a.accept("ab") << std::endl;

    //std::cout << a.accept("baa");
}

