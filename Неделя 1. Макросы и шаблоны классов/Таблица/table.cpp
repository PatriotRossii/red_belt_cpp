#include "test_runner.h"

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
class Table {
  vector<vector<T>> table;
  size_t rows, columns;

  void updateSize(size_t newRows, size_t newColumns) {
    bool isZero = (newRows == 0) || (newColumns == 0);
    this->rows = isZero ? 0 : newRows;
    this->columns = isZero ? 0 : newColumns;

    table.resize(this->rows);
    for(auto& row: table) {
      row.resize(newColumns);
    }
  }
public:
  Table(size_t rows, size_t columns) {
    updateSize(rows, columns);
  }

  const vector<T>& operator[](size_t idx) const {
    return table[idx];
  }
  vector<T>& operator[](size_t idx) {
    return table[idx];
  }

  void Resize(size_t newRows, size_t newColumns) {
    updateSize(newRows, newColumns);
  }

  pair<size_t, size_t> Size() const {
    return {rows, columns};
  }
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
