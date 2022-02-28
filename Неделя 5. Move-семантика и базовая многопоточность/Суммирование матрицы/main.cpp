//#include "../../common/test_runner.h"
#include "test_runner.h"

#include <vector>
#include <future>
#include <numeric>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename Iterator>
class RangeIterator {
  Iterator first;
  Iterator last;
  size_t size_;
public:
    RangeIterator(Iterator first, Iterator last, size_t size)
      : first(first), last(last), size_(size) { }

    Iterator begin() {
      return first;
    }
    Iterator end() {
      return last;
    }

    Iterator begin() const {
      return first;
    }
    Iterator end() const {
      return last;
    }

    size_t size() const {
      return size_;
    }
};

template <typename Iterator>
class Paginator {
  vector<RangeIterator<Iterator>> pages;
public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for(; begin < end; begin += page_size) {
      auto currentEnd = (begin + page_size) < end ? (begin + page_size) : end;
      pages.emplace_back(begin, currentEnd, currentEnd - begin);
    }
  }

  auto begin() {
    return pages.begin();
  }
  auto end() {
    return pages.end();
  }

  auto begin() const {
    return pages.begin();
  }
  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template<typename Iterator>
Paginator(Iterator, Iterator, size_t) -> Paginator<Iterator>;

template<typename Iterator>
auto MakePaginator(Iterator begin, Iterator end, size_t page_size) {
  return Paginator<Iterator>(begin, end, page_size);
}

template <typename C>
auto Paginate(const C& c, size_t page_size) {
  return MakePaginator(c.begin(), c.end(), page_size);
}


int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  size_t PAGE_SIZE = 2000;
  vector<future<int64_t>> futures;
  for(const auto& page: Paginate(matrix, PAGE_SIZE)) {
    futures.push_back(
      async([page]() -> int64_t {
        int64_t result = 0;
        for(auto it = page.begin(); it != page.end(); ++it) {
          result += accumulate(it->begin(), it->end(), 0);
        }
        return result;
      })
    );
  }

  int64_t result = 0;
  for(auto& x: futures) {
    result += x.get();
  }
  return result;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
