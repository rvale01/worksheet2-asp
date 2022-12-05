#include <iostream>
#include <cstring>
#include <memory>
using namespace std;

template <int Size>
class BumpAllocatorDown {
    private:
        void* p_next; //pointer to the next available location
        int allocation_counter; // it counts how many successfull allocation were made
        char* heap; //heap which stores the value
        std::size_t tot_size; // total size available

    public:
    BumpAllocatorDown(){
        allocation_counter = 0; //setting the counter to 0
        heap = new char[Size];  // initialising the heap
        p_next = (void*)(heap+(Size - 1));// equal to the end address of the heap 
        tot_size =  (std::size_t)Size; //setting the total size equal to the size passed to the class
    }
    
    // In this function, the std::align is not used and no alignment is done
    template<typename T>
    T* alloc (T num){

        // the total size available is checked, if it is more or equal to the size needed, the new value is added
        if(tot_size >= sizeof(T)*num){
            allocation_counter++; // ...the allocation counter is increased
            p_next = (char*)p_next - sizeof(T)*num; // the pointer to the next free address is updated
            tot_size -= sizeof(T)*num; // the tot available size is updated
            return (T*)p_next; //and the new pointer is returned
        }

        // otherwise it returns a nullptr
        return nullptr;
    }

    // the reset function just resets all the values as done in the constructor
    void reset(){
        p_next = p_next = (void*)(heap+(Size - 1)); //the next pointer is reset to end of the heap
        tot_size =  (std::size_t)Size; // the tot size is reset to the initial Size
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
