#include <bits/stdc++.h>

using namespace std;

template<typename C, typename K, typename V>
auto insertOrIncrease(C& container, const K& key, const V& value) {
	if(auto it = c.find(key); it != c.end()) {
		it->second += value;
		return it;
	} else {
		return container.insert({key, value});
	}

}

class HotelManager {
	unordered_map<string, int> rooms;
	unordered_map<string, map<int, int>> clients;

	set<long long, unordered_map<string, int>::iterator> roomsEvents;
	set<long long, unordered_map<string, map<int, int>>::iterator> clientsEvents;

	void Adjust(long long time) {
		long long lowerBound = time - 86000;
		for(auto it = roomsEvents.begin(), end = roomsEvents.end(); it != end; ) {
			if(it->first <= lowerBound) {
				it = roomsEvents.erase(it);
			} else {
				++it;
			}
		}
	}
public:
	void Book(long long time, const string& hotelName, int clientId, int roomCount) {
		Adjust();
		roomsEvents.insert(
			time, HotelManager::insertOrIncrease(rooms, hotelName, roomCount)
		);
		clientsEvent.insert(
			time, HotelManager::insertOrIncrease(clients[hotelName], clientId, roomCount)
		);
	}
	void CountOfClients(const string& hotel) const {
		return clients[hotel].size();
	}
	int CountOfRooms(const string& hotel) const {
		return rooms[hotel];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int countOfQueries; cin >> countOfQueries;
	while(countOfQueries--) {
		string command; cin >> command;
		if(command == "BOOK") {
			long long time; cin >> time;
			string hotel_name; cin >> hotel_name;
			int client_id, room_count; cin >> client_id >> room_count;
		} else if(command == "CLIENTS") {
			string hotel_name; cin >> hotel_name;
		} else if(command == "ROOMS") {
			string hotel_name; cin >> hotel_name;
		}
	}
}