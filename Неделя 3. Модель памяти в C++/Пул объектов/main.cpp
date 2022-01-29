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
      T* object = deallocated.front();

      allocated.insert(object);
      deallocated.pop_front();

      return object;
    }

    T* new_object = new T;
    allocated.insert(new_object);
    return new_object;
  }
  T* TryAllocate() {
    if(deallocated.size()) {
      T* object = deallocated.front();
      
      allocated.insert(object);
      deallocated.pop_front();

      return object;
    }
    return nullptr;
  }
  
  void Deallocate(T* object) {
    if(auto it = allocated.find(object); it == allocated.end()) {
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
  set<T*> allocated;
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