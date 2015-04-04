#include <iostream>
#include <utility>
#include "MyString.h"

using namespace std;

int main(int argc, char** argv) {

    cout << "const char ctor" << endl;
    MyString hello = "hello"; // const char* ctor

    cout << "copy ctor" << endl;
    MyString hello2 = hello;  // copy ctor

    cout << "noarg ctor" << endl;
    MyString hello3;

    cout << "=op" << endl;
    hello3 = hello2;

    cout << "move =op" << endl;
    hello3 = "moveOpHello";

    cout << "move ctor" << endl;
    MyString hello4 = std::move(hello3);

    cout << "return" << endl;
    return 0;
}
