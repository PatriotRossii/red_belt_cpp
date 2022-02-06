#include "test_runner.h"

#include <string>
#include <vector>
#include <string_view>
#include <unordered_map>
#include <utility>

using namespace std;

class Translator {
public:
  Translator() { }

  void Add(string_view source, string_view target) {
    auto sourceIt = sources.insert(string(source));
    auto targetIt = targets.insert(string(target));
    
    source = *sourceIt.first;
    target = *targetIt.first;

    forward[source] = target;
    backward[target] = source;
  }
  string_view TranslateForward(string_view source) const {
    if(forward.count(source) == 0) return "";
    return forward.at(source);
  }
  string_view TranslateBackward(string_view target) const {
    if(backward.count(target) == 0) return "";
    return backward.at(target);
  }
private:
  set<string> sources;
  set<string> targets;

  unordered_map<string_view, string_view> forward;
  unordered_map<string_view, string_view> backward;
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}