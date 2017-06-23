// Catch library will supply its own main function
#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include <List.hpp>
#include <Stack.hpp>
#include <Queue.hpp>
#include <LinkedList.hpp>
#include <Map.hpp>

#include <string>

#define STRESS_NUM		10			// NOTE: For some reason, there can only be 10 std::strings before an exception is thrown.

int main() {
	// Check for memory leaks and print in output with the combined flags of allocating memory and checking if its not being de-allocated
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int result = Catch::Session().run();

	system("pause");

	return (result < 0xff ? result : 0xff);
}

//			Description					Label
TEST_CASE("Testing Custom Containers", "[CONTAINERS]") {
	// REQUIRE break execution if assertion fails
	// CHECK   will execute but flags an error if assertion fails (helps pinpointing multiple errors later)

	SECTION("LIST") {
		List<int>	list;
		
		/// No items in container
		// Empty function
		REQUIRE(list.IsEmpty());

		// GetSize function
		REQUIRE(list.GetSize() == 0);

		// Push back function, subscript operator and top function
		for (auto i = 0; i < STRESS_NUM; ++i) {
			list.PushBack(i);
			REQUIRE(list[i] == i);
		}
		REQUIRE(list.Top() == STRESS_NUM - 1);

		/// Items in container
		// Empty function
		REQUIRE(!list.IsEmpty());

		// GetSize function
		REQUIRE(list.GetSize() == STRESS_NUM);

		// Pop back
		for (auto i = 0; i < STRESS_NUM; ++i) {
			list.PopBack();
		}

		/// Deep copy testing
		for (auto i = 0; i < STRESS_NUM; ++i) {
			list.PushBack(i);
		}

		List<int>			list_copy = list;
		List<int>			list_copy2(list);

		// Check accuracy and independence (pointers in list copy point to their OWN memory)
		for (auto i = 0; i < STRESS_NUM; ++i) {
			list_copy.PopBack();
			REQUIRE(list_copy2[i] == list[i]);
		}
	}


	SECTION("STACK") {
		Stack < std::string > stack;

		/// No items in container
		// Empty function
		REQUIRE(stack.IsEmpty());

		// GetSize function
		REQUIRE(stack.GetSize() == 0);

		// Push back function and top function (end of stack)
		for (auto i = 0; i < STRESS_NUM; ++i) {
			std::string tmp = "String " + std::to_string(i);
			stack.PushBack(tmp);
		}
		std::string tmp = "String " + std::to_string(STRESS_NUM - 1);
		REQUIRE(stack.Top() == tmp);

		/// Items in container
		// Empty function
		REQUIRE(!stack.IsEmpty());

		// GetSize function
		REQUIRE(stack.GetSize() == STRESS_NUM);

		// Contains function
		REQUIRE(stack.Contains("String 0"));
		REQUIRE(!stack.Contains("N/A"));

		// Pop back function and top function (end of container)
		for (auto i = 0; i < STRESS_NUM; ++i) {
			stack.PopBack();
		}
	}


	SECTION("DOUBLE_LINKED_LIST") {
		LinkedList<int> linklist;
		
		/// No items in container
		// Empty function
		REQUIRE(linklist.IsEmpty());

		// GetSize function
		REQUIRE(linklist.GetSize() == 0);

		// Push back function and top function (front of queue)
		for (auto i = 0; i < STRESS_NUM; ++i) {
			linklist.PushBack(i);
		}

		/// Items in container
		// Empty function
		REQUIRE(!linklist.IsEmpty());

		// GetSize function
		REQUIRE(linklist.GetSize() == STRESS_NUM);

		// Pop back and push front function
		for (auto i = 0; i < STRESS_NUM; ++i) {
			linklist.PopBack();
			linklist.PushFront(i);
		}

		// NOTE: Due to PushFront, numbers were added in reverse. STRESS_NUM - 1 is at the start.

		// Cycle forwards
		int count = STRESS_NUM - 1;
		for (auto val : linklist) {
			REQUIRE(val == count);
			count--;
		}

		// Erase functions and ranged-for
		linklist.Erase(linklist.begin());
		for (auto val : linklist) {
			// Ensure erase was successful by checking if value is still in the linked list
			REQUIRE(val != STRESS_NUM - 1);
		}
		linklist.Erase(linklist.begin(), linklist.end());
		for (auto val : linklist) {
			REQUIRE(!("Ranged-for still active despite all nodes in LinkedList being cleared."));
		}
		REQUIRE(linklist.IsEmpty());

		/// Deep copy testing
		for (auto i = 0; i < STRESS_NUM; ++i) {
			linklist.PushBack(i);
		}

		LinkedList<int>			linklist_copy = linklist;
		LinkedList<int>			linklist_copy2(linklist);

		// Loop through original, pop front from copy, and ensure original is not affected.
		count = 0;
		for (auto val : linklist) {
			linklist_copy.PopFront();
			REQUIRE(val == count);
			++count;
		}
	}

	SECTION("QUEUE") {
		Queue<std::string>	queue;

		/// No items in container
		// Empty function
		REQUIRE(queue.IsEmpty());

		// GetSize function
		REQUIRE(queue.GetSize() == 0);

		// Push back function and top function (front of queue)
		for (auto i = 0; i < STRESS_NUM; ++i) {
			std::string tmp = "String " + std::to_string(i);
			queue.PushBack(tmp);

			REQUIRE(queue.Top() == "String 0");
		}

		/// Items in container
		// Empty function
		REQUIRE(!queue.IsEmpty());

		// GetSize function
		REQUIRE(queue.GetSize() == STRESS_NUM);

		// Pop back function
		for (auto i = 0; i < STRESS_NUM; ++i) {
			queue.PopBack();
		}
	}

	SECTION("MAP") {
		Map <int, std::string> planetMap;

		/// Insertion
		planetMap.Insert(new Map<int, std::string>::PairNode(0, "Mercury"));
		REQUIRE(planetMap[0] == "Mercury");

		// Test ignoring of duplicate keys in pairs
		planetMap.Insert(new Map<int, std::string>::PairNode(0, "Earth"));
		REQUIRE(planetMap[0] == "Mercury");

		// Test numerical ordering of keys (smallest to biggest)
		planetMap.Insert(new Map<int, std::string>::PairNode(4, "Mars"));

		// Test adding a key smaller than root
		planetMap.Insert(new Map<int, std::string>::PairNode(-5, "Pluto"));
		REQUIRE(planetMap[-5] == "Pluto");

		// Test finding a node
		REQUIRE(planetMap.findNode(4)->m_val == "Mars");

		// Test subscript operator overload
		planetMap[10] = "Uranus";
		REQUIRE(planetMap.findNode(10)->m_val == "Uranus");

		// Test begin returns first element
		REQUIRE(planetMap.begin().GetKey() == -5);

		/// Stress test
		for (auto i = 0; i < STRESS_NUM; i++) {
			planetMap[i] = "Planet";
			REQUIRE(planetMap.findNode(i)->m_val == "Planet");
		}

		// Insertion after subscript operator
		planetMap.Insert(new Map<int, std::string>::PairNode(20, "Planet"));

		// Test traversal through binary tree
		std::cout << "FIRST TRAVERSAL:" << std::endl;
		for (auto pair : planetMap) {
			std::cout << pair.m_key << std::endl;
		}

		std::cout << std::endl;

		// Make sure binary tree can be traversed multiple times
		std::cout << "SECOND TRAVERSAL:" << std::endl;
		for (auto iter = planetMap.begin(); iter != planetMap.end(); ++iter) {
			std::cout << (*iter).m_key << std::endl;
		}
	}

}