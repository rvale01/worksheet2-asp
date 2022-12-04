#include <iostream>
#include <cstring>
using namespace std;

template <int Size>
class BumpAllocator {
    private:
        char* p_next; //pointer to the next available location
        int allocation_counter;
        char* heap;

    public:
    BumpAllocator(){
        allocation_counter = 0;
        heap = new char[Size];
        p_next = heap;// equal to the start address of the heap 
    }
    
    // use template
    template<typename T>
    int* alloc (T num){
        // if there is enough space
        //temp = p_next + sizeof(T)*num
        // std::align -> check online
        if(p_next + sizeof(T)*num <= (heap + Size)){
            allocation_counter++;
            //heap[p_next + sizeof(data)] = data;
            p_next = heap + sizeof(T)*num;

            return *p_next;
        }
        return nullptr;
    }


    void reset(){
        p_next = heap;
    }

    // alloc () -> should not have static data type
    // check if there is enough space check must account fo alignment
    // if not return nullptr
    // otherwise
    // align head_ to templatetemp = current head (alignment)
    // adjust hrad to account fo allocation
    // return tmp

    // dealloc() -> should not have static data type
    template<typename T>
    void dealloc(T * tmp){
        allocation_counter--;
        if(allocation_counter == 0){
            //In this case, the next pointer can be
            // reset to the start address of the heap
            reset();
        }
    }
};
