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
    MyString hello3_willBeMoved;

    cout << "=op" << endl;
    hello3_willBeMoved = hello2;

    cout << "move =op" << endl;
    hello3_willBeMoved = "moveOpHello";

    cout << "move ctor" << endl;
    MyString hello4 = std::move(hello3_willBeMoved);

    cout << "indexing operator get" << endl;
    cout << " * should be 'v': " << hello4[2] << endl;

    cout << "indexing operator modify" <<endl;
    hello[4] = 'a';
    cout << " * " << hello << " vs. " << hello2 << endl;

    cout << "indexing operator modify on one refCount stringvalue" << endl;
    hello[4] = 'u';

    cout << "return" << endl;
    return 0;
}
