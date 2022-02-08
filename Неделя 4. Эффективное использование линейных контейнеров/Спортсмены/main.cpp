#include <list>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin >> n;

	list<int> row;
	vector<list<int>::iterator> positions(100'000 + 1, row.end());

	while(n--) {
		int currentNumber; int numberNext;
		cin >> currentNumber >> numberNext;
		positions[currentNumber] = row.insert(positions[numberNext], currentNumber);
	}

	for(auto it = row.begin(), end = row.end(); it != end; ++it) {
		cout << *it << '\n';
	}
}