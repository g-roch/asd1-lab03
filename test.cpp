
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <chrono>

#include <utility>
#include <algorithm>

template < typename RandomAccessIterator >
void display( const RandomAccessIterator,
             const RandomAccessIterator,
             const RandomAccessIterator,
             const RandomAccessIterator) {
}
template < typename RandomAccessIterator >
void display( const RandomAccessIterator,
             const RandomAccessIterator,
             const RandomAccessIterator) { }

#include "select/selectAlgo.cpp"
#include "qsort/qsortAlgo.cpp"
#include "CountingSort/CountingSort.h"

#define VAL_MAX 100



using namespace std;
using namespace std::chrono;

class MyTimer
{
    public:
        MyTimer() : t(high_resolution_clock::now()) { }
        void start() { t = high_resolution_clock::now(); }
        double stop() { return duration_cast<nanoseconds>(high_resolution_clock::now() - t).count(); }
    private:
        high_resolution_clock::time_point t;
};

template <typename T>
ostream& operator << (ostream& os, const vector<T>& vect)
{
    for(size_t i = 0; i < 10 and i < vect.size(); ++i)
    {
        if(i) os << ", ";
        os << vect[i];
    }
    return os << endl;

}

template <typename T>
void inittab(vector<T>& vect, T max = VAL_MAX)
{
    for(auto& i : vect) i = rand()%max;
}



int main()
{
    srand((unsigned) time(nullptr));

    //for(size_t size = 1; size <= 16384; size *= 2)
    //{
    //    vector<unsigned> vect(size);
    //    inittab(vect);
    //    cout << "Tri de " << size << " valeur : ";
    //    MyTimer t;
    //    selectionSort(vect.begin(), vect.end());
    //    cout << fixed << t.stop() << " ns" << endl;
    //}

    //for(size_t size = 1; size <= 4194304; size *= 2)
    //{
    //    vector<unsigned> vect(size);
    //    inittab(vect);
    //    cout << "Tri de " << size << " valeur : ";
    //    MyTimer t;
    //    quickSort(vect.begin(), vect.end());
    //    cout << fixed << t.stop() << " ns" << endl;
    //}

    for(size_t size = 1; size <= 8388608; size *= 2)
    {
        vector<unsigned> vect(size);
        inittab(vect);
        cout << "Tri de " << size << " valeur : ";
        MyTimer t;
        asd1::RadixSort(vect);
        cout << fixed << t.stop() << " ns" << endl;
    }


    return 0;
}
