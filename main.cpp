﻿#include <iostream>
#include "SymbolConstants.h"

#include "NDFA.h"

int main() {
    //NDFA a("(a.b)");
    //NDFA a("(a+b)");
    //NDFA a("((a.b)+(b.a))");

    NDFA t("(a.((((b.a)+b))*))");

    std::cout << "Is empty language: " << t.isEmptyLanguage() << std::endl;
    std::cout << "Accept: " << t.accept("aba") << std::endl;
    std::cout << "Accept: " << t.accept("baa") << std::endl;

    NDFA t2("(b.((a)*))");
    NDFA t3 = Union(t, t2);
    std::cout << "Accept: " << t3.accept("aba") << std::endl;
    std::cout << "Accept: " << t3.accept("baa") << std::endl;

    //std::cout << a.accept("baa");
}

