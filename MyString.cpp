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

StringValue::StringValue(const char* d) : refCount {1} {
    int size = strlen(d) + 1;
    data = new char[size];
    for (int i = 0; i < size; i++) {
        data[i] = d[i];
    }
    data[size-1] = '\0';
    std::cout << "  * stringvalue const char ctor (" << data << ")" << std::endl;
}

StringValue::~StringValue() {
    std::cout << "  * stringvalue dtor" << std::endl;
    delete[] data;
}

StringValue& StringValue::operator= (const StringValue& rhs) {
    std::cout << " * stringvalue op= (" << data << " = " << rhs.data << ")" << std::endl;
    if (this != &rhs) {
        delete[] data;
        int rhsLength = strlen(rhs.getData());
        data = new char[rhsLength + 1];
        for (int i = 0; i < rhsLength; i++) {
            data[i] = rhs.getData()[i];
        }
        data[rhsLength] = '\0';
        refCount = rhs.getRefCount();
    }
    return *this;
}

StringValue StringValue::operator+ (const StringValue& other) {
    std::cout << "  * stringvalue + operator (" << data << " + " << other.data << ")" << std::endl;
    int length = strlen(data);
    int otherLength = strlen(other.getData());
    char* concated = new char[length + otherLength + 1];
    for (int i = 0; i < length; i++) {
        concated[i] = data[i];
    }
    for (int i = 0; i < otherLength; i++) {
        concated[length + i] = other.data[i];
    }
    concated[length + otherLength] = '\0';
    StringValue ret(concated);
    delete[] concated;
    return ret;
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

// mystring defs
MyString::MyString() {
    std::cout << " * mystring noarg ctor" << std::endl;
    value = new StringValue();
}

MyString::MyString(const char* d) {
    std::cout << " * mystring const char ctor (" << d << ")" << std::endl;
    value = new StringValue(d);
}

MyString::MyString(StringValue& sv) {
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
}

MyString::~MyString() {
    std::cout << " * mystring dtor" << std::endl;
    if (value != nullptr) {
        unlinkStringValue();
    }
}

MyString& MyString::operator= (const MyString& rhs) {
    std::cout << " * mystring op= (" << *this << " = " << rhs << ")" << std::endl;
    if (this != &rhs) {
        unlinkStringValue();
        value = rhs.value;
        value->incrementRefCount();
    }
    return *this;
}

MyString& MyString::operator= (MyString && rhs) {
    std::cout << " * mystring move op= (" << *this << " = " << rhs << ")" << std::endl;
    if (this != &rhs) {
        unlinkStringValue();
        value = rhs.value;
        rhs.value = nullptr;
    }
    return *this;
}

MyString& MyString::operator+= (const MyString& other) {
    std::cout << " * mystring += operator (" << *this << " += " << other << ")" << std::endl;
    *this = *this + other;
    return *this;
}

MyString MyString::operator+ (const MyString& other) {
    std::cout << " * mystring + operator (" << *this << " + " << other << ")" << std::endl;
    StringValue concated((*value) + (*other.value));
    return MyString(concated);
}

MyString& MyString::operator+= (const char* c) {
    std::cout << " * mystring += operator with const char* (" << *this << " + " << c << ")" << std::endl;
    *this = *this + c;
    return *this;
}

MyString MyString::operator+ (const char* c) {
    std::cout << " * mystring + operator with const char* (" << *this << " + " << c << ")" << std::endl;
    const char* concated = new char[strlen(value->getData()) + strlen(c) + 1];
    MyString ret(concated);
    delete[] concated;
    return ret;
}

MyString& MyString::operator+= (char c) {
    std::cout << " * mystring += operator with char (" << *this << " + " << c << ")" << std::endl;
    *this = *this + c;
    return *this;
}

MyString MyString::operator+ (char c) {
    std::cout << " * mystring + operator with char (" << *this << " + " << c << ")" << std::endl;
    int length = getLength();
    char* concated = new char[length + 1 + 1]; // current + 1 char + \0
    for (int i = 0; i < length; i++) {
        concated[i] = (*value)[i];
    }
    concated[length] = c;
    concated[length + 1] = '\0';
    MyString ret(concated);
    delete[] concated;
    return ret;
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

int MyString::getLength() {
    return strlen(value->getData());
}

void MyString::unlinkStringValue() {
    value->decrementRefCount();
    if (value->getRefCount() == 0) {
        delete value;
    }
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
