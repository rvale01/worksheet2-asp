#include <iostream>
#include <thread>
#include "benchmark.hpp"

// prototype of function we want to benchmark
int some_function(int a, int b){
    return a + b;
};

int main(){
    benchmark(some_function, 1, 3);
};