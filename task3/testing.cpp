#include "bumpAllocatorDown.hpp"
#include <simpletest.h>
using namespace std;
char const * groups[] = {
    "Bump",
};

// all of the allocations work fine (int)
DEFINE_TEST_G(BumpTest1, Bump){
    BumpAllocatorDown<6*sizeof(int)> bumper;
    int * tmp1 = bumper.alloc<int>(1);
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    int * tmp2 = bumper.alloc<int>(3);
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    int * tmp3 = bumper.alloc<int>(2);
    TEST_MESSAGE(tmp3 != nullptr, "Test passed! Bumper worked!");
}

// all of the allocations work fine (char)
DEFINE_TEST_G(BumpTest2, Bump){
    BumpAllocatorDown<6*sizeof(char)> bumper;
    char * tmp1 = bumper.alloc<char>(1);
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(3);
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    char * tmp3 = bumper.alloc<char>(2);
    TEST_MESSAGE(tmp3 != nullptr, "Test passed! Bumper worked!");
}

// last allocation returns nullptr (int)
DEFINE_TEST_G(BumpTest3, Bump){
    BumpAllocatorDown<6*sizeof(int)> bumper;
    int * tmp1 = bumper.alloc<int>(1);
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    int * tmp2 = bumper.alloc<int>(3);
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    int * tmp3 = bumper.alloc<int>(10);
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Bumper worked!");
}

// last allocation returns nullptr (char)
DEFINE_TEST_G(BumpTest4, Bump){
    BumpAllocatorDown<6*sizeof(char)> bumper;

    char * tmp1 = bumper.alloc<char>(1);
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(3);
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    char * tmp3 = bumper.alloc<char>(10);
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Failed to allocate!!!!");
}

// trying to reallocate when the allocation_counter is not 0 and space is full
DEFINE_TEST_G(BumpTest5, Bump){
    BumpAllocatorDown<6*sizeof(char)> bumper;

    char * tmp1 = bumper.alloc<char>(4);
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(2);
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    char * tmp3 = bumper.alloc<char>(10);
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Failed to allocate!!!!");

    bumper.dealloc(tmp2);

    char * tmp4 = bumper.alloc<char>(2);
    TEST_MESSAGE(tmp4 == nullptr, "Test passed! Failed to allocate!!!!");
}

// trying to reallocate when the allocation_counter is not 0 and space is full
DEFINE_TEST_G(BumpTest6, Bump){
    BumpAllocatorDown<6*sizeof(char)> bumper;

    char * tmp1 = bumper.alloc<char>(5);
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(1);
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    char * tmp3 = bumper.alloc<char>(10);
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Failed to allocate!!!!");

    bumper.dealloc(tmp2);

    char * tmp4 = bumper.alloc<char>(1);
    TEST_MESSAGE(tmp4 == nullptr, "Test passed! Failed to allocate!!!!");
}

// deallocating and reallocating values
DEFINE_TEST_G(BumpTest7, Bump){
    BumpAllocatorDown<6*sizeof(char)> bumper; //creating an object of size 24

    char * tmp1 = bumper.alloc<char>(4); //allocating 4 bits
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(2); // allocating 2 bits
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    // trying to allocate 10 bits, but it fails because there is not enough space
    char * tmp3 = bumper.alloc<char>(10); 
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Failed to allocate!!!!");

    // deallocating all of the successful allocations
    bumper.dealloc(tmp2);
    bumper.dealloc(tmp1);

    // allocating a new allocation of size 2
    char * tmp4 = bumper.alloc<char>(2);
    TEST_MESSAGE(tmp4 != nullptr, "Test passed! Failed to allocate!!!!");
}

// deallocating and reallocating values
DEFINE_TEST_G(BumpTest8, Bump){
    BumpAllocatorDown<6*sizeof(char)> bumper;
    char * tmp1 = bumper.alloc<char>(5); //allocating 20 bits
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(1); //allocating 4 bits
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    // trying to allocate 40 bits, but it fails because there is not enough space
    char * tmp3 = bumper.alloc<char>(10);
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Failed to allocate!!!!");

    // deallocating all of the successful allocations
    bumper.dealloc(tmp2);
    bumper.dealloc(tmp1);

    // // allocating a new allocation of size 4
    char * tmp4 = bumper.alloc<char>(1);
    TEST_MESSAGE(tmp4 != nullptr, "Test passed! Failed to allocate!!!!");
}

int main() {
    bool pass = true;
    for (auto group : groups) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }
    return pass ? 0 : 1;
}