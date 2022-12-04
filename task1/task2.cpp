#include "bumpAllocator.hpp"
#include <simpletest.h>

using namespace std;
char const * groups[] = {
    "Bump",
};

// all of the allocations work fine (int)
DEFINE_TEST_G(BumpTest1, Bump){
    BumpAllocator<6*sizeof(int)> bumper; //creating an object of size 24

    int * tmp1 = bumper.alloc<int>(1); //allocating 4 bits
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    int * tmp2 = bumper.alloc<int>(3); // allocation 12 bits
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    int * tmp3 = bumper.alloc<int>(2); // allocating 8 bits
    TEST_MESSAGE(tmp3 != nullptr, "Test passed! Bumper worked!");
}

// all of the allocations work fine (char)
// This test does the same things as before, the only difference is the type
// The test is done using char
DEFINE_TEST_G(BumpTest2, Bump){
    BumpAllocator<6*sizeof(char)> bumper;  //creating an object of size 6

    char * tmp1 = bumper.alloc<char>(1); //allocating 1 bit
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(3); //allocating 3 bits
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    char * tmp3 = bumper.alloc<char>(2); // allocating 2 bits
    TEST_MESSAGE(tmp3 != nullptr, "Test passed! Bumper worked!");
}

// last allocation returns nullptr (int)
DEFINE_TEST_G(BumpTest3, Bump){
    BumpAllocator<6*sizeof(int)> bumper; //creating an object of size 24
    
    int * tmp1 = bumper.alloc<int>(1); //allocating 4 bits
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    int * tmp2 = bumper.alloc<int>(3); // allocation 12 bits
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    // trying to allocating 40 more bits. Since there is no space, the allocation fails
    // and the function alloc will return a nullptr
    int * tmp3 = bumper.alloc<int>(10);
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Bumper worked!");
}

// last allocation returns nullptr (char)
DEFINE_TEST_G(BumpTest4, Bump){
    BumpAllocator<6*sizeof(char)> bumper; //creating an object of size 6
    
    char * tmp1 = bumper.alloc<char>(1); //allocating 1 bit
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(3); //allocating 3 bits
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    // trying to allocating 10 more bits. Since there is no space, the allocation fails
    // and the function alloc will return a nullptr
    char * tmp3 = bumper.alloc<char>(10);
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Failed to allocate!!!!");
}

// trying to reallocate when the allocation_counter is not 0 after deallocation is performed
DEFINE_TEST_G(BumpTest5, Bump){
    BumpAllocator<6*sizeof(char)> bumper; //creating an object of size 24

    char * tmp1 = bumper.alloc<char>(4); //allocating 4 bits
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(2); // allocating 2 bits
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    // trying to allocate 10 bits, but it fails because there is not enough space
    char * tmp3 = bumper.alloc<char>(10); 
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Failed to allocate!!!!");

    // deallocating one of the allocations
    bumper.dealloc(tmp2);

    // trying to allocate a new allocation of size 2, but failing because the allocation haven't been reset yet
    char * tmp4 = bumper.alloc<char>(2);
    TEST_MESSAGE(tmp4 == nullptr, "Test passed! Failed to allocate!!!!");
}

// trying to reallocate when the allocation_counter is not 0 after deallocation is performed
DEFINE_TEST_G(BumpTest6, Bump){
    BumpAllocator<6*sizeof(char)> bumper;
    char * tmp1 = bumper.alloc<char>(5); //allocating 20 bits
    TEST_MESSAGE(tmp1 != nullptr, "Test passed! Bumper worked");

    char * tmp2 = bumper.alloc<char>(1); //allocating 4 bits
    TEST_MESSAGE(tmp2 != nullptr, "Test passed! Bumper worked!");

    // trying to allocate 40 bits, but it fails because there is not enough space
    char * tmp3 = bumper.alloc<char>(10);
    TEST_MESSAGE(tmp3 == nullptr, "Test passed! Failed to allocate!!!!");

    // deallocating one of the allocations
    bumper.dealloc(tmp2);

    // trying to allocate a new allocation of size 4, but failing because the allocation haven't been reset yet
    char * tmp4 = bumper.alloc<char>(1);
    TEST_MESSAGE(tmp4 == nullptr, "Test passed! Failed to allocate!!!!");
}

// deallocating and reallocating values
DEFINE_TEST_G(BumpTest7, Bump){
    BumpAllocator<6*sizeof(char)> bumper; //creating an object of size 24

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
    BumpAllocator<6*sizeof(char)> bumper;
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