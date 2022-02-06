#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin >> n;
	list<int> row;

	while(n--) {
		int currentNumber; int numberNext;
		cin >> currentNumber >> numberNext;

		if(auto it = std::find(row.begin(), row.end(), numberNext); it == row.end()) {
			row.push_back(currentNumber);
		} else {
			row.insert(it, currentNumber);
		}
	}

	for(auto it = row.begin(), end = row.end(); it != end; ++it) {
		cout << *it << '\n';
	}
}