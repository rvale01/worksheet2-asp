# Part 1
In the folder "task1", there are all the files of task 1 and task 2. 

<h3>Task 1</h3>
The bumpAllocator.hpp contains a class which implements the BumpAllocator. The class contains four attributes: 
<ul>
    <li>pointer to the next available location</li>
    <li>a counter which counts how many successfull allocation were made</li>
    <li>heap which stores the value</li>
    <li>total size available</li>
</ul>

<br/>

The attributes are private. While public, there are a few functions and the constructor.

The constructor sets the allocation couter to 0, initialises the heap and sets the next pointer equal to the start address of the heap, and it calculetes the total size.

The other functions available are the alloc function, the dealloc function and the reset. 

The allocation function allocs a new value to the heap. It uses the std::align function, which, given the available space, and how much space is needed, it returns either a nullptr (if there is not enough space) or the new position of the pointer. If the std::align returns a pointer, then the allocation counter is increased, the new position of the pointer is set, and the total size is updated.

The delloc function just decreases the allocation counter everytime itis called, and,if the allocation counter is 0, it calls the reset function.

The reset function just resets everything to the initial values.
To run task 1 this is the command:
<code>clang++ -o task1 task1.cpp</code>

<h3>Task 2</h3>
Task 2 includes testing. In order to do that, an external repo was added to the project. A total of 8 tests were written, 4 for chars and 4 for integers.
The tests written are:
<ul>
    <li>where all the allocations work fine</li>
    <li>last allocation returns nullptr because there is not enough space</li>
    <li>trying to reallocate when the allocation_counter is not 0 after deallocation is performed</li>
    <li>deallocating and reallocating values without errors</li>
</ul>

To run task 2 this is the command:
<code>clang++ -std=c++17 -I./simpletest -o task2 task2.cpp simpletest/simpletest.cpp</code>