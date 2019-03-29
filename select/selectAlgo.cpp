
using namespace std;

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


   
    // A COMPLETER

}
