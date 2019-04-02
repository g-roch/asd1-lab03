//
//  CountingSort.h
//

#ifndef CountingSort_h
#define CountingSort_h

#include <vector>
#include <algorithm>
#include <type_traits>

#include <iostream>
using namespace std;

namespace asd1 {

   /**
     Tri comptage générique

https://en.wikipedia.org/wiki/Counting_sort

@param first  [first,last] est la plage d'éléments d'un tableau à trier.
@param last   [first,last] est la plage d'éléments d'un tableau à trier.
@param output début du tableau où écrire le résultat. Doit être différent
du tableau d'entrée
@param key fonction prenant un élément en entrée et retourant sa position
dans le tableau de comptage
@param max_key valeur maximale pouvant être retournée par key(...). Si -1,
la fonction calcule cette valeur en parcourant le tableau une
fois de plus
*/
   template<typename RandomAccessIterator, typename Fn>
      void CountingSort(RandomAccessIterator first,
            RandomAccessIterator last,
            RandomAccessIterator output,
            Fn key,
            size_t max_key = (size_t) -1)
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

         //for(auto it = first; it != last; ++it)
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
   void RadixSort(std::vector<unsigned int>& v)
   {
      std::vector<unsigned int> m(v.size());

      for(int j = 0; j < 4; ++j)
      {
        CountingSort(v.begin(), v.end(), m.begin(), [j](unsigned int i) { return (i >> (8*j)) & 255  ; }, 255);
        swap(m, v);
      }
      
      // a compléter
   }
}

#endif /* CountingSort_h */
