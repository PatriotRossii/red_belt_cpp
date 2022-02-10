//#include "test_runner.h"
#include "../../common/test_runner.h"

#include <iterator>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	size_t length = distance(range_begin, range_end);
	if(length < 2) {
		return;
	}

	vector<typename RandomIt::value_type> elements{
		make_move_iterator(range_begin),
		make_move_iterator(range_end)
	};

	auto begin = elements.begin();
	auto end = elements.end();

	auto firstPartBegin = begin;
	auto firstPartEnd = next(begin, length / 3);

	auto secondPartBegin = firstPartEnd;
	auto secondPartEnd = next(begin, length / 3 * 2);

	auto thirdPartBegin = secondPartEnd;
	auto thirdPartEnd = end;

	MergeSort(firstPartBegin, firstPartEnd);
	MergeSort(secondPartBegin, secondPartEnd);
	MergeSort(thirdPartBegin, thirdPartEnd);

	vector<typename RandomIt::value_type> temporaryVector;
	merge(
		make_move_iterator(firstPartBegin), make_move_iterator(firstPartEnd),
		make_move_iterator(secondPartBegin), make_move_iterator(secondPartEnd),
		back_inserter(temporaryVector)
	);
	merge(
		make_move_iterator(temporaryVector.begin()), make_move_iterator(temporaryVector.end()),
		make_move_iterator(thirdPartBegin), make_move_iterator(thirdPartEnd),
		range_begin
	);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
