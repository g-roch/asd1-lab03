
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


template < typename RandomAccessIterator >
void selectionSort( RandomAccessIterator begin,
                    RandomAccessIterator end );
template < typename RandomAccessIterator >
RandomAccessIterator selectPivot( const RandomAccessIterator begin,
                                  const RandomAccessIterator end );
template < typename RandomAccessIterator >
RandomAccessIterator partition( RandomAccessIterator begin,
                                RandomAccessIterator end,
                                RandomAccessIterator pivot);
template < typename RandomAccessIterator >
void quickSort( RandomAccessIterator begin,
                RandomAccessIterator end );
template<typename RandomAccessIterator, typename Fn>
void asdCountingSort(RandomAccessIterator first,
                     RandomAccessIterator last,
                     RandomAccessIterator output,
                     Fn key,
                     size_t max_key = (size_t) -1);
void asdRadixSort(std::vector<unsigned int>& v);


#define VAL_MAX 100
#define NBR_BOUCLE_INTERNE 20
#define MAX_VAL 10000
#define NBR_DIFF 10000


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

   for(size_t size = 1; size <= MAX_VAL; size *= 10)
    {
        double sommeTimerSelect =0;
        double sommeTimerQSort  =0;
        double sommeTimerRadix  =0;
        double sommeTimerComptage=0;

        for (size_t i = 0; i < NBR_BOUCLE_INTERNE; ++i) {
            vector<unsigned> vectSelect(size);
            inittab(vectSelect);
            vector<unsigned> vectQSort =vectSelect;
            vector<unsigned> vectRadix =vectSelect;
            vector<unsigned> vectComptage =vectSelect;

            MyTimer t;
            selectionSort(vectSelect.begin(), vectSelect.end());
            sommeTimerSelect +=t.stop();

            MyTimer u;
            quickSort(vectQSort.begin(), vectQSort.end());
            sommeTimerQSort +=u.stop();

            MyTimer v;
            asdRadixSort(vectRadix);
            sommeTimerRadix +=v.stop();
            MyTimer w;
            std::vector<unsigned int> m(vectComptage.size());
            asdCountingSort(vectComptage.begin(), vectComptage.end(), m.begin(), []( unsigned int  i) {;return i; });
            sommeTimerComptage +=w.stop();

        }
        cout << "Tri de : " << size << " valeur : \n";
        cout << "moyenne Select :"<<fixed << sommeTimerSelect/NBR_BOUCLE_INTERNE<< "ns"<<endl;
        cout << "moyenne Qsort :"<<fixed << sommeTimerQSort/NBR_BOUCLE_INTERNE<< "ns"<<endl;
        cout << "moyenne radix :"<<fixed << sommeTimerRadix/NBR_BOUCLE_INTERNE<< "ns"<<endl;
        cout << "moyenne comptage :"<<fixed << sommeTimerComptage/NBR_BOUCLE_INTERNE<< "ns"<<endl;


    }
    //taille de vecteur de 100 000 avec n éléments différents

        double sommeTimerSelect =0;
        double sommeTimerQSort  =0;
        double sommeTimerRadix  =0;
        double sommeTimerComptage  =0;
        for (size_t i = 0; i < NBR_BOUCLE_INTERNE; ++i) {
            vector<unsigned> vectSelect(MAX_VAL);
            inittab(vectSelect,unsigned(NBR_DIFF));
            vector<unsigned> vectQSort =vectSelect;
            vector<unsigned> vectRadix =vectSelect;
            vector<unsigned> vectComptage =vectSelect;

            MyTimer t;
            selectionSort(vectSelect.begin(), vectSelect.end());
            sommeTimerSelect +=t.stop();

            MyTimer u;
            quickSort(vectQSort.begin(), vectQSort.end());
            sommeTimerQSort +=u.stop();

            MyTimer v;
            asdRadixSort(vectRadix);
            sommeTimerRadix +=v.stop();
            MyTimer w;
            std::vector<unsigned int> m(vectComptage.size());
            asdCountingSort(vectComptage.begin(), vectComptage.end(), m.begin(), []( unsigned int  i) {;return i; });
            sommeTimerComptage +=w.stop();
        }
        cout << "Nombre de valeurs : " << MAX_VAL << " nombre de valeurs différentes : " <<NBR_DIFF<< endl;
        cout << "moyenne Select :"<<fixed << sommeTimerSelect/NBR_BOUCLE_INTERNE<< "ns"<<endl;
        cout << "moyenne Qsort :"<<fixed << sommeTimerQSort/NBR_BOUCLE_INTERNE<< "ns"<<endl;
        cout << "moyenne radix :"<<fixed << sommeTimerRadix/NBR_BOUCLE_INTERNE<< "ns"<<endl;
        cout << "moyenne comptage :"<<fixed << sommeTimerComptage/NBR_BOUCLE_INTERNE<< "ns"<<endl;

    return 0;
}
/*
 *
 * SELECT SORT
 *
 */
template < typename RandomAccessIterator >
void selectionSort( RandomAccessIterator begin,
                    RandomAccessIterator end )
{
    auto min = begin;

    for(auto it = begin; it < end-1; ++it)
    {
        min = it;
        for(auto it2 = it+1; it2 < end; ++it2)
            if(*it2 < *min)
                min = it2;

        if(it != min)
            swap(*(it), *min);
        display(begin,it,min,end);
    }
}
/*
 *
 * QUICK SORT
 *
 */
template < typename RandomAccessIterator >
RandomAccessIterator selectPivot( const RandomAccessIterator begin,
                                  const RandomAccessIterator end )
{
    RandomAccessIterator p1 = begin;
    RandomAccessIterator p2 = begin + ( end-begin ) / 2;
    RandomAccessIterator p3 = end-1;

    if(*p1 < *p2) {
        if( *p2 < *p3 ) return p2;
        else if(*p1 < *p3) return p3;
        return p1;
    } else {
        if( *p1 < *p3 ) return p1;
        else if(*p2 < *p3) return p3;
        return p2;
    }
}

template < typename RandomAccessIterator >
RandomAccessIterator partition( RandomAccessIterator begin,
                                RandomAccessIterator end,
                                RandomAccessIterator pivot)
{
    auto i = begin - 1;
    auto j = end - 1;

    while(true)
    {
        do
            ++i;
        while(*i < *pivot);

        do
            --j;
        while(j > begin and *pivot < *j);

        if(i >= j) break;

        swap(*i, *j);
    }
    swap(*i, *pivot);
    return i;
}

template < typename RandomAccessIterator >
void quickSort( RandomAccessIterator begin,
                RandomAccessIterator end )
{

    const auto hi = end-1;

    if(hi <= begin) return;

    auto pivot = selectPivot(begin, end);

    if(pivot != hi) swap(*pivot, *hi);

    auto i = partition(begin, end, hi);

    display( begin, i, end );

    quickSort(begin, i);
    quickSort(i+1, end);

}
template<typename RandomAccessIterator, typename Fn>
void asdCountingSort(RandomAccessIterator first,
                  RandomAccessIterator last,
                  RandomAccessIterator output,
                  Fn key,
                  size_t max_key)
{
    if(max_key == (size_t) -1)
    {
        max_key = 0;
        for(auto it = first; it != last; ++it)
            if(max_key < key(*it)) max_key = key(*it);
    }

    size_t count[max_key+1];
    for(size_t& i : count) i = 0;

    for(auto it = first; it != last; ++it)
        ++count[key(*it)];

    for(size_t i = 1; i <= max_key; ++i)
        count[i] += count[i-1];

    for(size_t& i : count) i--;

    for(auto it = last-1; it != first-1; --it)
    {
        output[count[key(*it)]] = *it;
        --count[key(*it)];
    }
}

/**
  Tri par base d'entiers non signés sur 32 bits mis en oeuvre en appelant
  4 fois le tri comptage en triant successivement par groupe de 8 bits.

https://en.wikipedia.org/wiki/Radix_sort

@param v vecteur à trier, modifié par cette fonction
*/
void asdRadixSort(std::vector<unsigned int>& v)
{
    std::vector<unsigned int> m(v.size());

    for(int j = 0; j < 4; ++j)
    {
        asdCountingSort(v.begin(), v.end(), m.begin(), [j](unsigned int i) { return (i >> (8*j)) & 255  ; }, 255);
        swap(m, v);
    }

}
