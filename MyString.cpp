#include "MyString.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

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
            std::cout << "  * stringvalue dtor: refCount decreased to " << refCount << " (" << data << ")" << std::endl;
        }
    }
}

StringValue StringValue::operator+ (const StringValue& other) {
    std::cout << "  * stringvalue + operator (" << data << " + " << other.data << ")" << std::endl;
    char* concated = new char[size + other.getSize() - 1]; // drop first string's trailing '\0'
    for (int i = 0; i < size; i++) {
        concated[i] = data[i];
    }

    // start from size - 1 to omit trailing '\0'
    for (int i = 0; i < other.getSize(); i++) {
        concated[size - 1 + i] = other.data[i];
    }
    return StringValue(concated);
}

char& StringValue::operator[] (int index) {
    std::cout << "  * stringvalue [] operator" << std::endl;
    if (index < 0 || index >= size) {
        throw std::out_of_range("index out of range");
    }
    return data[index];
}

int StringValue::getRefCount() const {
    return refCount;
}

int StringValue::getSize() const {
    return size;
}

char* StringValue::getData() const {
    return data;
}

void StringValue::incrementRefCount() {
    ++refCount;
    std::cout << "  * stringvalue refCount increased to " << refCount << " (" << data << ")" << std::endl;
}

// mystring defs
MyString::MyString() {
    std::cout << " * mystring noarg ctor" << std::endl;
    value = new StringValue();
}

MyString::MyString(const char* d) {
    std::cout << " * mystring const char ctor (" << d << ")" << std::endl;
    value = new StringValue(d);
}

MyString::MyString(StringValue sv) {
    value = new StringValue(sv);
}

MyString::MyString(const MyString& other) {
    std::cout << " * mystring copy ctor (" << other.value->getData() << ")" << std::endl;
    value = other.value;
    value->incrementRefCount();
}

MyString::MyString(MyString && other) {
    std::cout << " * mystring move ctor (" << other.value->getData() << ")" << std::endl;
    value = other.value;
    other.value = nullptr;
    other.~MyString();
}

MyString::~MyString() {
    if (value != nullptr) {
        std::cout << " * mystring dtor (" << value->getData() << ")" << std::endl;
        value->~StringValue();
    } else {
        std::cout << " * mystring dtor noop" << std::endl;
    }
}

MyString& MyString::operator= (const MyString& rhs) {
    std::cout << " * mystring op= (" << *this << " = " << rhs << ")" << std::endl;
    if (this != &rhs) {
        value->~StringValue();
        value = rhs.value;
        value->incrementRefCount();
    }
    return *this;
}

MyString& MyString::operator= (MyString && rhs) {
    std::cout << " * mystring move op= (" << *this << " = " << rhs << ")" << std::endl;
    if (this != &rhs) {
        value->~StringValue();
        value = rhs.value;
        rhs.value = nullptr;
    }
    return *this;
}

MyString& MyString::operator+= (MyString& other) {
    std::cout << " * mystring += operator (" << *this << " += " << other << ")" << std::endl;
    *this = *this + other;
    return *this;
}

MyString MyString::operator+ (const MyString& other) {
    std::cout << " * mystring + operator (" << *this << " + " << other << ")" << std::endl;
    return MyString(*(value) + *(other.value));
}

const char& MyString::operator[] (int index) const {
    std::cout << " * mystring const [] operator" << std::endl;
    if (index < 0 || index >= value->getSize()) {
        throw std::out_of_range("index out of range");
    }
    return (*value)[index];
}

char& MyString::operator[] (int index) {
    std::cout << " * mystring [] operator" << std::endl;
    if (index < 0 || index >= value->getSize()) {
        throw std::out_of_range("index out of range");
    }

    // there will be other MyStrings who refer to this StringValue - no leak
    if (value->getRefCount() > 1) {
        value->~StringValue();
        value = new StringValue(value->getData());
    }
    return (*value)[index];
}

StringValue* MyString::getValue() {
    return value;
}

int MyString::getLength() {
    return value->getSize();
}

std::ostream& operator << (std::ostream& os, const MyString& myString) {
    os << myString.value->getData();
    return os;
}
