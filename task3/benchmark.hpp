#include <chrono>
/* Only needed for the sake of this example. */
#include <iostream>
#include <thread>

class Benchmark {
    private: 
        std::chrono::_V2::system_clock::time_point t1;
        std::chrono::_V2::system_clock::time_point t2;

    public: 
        Benchmark(){
            using std::chrono::high_resolution_clock;
            t2 = high_resolution_clock::now();
            t1 = high_resolution_clock::now();
        }

        void start() {
            using std::chrono::high_resolution_clock;
            t1 = high_resolution_clock::now();
        }

        void end(){
            using std::chrono::high_resolution_clock;
            t2 = high_resolution_clock::now();
        }

        double get_time(){
            using std::chrono::duration;
            using std::chrono::milliseconds;
            using std::chrono::duration_cast;

            duration<double, std::milli> ms_double = t2 - t1;
            return ms_double.count();
        }
    
};