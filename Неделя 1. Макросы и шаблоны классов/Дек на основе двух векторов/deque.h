#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Deque {
	enum class Location {
		FrontVector,
		BackVector
	};

	std::vector<T> front;
	std::vector<T> back;

	Location GetElementLocation(size_t index) const {
		if(index >= front.size()) {
			return Location::BackVector;
		} else {
			return Location::FrontVector;
		}
	}

	size_t GetFrontIndex(size_t index) const {
		return front.size() - 1 - index;
	}
	size_t GetBackIndex(size_t index) const {
		return index - front.size();
	}

	typename std::vector<T>::iterator GetElementIterator(size_t index) {
		size_t targetIndex = 0;
		switch(GetElementLocation(index)) {
			case Location::FrontVector:
				targetIndex = GetFrontIndex(index);
				if(targetIndex >= front.size()) return front.end();
				return front.begin() + targetIndex;
			case Location::BackVector:
				targetIndex = GetBackIndex(index);
				if(targetIndex >= back.size()) return back.end();
				return back.begin() + targetIndex;
		}
	}
	typename std::vector<T>::const_iterator GetElementIterator(size_t index) const {
		size_t targetIndex = 0;
		switch(GetElementLocation(index)) {
			case Location::FrontVector:
				targetIndex = GetFrontIndex(index);
				if(targetIndex >= front.size()) return front.cend();
				return front.cbegin() + targetIndex;
			case Location::BackVector:
				targetIndex = GetBackIndex(index);
				if(targetIndex >= back.size()) return back.cend();
				return back.cbegin() + targetIndex;
		}
	}
public:
	Deque() { }

	bool Empty() const {
		return front.empty() && back.empty();
	}
	size_t Size() const {
		return front.size() + back.size();
	}

	T& operator[](size_t index) {
		return *GetElementIterator(index);
	}
	const T& operator[](size_t index) const {
		return *GetElementIterator(index);
	}

	T& At(size_t index) {
		auto it = GetElementIterator(index);
		if(it == front.end() || it == back.end()) {
			throw std::out_of_range{std::string("Element with index ") + std::to_string(index) + " is out of range"};
		}
		return *it;

	}
	const T& At(size_t index) const {
		auto it = GetElementIterator(index);
		if(it == front.end() || it == back.end()) {
			throw std::out_of_range{std::string("Element with index ") + std::to_string(index) + " is out of range"};
		}
		return *it;
	}

	T& Front() {
		return *GetElementIterator(0);
	}
	const T& Front() const {
		return *GetElementIterator(0);
	}

	T& Back() {
		return *GetElementIterator(Size() - 1);
	}
	const T& Back() const {
		return *GetElementIterator(Size() - 1);
	}

	void PushFront(const T& value) {
		front.push_back(value);
	}
	void PushBack(const T& value) {
		back.push_back(value);
	}
};