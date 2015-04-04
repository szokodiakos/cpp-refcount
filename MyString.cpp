#include "MyString.h"
#include <iostream>
#include <cstring>

// stringvalue defs
StringValue::StringValue() : refCount {1} {
    size = 1;
    data = new char[size];
    data[size-1] = '\0';
    std::cout << "  * stringvalue noarg ctor (" << data << ")" << std::endl;
}

StringValue::StringValue(const char* d) : refCount {1} {
    size = strlen(d) + 1;
    data = new char[size];
    for (int i = 0; i < size; i++) {
        data[i] = d[i];
    }
    data[size-1] = '\0';
    std::cout << "  * stringvalue const char ctor (" << data << ")" << std::endl;
}

StringValue::~StringValue() {
    if (refCount != -1) {
        --refCount;
        if (refCount == 0) {
            std::cout << "  * stringvalue dtor (" << data << ")" << std::endl;
            delete[] data;
        } else {
            std::cout << "  * stringvalue refCount decreased to " << refCount << " (" << data << ")" << std::endl;
        }
    }
}

int StringValue::getRefCount() {
    return refCount;
}

char* StringValue::getData() {
    return data;
}

void StringValue::incrementRefCount() {
    ++refCount;
    std::cout << "  * stringvalue refCount increased to " << refCount << " (" << data << ")" << std::endl;
}

// mystring defs
MyString::MyString() {
    value = new StringValue();
    std::cout << " * mystring noarg ctor" << std::endl;
}

MyString::MyString(const char* d) {
    std::cout << " * mystring const char ctor (" << d << ")" << std::endl;
    value = new StringValue(d);
}

MyString::MyString(const MyString& other) {
    std::cout << " * mystring copy ctor (" << other.value->getData() << ")" << std::endl;
    value = other.value;
    value->incrementRefCount();
}

MyString::~MyString() {
    std::cout << " * mystring dtor (" << value->getData() << ")" << std::endl;
    value->~StringValue();
}

MyString& MyString::operator= (const MyString& rhs) {
    std::cout << " * mystring op=" << std::endl;
    if (this != &rhs) {
        value = rhs.value;
        value->incrementRefCount();
    }
    return *this;
}

StringValue* MyString::getValue() {
    return value;
}

std::ostream& operator << (std::ostream& os, const MyString& myString) {
    os << myString.value->getData();
    return os;
}
