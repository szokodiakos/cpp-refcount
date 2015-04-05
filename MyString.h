#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class StringValue {
private:
    char *data;
    int refCount;
public:
    StringValue();
    StringValue(const StringValue&);
    StringValue(const char*);

    ~StringValue();

    StringValue& operator= (const StringValue&);
    StringValue operator+ (const StringValue&);
    char& operator[] (int);

    int getRefCount() const;
    char* getData() const;
    void incrementRefCount();
    void decrementRefCount();
};

class MyString {
private:
    StringValue *value;
public:
    MyString();
    MyString(const char*);
    MyString(StringValue&);
    MyString(const MyString&);
    MyString(MyString &&);

    ~MyString();

    MyString& operator= (const MyString&);
    MyString& operator= (MyString &&);

    MyString& operator+= (const MyString&);
    MyString operator+ (const MyString&);

    MyString& operator+= (const char*);
    MyString operator+ (const char*);

    MyString& operator+= (char);
    MyString operator+ (char);

    char& operator[] (int);
    const char& operator[] (int) const;

    StringValue* getValue();
    int getLength();
    void unlinkStringValue();
    friend std::ostream& operator << (std::ostream&, const MyString&);
};

#endif // MYSTRING_H
