#include <iostream>
#include <cstring>
#include <memory>
using namespace std;

template <int Size>
class BumpAllocatorUp {
    private:
        void* p_next; //pointer to the next available location
        int allocation_counter; // it counts how many successfull allocation were made
        char* heap; //heap which stores the value
        std::size_t tot_size; // total size available

    public:
    BumpAllocatorUp(){
        allocation_counter = 0; //setting the counter to 0
        heap = new char[Size]; // initialising the heap
        p_next = (void*)heap;// equal to the start address of the heap 
        // calculating the tot size
        tot_size =  (std::size_t)Size;
    }
    

    template<typename T>
    T* alloc (T num){
        //using the std::align to check if the space available is enough.
        // If it is enough...
        if (std::align(alignof(T), sizeof(T)*num, p_next, tot_size)) {
            // ...the allocation counter is increased
            allocation_counter++;
            p_next = (char*)p_next + sizeof(T)*num; // the pointer to the next free address is updated
            tot_size -= sizeof(T)*num; // the tot available size is updated
            return (T*)p_next; //and the new pointer is returned
        }
        return nullptr;
    }


    // the reset function just resets all the values as done in the constructor
    void reset(){
        p_next = (void*)heap; //the next pointer is reset to start of the heap
        tot_size =  (std::size_t)((heap + Size) - (char*)p_next); // the tot size is recalculated
    }


    template<typename T>
    void dealloc(T * tmp){
        // decreases the counter by 1
        allocation_counter--;
        if(allocation_counter == 0){ // if the allocation counter is 0
            // everything is reset by calling the reset function
            reset();
        }
    }

};
