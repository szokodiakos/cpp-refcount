#include <iostream>
#include "MyString.h"

using namespace std;

int main(int argc, char** argv) {
    cout << "const char ctor" << endl;
    MyString hello = "hello"; // const char* ctor

    cout << "copy ctor" << endl;
    MyString hello2 = hello;  // copy ctor

    cout << "noarg ctor" << endl;
    MyString hello3;

    cout << "assigment op" << endl;
    hello3 = hello2;

    cout << "return" << endl;
    return 0;
}
