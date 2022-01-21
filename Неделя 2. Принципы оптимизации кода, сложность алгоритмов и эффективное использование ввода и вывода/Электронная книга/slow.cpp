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
  ReadingManager() { }

  void Read(int user_id, int page_count) {
  	if(auto it = userToPage.find(user_id); it != userToPage.end()) {
  		pageToUsercount[it->second] -= 1;
  	}
  	userToPage[user_id] = page_count;
  	pageToUsercount[page_count] += 1;
  }

  double Cheer(int user_id) const {
  	if(userToPage.find(user_id) == userToPage.end()) {
  		return 0;
  	}
  	if(userToPage.size() == 1) {
  		return 1;
  	}

  	return std::accumulate(
  		pageToUsercount.begin(),
  		std::prev(pageToUsercount.upper_bound(userToPage.at(user_id))),
  		0.0, [](const auto& x, const auto& y) { return x + y.second; }
  	) / (userToPage.size() - 1);
  }

private:
  static const int MAX_USER_COUNT_ = 100'000;
  map<int, int> pageToUsercount;
  unordered_map<int, int> userToPage;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

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