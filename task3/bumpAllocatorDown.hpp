#include <iostream>
#include <cstring>
#include <memory>
using namespace std;

template <int Size>
class BumpAllocatorDown {
    private:
        void* p_next; //pointer to the next available location
        int allocation_counter;
        char* heap;
        std::size_t tot_size;

    public:
    BumpAllocatorDown(){
        allocation_counter = 0;
        heap = new char[Size];
        p_next = (void*)&heap[Size - 1];// equal to the end address of the heap 
        tot_size =  (std::size_t)((char*)p_next - (heap - Size));
    }
    
    // use template
    template<typename T>
    T* alloc (T num){
        std::cout << tot_size << ("This is working fine!") << std::endl;

        if (std::align(alignof(T), sizeof(T)*num, p_next, tot_size)) {
            allocation_counter++;
            p_next = (char*)p_next - sizeof(T)*num;
            tot_size -= sizeof(T)*num;
            return (T*)p_next;
        }
        return nullptr;
    }


    void reset(){
        p_next = (void*) &heap[Size];
        tot_size =  (std::size_t)((char*)p_next - (heap - Size));
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
