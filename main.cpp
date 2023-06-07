#include <iostream>

#include "NDFA.h"

int main() {
    NDFA a("a.(b.a+b)*");

    std::cout << a.accept("aba");
    std::cout << a.accept("baa");
}

