#include <iostream>
#include <utility>
#include "MyString.h"

int reserved = 0;

void * operator new(size_t size) {
    if(size > 1024*1024) throw std::bad_alloc();
    void *res = malloc(size);
    if(res == nullptr) throw std::bad_alloc();
    std::cout << "~~~ allocated " << size << " bytes at " << res << std::endl;
    reserved ++;
    return res;
}

void operator delete(void *p) noexcept {
    free(p);
    std::cout << "~~~ freed memory at " << p << std::endl;
    reserved--;
}

void * operator new[](size_t size) {
    if(size > 1024*1024) throw std::bad_alloc();
    void *res = malloc(size);
    if(res == nullptr) throw std::bad_alloc();
    std::cout << "~~~ allocated " << size << " bytes at " << res << std::endl;
    reserved ++;
    return res;
}

void operator delete[](void *p) noexcept {
    free(p);
    std::cout << "~~~ freed memory at " << p << std::endl;
    reserved--;
}

void check() {
    std::cout << "~~~ Reserved: " << reserved << std::endl;
}

using namespace std;

int main(int argc, char** argv) {

    atexit(check);

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

    cout << "+op concat" << endl;
    MyString hello5 =hello + hello2 ;

    cout << "+=op concat" << endl;
    hello5 += hello;

    cout << "+op concat with char" << endl;
    hello5 = hello + 'x';

    cout << "+=op concat with char" << endl;
    hello5 += 'q';

    cout << "return" << endl;
    return 0;
}
