#include <iostream>
#include <thread>
#include "benchmark.hpp"
#include "bumpAllocatorUp.hpp"
#include "bumpAllocatorDown.hpp"

int main(){
    // creating an object of the bump allocator up
    BumpAllocatorUp<6*sizeof(int)> allocator1;
    Benchmark bm;

    // calling the start function of the benchmark
    bm.start();
    // calling some alloc functions
    allocator1.alloc(4);
    allocator1.alloc(2);
    allocator1.alloc(1);
    // calling the end function of the benchmark;
    bm.end();
    // saving the total time of the bump allocator down
    double up_time = bm.get_time();


    // doing the same thing as before with the bump allocator up
    BumpAllocatorDown<6*sizeof(int)> allocator2;
    bm.start();
    allocator2.alloc(4);
    allocator2.alloc(2);
    allocator2.alloc(1);
    bm.end();
    double down_time = bm.get_time();

    // printing both times
    std::cout << " Allocator up: " << up_time << "ms\n";
    std::cout << " Allocator up: " << down_time << "ms\n";
};