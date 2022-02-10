#include "test_runner.h"
//#include "../../common/test_runner.h"

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

	vector<typename RandomIt::value_type> firstPart{
		make_move_iterator(begin),
		make_move_iterator(next(begin, length / 3))
	};
	vector<typename RandomIt::value_type> secondPart{
		make_move_iterator(next(begin, length / 3)),
		make_move_iterator(next(begin, length / 3 * 2))
	};
	vector<typename RandomIt::value_type> thirdPart{
		make_move_iterator(next(begin, length / 3 * 2)),
		make_move_iterator(end)
	};

	MergeSort(firstPart.begin(), firstPart.end());
	MergeSort(secondPart.begin(), secondPart.end());
	MergeSort(thirdPart.begin(), thirdPart.end());

	vector<typename RandomIt::value_type> temporaryVector;
	merge(
		make_move_iterator(firstPart.begin()), make_move_iterator(firstPart.end()),
		make_move_iterator(secondPart.begin()), make_move_iterator(secondPart.end()),
		back_inserter(temporaryVector)
	);
	merge(
		make_move_iterator(temporaryVector.begin()), make_move_iterator(temporaryVector.end()),
		make_move_iterator(thirdPart.begin()), make_move_iterator(thirdPart.end()),
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
