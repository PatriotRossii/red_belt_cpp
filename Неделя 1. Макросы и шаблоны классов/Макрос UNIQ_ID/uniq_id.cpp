#include <string>
#include <vector>

using namespace std;

#define S1(identificator, x) identificator##x
#define S2(identificator, line) S1(identificator, line)
#define UNIQ_ID S2(unique_identificator, __LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}