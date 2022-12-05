#include <iostream>
#include <thread>
#include "benchmark.hpp"
#include "bumpAllocatorUp.hpp"
#include "bumpAllocatorDown.hpp"

int main(){
    BumpAllocatorUp<6*sizeof(int)> allocator1;
    Benchmark bm;

    bm.start();
    allocator1.alloc(4);
    allocator1.alloc(2);
    allocator1.alloc(1);
    bm.end();
    double up_time = bm.get_time();


    BumpAllocatorDown<6*sizeof(int)> allocator2;
    bm.start();
    allocator2.alloc(4);
    allocator2.alloc(2);
    allocator2.alloc(1);
    bm.end();
    double down_time = bm.get_time();

    std::cout << " Allocator up: " << up_time << "ms\n";
    std::cout << " Allocator up: " << down_time << "ms\n";
};