#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ReadingManager {
public:
  ReadingManager() { }

  void Read(int user_id, int page_count) {
  	if(auto it = userToPage.find(user_id); it != userToPage.end()) {
  		pageToUser[it->second].erase(user_id);
  	}
  	userToPage[user_id] = page_count;
  	pageToUser[page_count].insert(user_id);
  }

  double Cheer(int user_id) const {
  	if(userToPage.find(user_id) == userToPage.end()) {
  		return 0;
  	}
  	if(userToPage.size() == 1) {
  		return 1;
  	}

  	int currentUserPage = userToPage.at(user_id);
  	int total = 0;

  	for(auto it = pageToUser.begin(), end = (--pageToUser.upper_bound(currentUserPage)); it != end; ++it) {
  		total += it->second.size();
  	}
  	return static_cast<double>(total) / (userToPage.size() - 1);
  }

private:
  static const int MAX_USER_COUNT_ = 100'000;
  map<int, unordered_set<int>> pageToUser;
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
      cout << setprecision(6) << manager.Cheer(user_id) << std::endl;
    }
  }

  return 0;
}