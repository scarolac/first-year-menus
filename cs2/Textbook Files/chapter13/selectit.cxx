template <class ForwardIterator>
void selectionsort(ForwardIterator first, ForwardIterator last)
// Precondition: first and last are ForwardIterators that define a sequence
// of items that can be compared with the < operator.
// Postcondition: The elements of [first..last) have been sorted from
// smallest to largest.
// Library facilities used: algorithm
{
    for (ForwardIterator i = first; i != last; ++i)
    { // Find smallest from [i..last) and swap it with *i.
	ForwardIterator location_of_smallest = i;
	for (ForwardIterator j = i+1; j != last; ++j)
	{
	    if (*j < *location_of_smallest)
		location_of_smallest = j;
	}
        // location_of_smallest is now at the smallest item in [i..last).
	std::iter_swap(i, location_of_smallest);
    }
}
