//#include "test_runner.h"
#include "../../common/test_runner.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
private:
  struct PriorityObject {
    T object;
    mutable int priority;
    bool operator<(const PriorityObject& rhs) const {
      return std::tie(this->priority, this->object) > std::tie(rhs.priority, rhs.object);
    }
  };
public:
  using Id = typename set<PriorityObject>::iterator;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
    auto [iterator, _] = queue.insert(PriorityObject{std::move(object), 0});
    return iterator;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
    while(range_begin != range_end) {
      *(ids_begin++) = *(range_begin++);
    }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
    return id >= queue.begin() && id < queue.end();
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
    return id->object;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
    id->priority = 1;
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
    const PriorityObject& min_priority = queue.front();
    return {min_priority.object, min_priority.priority};
  }

  pair<T, int> PopMax() {
    PriorityObject min_priority = move(queue.extract(queue.begin()).value());
    queue.erase(queue.begin());
    return {move(min_priority.object), move(min_priority.priority)};
  }
private:
  set<PriorityObject> queue;
};


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
