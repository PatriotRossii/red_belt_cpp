#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Deque {
	std::vector<std::pair<size_t, T>> front;
	std::vector<std::pair<size_t, T>> back;
	int currentIdx = 0;
public:
	Deque() { }

	bool Empty() const {
		return front.empty() && back.empty();
	}
	size_t Size() const {
		return front.size() + back.size();
	}

	T& operator[](size_t index) {
		return this->operator[](index);
	}
	const T& operator[](size_t index) const {
		auto it = std::find_if(front.begin(), front.end(), [index](const auto& pair) {
			return pair.first == index;
		});
		if(it != front.end()) {
			return it->second;
		}

		it = std::find_if(back.begin(), back.end(), [index](const auto& pair) {
			return pair.first == index;
		});
		if(it != back.end()) {
			return it->second;
		}
	}

	T& At(size_t index) {
		return this->At(index);
	}
	const T& At(size_t index) const {
		auto it = std::find_if(front.begin(), front.end(), [index](const auto& pair) {
			return pair.first == index;
		});
		if(it != front.end()) {
			return it->second;
		}

		it = std::find_if(back.begin(), back.end(), [index](const auto& pair) {
			return pair.first == index;
		});
		if(it != back.end()) {
			return it->second;
		}

		throw std::out_of_range{"Out of range"};
	}

	T& Front() {
		if(!front.empty()) return front.back();
		return back.front();
	}
	const T& Front() const {
		if(!front.empty()) return front.back();
		return back.front();
	}

	T& Back() {
		if(!back.empty()) return back.back();
		return front.front();
	}
	const T& Back() const {
		if(!back.empty()) return back.back();
		return front.front();
	}

	void PushFront(const T& value) {
		front.push_back({currentIdx++, value});
	}
	void PushBack(const T& value) {
		back.push_back({currentIdx++, value});
	}
};