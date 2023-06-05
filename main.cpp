#include <iostream>

#include "DynamicArray.hpp"
#include "MyString.h"

int main()
{
    DynamicArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.pushBack(3);
    arr.pushBack(4);
    arr.pushBack(5);

    arr.popBack();
    arr.popBack();

    for (int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << std::endl;
    }

    DynamicArray<MyString> arr2;
    arr2.pushBack("Hello");
    arr2.pushBack("Haii");
    arr2.pushBack(":3333");
    arr2.pushBack(":,^)");

    arr2.erase(2);

    for (int i = 0; i < arr2.getSize(); i++) {
        std::cout << arr2[i] << std::endl;
    }
}

