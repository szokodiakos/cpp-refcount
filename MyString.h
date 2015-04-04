#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class StringValue {
private:
    int size;
    char *data;
    int refCount;
public:
    StringValue();
    StringValue(const char*);
    ~StringValue();
    int getRefCount();
    char* getData();
    void incrementRefCount();
};

class MyString {
private:
    StringValue *value;
public:
    MyString();
    MyString(const char*);
    MyString(const MyString&);
    ~MyString();
    MyString& operator= (const MyString&);
    StringValue* getValue();
    friend std::ostream& operator << (std::ostream&, const MyString&);
};

#endif // MYSTRING_H
