#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    if(deallocated.size()) {
      allocated.push_back(deallocated.front());
      deallocated.pop_front();
    } else {
      allocated.push_back(new T);
    }
    return allocated.back();
  }
  T* TryAllocate() {
    if(deallocated.size()) {
      allocated.push_back(deallocated.front());
      deallocated.pop_front();
      return allocated.back();
    }
    return nullptr;
  }
  
  void Deallocate(T* object) {
    if(auto it = find(allocated.begin(), allocated.end(), object); it == allocated.end()) {
      throw invalid_argument{"No such object"};
    } else {
      deallocated.push_back(*it);
      allocated.erase(it);
    }
  }

  ~ObjectPool() {
    for(auto& x: allocated) {
      delete x;
    }
    for(auto& x: deallocated) {
      delete x;
    }
  }
private:
  deque<T*> allocated;
  deque<T*> deallocated;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}