#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>

using namespace std;

class ReadingManager {
public:
  ReadingManager(): pages(1001, 0), users(100'000 + 1, -1) {  }

  void Read(int user_id, int page_count) {
    for(int i = users[user_id] + 1; i <= page_count; ++i) {
      pages[i] += 1;
    }
    users[user_id] = page_count;
  }

  double Cheer(int user_id) const {
    if(users[user_id] == -1) {
      return 0;
    } else if(pages[0] == 1) {
      return 1;
    }

    return static_cast<double>(pages[0] - pages[users[user_id]])
      / (pages[0] - 1);
  }

private:
  vector<int> pages;
  vector<int> users;
};


int main() {
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << '\n';
    }
  }

  return 0;
}