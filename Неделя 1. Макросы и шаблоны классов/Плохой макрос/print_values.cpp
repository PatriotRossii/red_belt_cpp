#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) {                 \
  std::ostream& adsolqwei1 = (out);               \
  const auto& asd2389 = (x);                      \
  const auto& asdilj18 = (y);                     \
	adsolqwei1 << asd2389 << std::endl << asdilj18 << std::endl;  \
}

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");

  if(true) {
    PRINT_VALUES(std::cout, 10, "MY FIRST TEST")
  } else {
    PRINT_VALUES(std::cout, 10, "MY FIRST TEST AGAIN")
  }

  if(true)
    PRINT_VALUES(std::cout, 10, "MY SECOND TEST")
  else
    PRINT_VALUES(std::cout, 10, "MY SECOND TEST AGAIN")

  return 0;
}