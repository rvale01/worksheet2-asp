#include "bumpAllocator.hpp"

int main() {

    // creating an object with size 24 (6*4)
    BumpAllocator<6*sizeof(int)> allocator;

    // allocate objects of different sizes and the use of the allocated memory
    int * tmp = allocator.alloc<int>(1);
    int * tmp2 = allocator.alloc<int>(3);

    // allocate fails, returning nullptr, when not enough memory
    if(allocator.alloc(3) == nullptr){
        std::cout << ("This is working fine!") << std::endl;
    }

    // allocator resets of one allocation
    allocator.dealloc(tmp2);

    // all the allocations haven't been reset and sice there is no space left, the next allocation fails
    if(allocator.alloc<int>(1) == nullptr){
        std::cout << ("This is working fine!") << std::endl;
    }

    // allocator resets to the beginning when deallocations matches the number of (successful) allocation
    allocator.dealloc(tmp);
}