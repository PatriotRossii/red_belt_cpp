template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
  ForwardIterator first, ForwardIterator last, UnaryPredicate predicate);

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
  ForwardIterator first, ForwardIterator last, UnaryPredicate predicate)
{
  ForwardIterator max_element_iterator = last;
  for(; first != last; ++first) {
    if(predicate(*first)) {
      if(max_element_iterator == last || *first > *max_element_iterator) {
        max_element_iterator = first;
      }
    }
  }
  return max_element_iterator;
}

int main() { }