#include <iostream>

#include "NDFA.h"

int main() {
    //NDFA a("(a.b)");
    //NDFA a("(a+b)");
    NDFA a("((a)*)");

    std::cout << a.accept("aaa");
    //std::cout << a.accept("baa");
}

