#include "MyString.h"
#include <iostream>
#include <cstring>

MyString::MyString(const char* d) {
    value = new StringValue(d);
}

MyString::~MyString() {
    std::cout << "mystring dtor" << std::endl;
    value->~StringValue();
}

StringValue::StringValue() : refCount {1} {
    size = 1;
    data = new char[size];
    data[size-1] = '\0';
}

StringValue::StringValue(const char* d) : refCount {1} {
    size = strlen(d) + 1;
    data = new char[size];
    for (int i = 0; i < size; i++) {
        data[i] = d[i];
    }
    data[size-1] = '\0';
}

StringValue::~StringValue() {
    std::cout << "stringvalue dtor" << std::endl;
    --refCount;
    if (refCount == 0) {
        delete[] data;
    }
}
