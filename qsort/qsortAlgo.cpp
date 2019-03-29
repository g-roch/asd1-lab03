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

