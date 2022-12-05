#include <chrono>
/* Only needed for the sake of this example. */
#include <iostream>
#include <thread>

class Benchmark {
    // in t1 is saved the start time,
    // in t2 is saved the end time.
    private: 
        std::chrono::_V2::system_clock::time_point t1;
        std::chrono::_V2::system_clock::time_point t2;

    public: 
        Benchmark(){
            // both t1 and t2 are initialised to time of when the object is created
            using std::chrono::high_resolution_clock;
            t2 = high_resolution_clock::now();
            t1 = high_resolution_clock::now();
        }

        // the start function should be called before the function we want to test is called
        // in this function, the only thing done is setting the t1 (time of start)
        void start() {
            using std::chrono::high_resolution_clock;
            t1 = high_resolution_clock::now();
        }

        // this function is called after the function we want to test
        // it just sets t2
        void end(){
            using std::chrono::high_resolution_clock;
            t2 = high_resolution_clock::now();
        }

        // this function returns the difference from t2 to t1 as a double
        double get_time(){
            using std::chrono::duration;
            using std::chrono::milliseconds;
            using std::chrono::duration_cast;

            duration<double, std::milli> ms_double = t2 - t1;
            return ms_double.count();
        }
    
};