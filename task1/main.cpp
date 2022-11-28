#include "bumpAllocator.hpp"

int main() {

    BumpAllocator<6*sizeof(int)> allocator;

    // allocate objects of different sizes and the use of the allocated memory TODO: ask last part
    int * tmp = allocator.alloc<int>(3);
    int * tmp2 = allocator.alloc<int>(2);

    // allocate fails, returning nullptr, when not enough memory
    int * tmp3 = allocator.alloc(3);

    // allocator resets when deallocations matches the number of (successful) allocation
    allocator.dealloc(tmp2);
    allocator.dealloc(tmp);
}

// TODO: what tests should be included?