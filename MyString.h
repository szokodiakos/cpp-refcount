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
    char& operator[] (int);
    int getRefCount();
    int getSize();
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
    MyString(MyString &&);
    ~MyString();
    MyString& operator= (const MyString&);
    MyString& operator= (MyString &&);
    char& operator[] (int);
    const char& operator[] (int) const;
    StringValue* getValue();
    friend std::ostream& operator << (std::ostream&, const MyString&);
};

#endif // MYSTRING_H
