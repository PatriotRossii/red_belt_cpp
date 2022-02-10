//#include "test_runner.h"
#include "../../common/test_runner.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = pair<int, typename list<T>::iterator>;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
    objects[0].push_back(move(object));
    return {0, --objects[0].end()};
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
    while(range_begin != range_end) {
      *(ids_begin++) = Add(move(*(range_begin++)));
    }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
    if(objects.count(id.first)) {
        const list<T>& cluster = objects[id.first];
        return id.second >= cluster.begin() && id.second <= cluster.end();
    }
    return false;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
    return *(id.second);
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
    objects[id.first + 1].push_back(move(*(id.second)));
    objects[id.first].erase(id.second);
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
    return {objects.begin()->second.front(), objects.begin()->first};
  }

  pair<T, int> PopMax() {
    T value = std::move(objects.begin()->second.front());
    int priority = objects.begin()->first;

    objects.begin()->second.erase(objects.begin()->second.begin());
    return {move(value), priority};
  }
private:
  map<int, list<T>, std::greater<int>> objects;
};

// Set of pointers to clusters of objects with same priorities: set<Wrapper<int, vector<list<T>>::iterator>> priorities
// vector<list<T>> objects;

class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
