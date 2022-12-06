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

The constructor sets the allocation couter to 0, initialises the heap and sets the next pointer equal to the start address of the heap, and it sets the total size.

The other functions available are the alloc function, the dealloc function and the reset. 

The allocation function allocs a new value to the heap. It uses the std::align function, which, given the available space, and how much space is needed, it returns either a nullptr (if there is not enough space) or the new position of the pointer. If the std::align returns a pointer, then the allocation counter is increased, the new position of the pointer is set, and the total size is updated.

The delloc function just decreases the allocation counter everytime itis called, and,if the allocation counter is 0, it calls the reset function.

The reset function just resets everything to the initial values.
To run task 1 this is the command:
<code>clang++ -o task1 task1.cpp</code>
<code>./task1</code>

Here is the result in running them:
<br/>
![Alt text](https://gitlab.uwe.ac.uk/v2-ronchi/worksheet2-asp/-/raw/main/task1.png "Task 1")

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
<code>./task2</code>

Here is the result in running them:
<br/>
![Alt text](https://gitlab.uwe.ac.uk/v2-ronchi/worksheet2-asp/-/raw/main/task_2.png "Task 1")


# Part 2
The other folder (task3) has all the files which are needed for task 3. Task included creating a bump down allocator and a benchmark library which could calculate how much time it takes to run a function.

<h3>Bump Down</h3>
The first part is done in the bumpAllocatorDown.hpp. This file contains a class called BumpAllocatorDown. The class has a pointer to the next available location, a counter which counts how many successfull allocation were made, heap which stores the values, and the total size available.

The constructor does a few things similar to the bumpAllocatorUp: it sets the counter to 0, it initialises the heap, it sets the next available pointer equal to the END of the heap (not the start, like in the bumpAllocatorUp) and it sets the total size.

There are three functions in this class: the alloc function, the reset function and dealloc function. Both the reset and the dealloc function do the same things as in the bumpAllocatorUp. The alloc function is a bit different.
In the alloc function, the std::align is not used and no alignment is done. However, it checks the total available size. 
If it is more (or equal) than the size needed, then the counter is increase, the new pointer is calculated and the tot size is updated.
If it is not, then the nullptr is returned

This class is tested in the testing file. It has the same tests used for the bumpAllocatorUp in task 2.

<code>clang++ -std=c++17 -I./simpletest -o testing testing.cpp simpletest/simpletest.cpp</code>
<code>./testing</code>

Here is the result in running them:
<br/>
![Alt text](https://gitlab.uwe.ac.uk/v2-ronchi/worksheet2-asp/-/raw/main/task_3.1.png "Task 1")


<h3>Benchmark</h3>
For the benchmark, a class was created, which contains two attributes: t1 and t2 (the start and end time)

The class contains a constructor, where both t1 and t2 are initialised to time of when the object is created, a start and end function and, finally, a get_time function.
The start function should be called just before the function we want to test. The end function should be called just after the function we want to test.
The get_time function returns returns the difference from t2 to t1 as a double

This class is tested in the main.cpp file, where both the BumpAllocatorUp class and the BumpAllocatorDown are used. Two objects are created (one for the BumpAllocatorDown, one for the BumpAllocatorUp) and a benchmark object.

For each type of bumper, the same amount of allocations are done, and the benchmark is called to calculate how much each sets of allocation takes. At the end, both times are printed, where it can be seen that the bumpDown allocator is faster.

In order to run the benchmark, the following command can be used:
<code>clang++ -o main main.cpp</code>
<code>./main</code>

Here is the result in running them:
<br/>
![Alt text](https://gitlab.uwe.ac.uk/v2-ronchi/worksheet2-asp/-/raw/main/task_3.2.png "Task 1")

