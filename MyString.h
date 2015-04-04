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
    StringValue operator+ (const StringValue&);
    char& operator[] (int);
    int getRefCount() const;
    int getSize() const;
    char* getData() const;
    void incrementRefCount();
};

class MyString {
private:
    StringValue *value;
public:
    MyString();
    MyString(const char*);
    MyString(StringValue);
    MyString(const MyString&);
    MyString(MyString &&);
    ~MyString();
    MyString& operator= (const MyString&);
    MyString& operator= (MyString &&);
    MyString& operator+= (MyString&);
    MyString operator+ (const MyString&);
    char& operator[] (int);
    const char& operator[] (int) const;
    StringValue* getValue();
    int getLength();
    friend std::ostream& operator << (std::ostream&, const MyString&);
};

#endif // MYSTRING_H
