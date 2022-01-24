#include <bits/stdc++.h>

using namespace std;

template<typename C, typename K, typename V>
typename C::iterator insertOrIncrease(C& container, const K& key, const V& value) {
	if(auto it = container.find(key); it != container.end()) {
		it->second += value;
		return it;
	} else {
		return container.insert({key, value}).first;
	}

}

class HotelManager {
	unordered_map<string, int> rooms;
	unordered_map<string, map<int, int>> clients;

	map<long long, vector<pair<string, map<int, int>::iterator>>> events;
	void Adjust(long long time) {
		long long lowerBound = time - 86400;

		for(auto it = events.begin(), end = events.end(); it != end; ) {
			if(it->first <= lowerBound) {
				for(auto& [hotelName, clientIterator]: it->second) {
					rooms[hotelName] -= clientIterator->second;
					clients[hotelName].erase(clientIterator);
				}
				it = events.erase(it);
			} else {
				++it;
			}
		}
	}
public:
	void Book(long long time, const string& hotelName, int clientId, int roomCount) {
		Adjust(time);

		rooms[hotelName] += roomCount;
		pair<string, map<int, int>::iterator> clientsNode =
			{hotelName, insertOrIncrease(clients[hotelName], clientId, roomCount)};
		events[time].push_back(clientsNode);
	}
	int CountOfClients(const string& hotel) const {
		if(clients.count(hotel)) {
			return clients.at(hotel).size();
		}
		return 0;
	}
	int CountOfRooms(const string& hotel) const {
		if(rooms.count(hotel)) {
			return rooms.at(hotel);
		}
		return 0;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	HotelManager manager;
	int countOfQueries; cin >> countOfQueries;

	while(countOfQueries--) {
		string command; cin >> command;
		if(command == "BOOK") {
			long long time; cin >> time;
			string hotelName; cin >> hotelName;
			int clientId, roomCount; cin >> clientId >> roomCount;
			manager.Book(time, hotelName, clientId, roomCount);
		} else if(command == "CLIENTS") {
			string hotelName; cin >> hotelName;
			cout << manager.CountOfClients(hotelName) << '\n';
		} else if(command == "ROOMS") {
			string hotelName; cin >> hotelName;
			cout << manager.CountOfRooms(hotelName) << '\n';
		}
	}
}