#include "MyString.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

// stringvalue defs
StringValue::StringValue() : refCount {1} {
    int size = 0;
    data = new char[size + 1];
    data[size] = '\0';
    std::cout << "  * stringvalue noarg ctor (" << data << ")" << std::endl;
}

StringValue::StringValue(const StringValue& other) : refCount {1} {
    int size = strlen(other.getData());
    data = new char[size + 1];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
    data[size] = '\0';
    std::cout << "  * stringvalue copy ctor (" << data << ")" << std::endl;
}

StringValue::StringValue(StringValue && other) : refCount {1} {
    std::cout << " * stringvalue move ctor (" << other.data << ")" << std::endl;
    data = other.data;
    other.data = nullptr;
}

StringValue::StringValue(const char* string) : refCount {1} {
    int size = strlen(string) + 1;
    data = new char[size];
    for (int i = 0; i < size; i++) {
        data[i] = string[i];
    }
    data[size-1] = '\0';
    std::cout << "  * stringvalue const char ctor (" << data << ")" << std::endl;
}

StringValue::~StringValue() {
    std::cout << "  * stringvalue dtor" << std::endl;
    delete[] data;
}

StringValue& StringValue::operator= (StringValue rhs) {
    std::cout << " * stringvalue op= (" << data << " = " << rhs.data << ")" << std::endl;
    std::swap(refCount, rhs.refCount);
    std::swap(data, rhs.data);
    return *this;
}

char& StringValue::operator[] (int index) {
    int length = static_cast<int>(strlen(data));
    if (index < 0 || index >= length) {
        throw std::out_of_range("index out of range");
    }
    std::cout << "  * stringvalue [" << index << "] operator: " << data[index] << std::endl;
    return data[index];
}

int StringValue::getRefCount() const {
    return refCount;
}

char* StringValue::getData() const {
    return data;
}

void StringValue::incrementRefCount() {
    ++refCount;
    std::cout << "  * stringvalue refCount increased to " << refCount << " (" << data << ")" << std::endl;
}

void StringValue::decrementRefCount() {
    --refCount;
    std::cout << "  * stringvalue refCount decreased to " << refCount << " (" << data << ")" << std::endl;
}

StringValue operator+ (const StringValue& lhs, const StringValue& rhs) {
    std::cout << "  * stringvalue + operator (" << lhs.data << " + " << rhs.data << ")" << std::endl;
    int lhsLength = strlen(lhs.data);
    int rhsLength = strlen(rhs.data);
    char* concated = new char[lhsLength + rhsLength + 1];
    for (int i = 0; i < lhsLength; i++) {
        concated[i] = lhs.data[i];
    }
    for (int i = 0; i < rhsLength; i++) {
        concated[lhsLength + i] = rhs.data[i];
    }
    concated[lhsLength + rhsLength] = '\0';
    StringValue ret(concated);
    delete[] concated;
    return ret;
}

// mystring defs
MyString::MyString() {
    std::cout << " * mystring noarg ctor" << std::endl;
    value = new StringValue();
}

MyString::MyString(const char* string) {
    std::cout << " * mystring const char ctor (" << string << ")" << std::endl;
    value = new StringValue(string);
}

MyString::MyString(StringValue& stringValue) {
    value = new StringValue(stringValue);
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
}

MyString::~MyString() {
    std::cout << " * mystring dtor" << std::endl;
    if (value != nullptr) {
        unlinkStringValue();
    }
}

MyString& MyString::operator= (MyString rhs) {
    std::cout << " * mystring op= (" << *this << " = " << rhs << ")" << std::endl;
    std::swap(value, rhs.value);
    return *this;
}

MyString& MyString::operator+= (const MyString& rhs) {
    std::cout << " * mystring += operator (" << *this << " += " << rhs << ")" << std::endl;
    *this = *this + rhs;
    return *this;
}

MyString& MyString::operator+= (const char* string) {
    std::cout << " * mystring += operator with const char* (" << *this << " + " << string << ")" << std::endl;
    *this = *this + string;
    return *this;
}

MyString& MyString::operator+= (char string) {
    std::cout << " * mystring += operator with char (" << *this << " + " << string << ")" << std::endl;
    *this = *this + string;
    return *this;
}

const char& MyString::operator[] (int index) const {
    std::cout << " * mystring const [] operator" << std::endl;
    if (index < 0 || index >= static_cast<int>(strlen(value->getData()))) {
        throw std::out_of_range("index out of range");
    }
    return (*value)[index];
}

char& MyString::operator[] (int index) {
    std::cout << " * mystring [] operator" << std::endl;
    int length = static_cast<int>(strlen(value->getData()));
    if (index < 0 || index >= length) {
        throw std::out_of_range("index out of range");
    }

    // there will be other MyStrings who refer to this StringValue - no leak
    if (value->getRefCount() > 1) {
        unlinkStringValue();
        value = new StringValue(value->getData());
    }
    return (*value)[index];
}

StringValue* MyString::getValue() {
    return value;
}

int MyString::getLength() const {
    return strlen(value->getData());
}

void MyString::unlinkStringValue() {
    value->decrementRefCount();
    if (value->getRefCount() == 0) {
        delete value;
    }
}

MyString operator+ (const MyString& lhs, const MyString& rhs) {
    std::cout << " * mystring + operator (" << lhs << " + " << rhs << ")" << std::endl;
    StringValue concated((*lhs.value) + (*rhs.value));
    return MyString(concated);
}

MyString operator+ (const MyString& myString, const char* string) {
    std::cout << " * mystring + operator with const char* (" << myString << " + " << string << ")" << std::endl;
    const char* concated = new char[strlen(myString.value->getData()) + strlen(string) + 1];
    MyString ret(concated);
    delete[] concated;
    return ret;
}

MyString operator+ (const MyString& myString, char c) {
    std::cout << " * mystring + operator with char (" << myString << " + " << c << ")" << std::endl;
    int length = myString.getLength();
    char* concated = new char[length + 1 + 1]; // current + 1 char + \0
    for (int i = 0; i < length; i++) {
        concated[i] = myString[i];
    }
    concated[length] = c;
    concated[length + 1] = '\0';
    MyString ret(concated);
    delete[] concated;
    return ret;
}

std::ostream& operator<< (std::ostream& os, const MyString& myString) {
    os << myString.value->getData();
    return os;
}

std::istream& operator>> (std::istream& is, MyString& myString) {
    char buffer[256];
    is >> buffer;
    myString = MyString(buffer);
    return is;
}
