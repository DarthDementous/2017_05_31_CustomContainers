#include <iostream>

#include "List.hpp"

void main() {
#pragma region List Testing
	List<int> list;
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);

	list.PopBack();
	list.PopBack();
	list.PopBack();

	for (auto i = 0; i < 100; i++) {
		list.PushBack(i);
	}

	for (auto i = 0; i < (int)list.GetSize(); i++) {
		std::cout << list[i] << std::endl;
	}
#pragma endregion
	
	system("pause");
}