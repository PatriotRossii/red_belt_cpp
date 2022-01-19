#include "deque.h"

#include <iostream>

using namespace std;

int main() {
	Deque<int> d;

	d.PushBack(7);
	d.PushBack(5);
	d.PushBack(16);
	d.PushBack(8);

	d.PushFront(13);
	d.PushBack(25);

	for(size_t i{}; i != d.Size(); ++i) {
		std::cout << d.At(i) << ' ';
	}
	std::cout << std::endl;

	std::cout << "Front element: " << d.Front() << std::endl;
	std::cout << "Back element: " << d.Back() << std::endl;
	std::cout << "Size: " << d.Size() << std::endl;
}