#include "LinkedList.h"
#include "Stack.h"
#include "vector.h"
#include <iostream>
#include "Porque.h"

int main(int argc, char** argv) {
	
	LinkedList<TestThing*> test;

	test.push_back(new TestThing());
	test.push_back(new TestThing());
	test.push_back(new TestThing());



	system("pause");
	return 0x0;
}