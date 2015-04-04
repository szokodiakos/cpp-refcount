#ifndef MYSTRING_H
#define MYSTRING_H

class StringValue {
private:
    int size;
    char *data;
    int refCount;
public:
    StringValue();
    StringValue(const char*);
    ~StringValue();
};

class MyString {
private:
    StringValue *value;
public:
    MyString(const char*);
    ~MyString();
};

#endif // MYSTRING_H
