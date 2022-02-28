#include "test_runner.h"
//#include "../../common/test_runner.h"
#include "profile.h"
//#include "../../common/profile.h"

#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <future>
#include <numeric>
#include <iostream>

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

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return MakePaginator(c.begin(), c.end(), page_size);
}

struct Stats {
  map<string, int> word_frequences;

  auto begin() const {
    return word_frequences.begin();
  }
  auto end() const {
    return word_frequences.end();
  }

  void operator += (const Stats& other) {
    for(const auto& [key, value]: other) {
      word_frequences[key] += value;
    }
  }
};

Stats ExploreKeyWords(const set<string>& key_words, const string& line) {
  Stats statistics;
  istringstream input{line};

  std::string word;
  while(input >> word) {
    if(key_words.count(word) == 1) {
      statistics.word_frequences[word] += 1;
    }
  }

  return statistics;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  Stats statistics;
  vector<future<Stats>> futures;

  vector<string> lines;
  for (string line; getline(input, line);) {
      lines.push_back(move(line));
  }
  for(auto& x: Paginate(lines, 2000)) {
    futures.push_back(
        async([&key_words, x]() -> Stats {
          Stats result;

          for(const auto& line: x) {
            result += ExploreKeyWords(key_words, line);
          }

          return result;
        })
    );
  }

  for(auto& x: futures) {
    statistics += x.get();
  }

  return statistics;
}


void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}