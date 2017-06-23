// Catch library will supply its own main function
#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include <List.hpp>
#include <Stack.hpp>
#include <Queue.hpp>
#include <LinkedList.hpp>
#include <Map.hpp>

#include <string>

#define STRESS_NUM		20

int main() {
	int result = Catch::Session().run();

	system("pause");

	return (result < 0xff ? result : 0xff);
}

//			Description					Label
TEST_CASE("Testing Custom Containers", "[CONTAINERS]") {
	// REQUIRE break execution if assertion fails
	// CHECK   will execute but flags an error if assertion fails (helps pinpointing multiple errors later)

	SECTION("LIST") {
		List<const char*>	str_list;
		
		REQUIRE(str_list.IsEmpty());

		str_list.PushBack("String_1");
		str_list.PushBack("String_2");
		REQUIRE(str_list[0] == "String_1");
		REQUIRE(str_list[1] == "String_2");
		
		REQUIRE(!str_list.IsEmpty());

		str_list.PopBack();
		REQUIRE(str_list.GetSize() == 1);
		str_list.PushBack("String_2");
		REQUIRE(str_list[1] == "String_2");

		str_list.PopBack();
		str_list.PopBack();
		REQUIRE(str_list.IsEmpty());

		///Strain Testing
		List<int>			int_list;

		for (auto i = 0; i < STRESS_NUM; ++i) {
			int_list.PushBack(i);
			REQUIRE(int_list[i] == i);
		}

		REQUIRE(int_list.GetSize() == STRESS_NUM);

		/// Deep copy testing
		List<int>			int_list_copy = int_list;
		List<int>			int_list_copy2(int_list);

		// Make sure values are identical
		for (auto i = 0; i < STRESS_NUM; ++i) {
			REQUIRE(int_list_copy2[i] == int_list[i]);
		}

		for (auto i = 0; i < STRESS_NUM; ++i) {
			// Remove from copy and ensure original is not affected
			int_list_copy.PopBack();
			REQUIRE(int_list[i] == i);
		}
	}

	SECTION("STACK") {
		Stack<const char*>	str_stk;

		REQUIRE(str_stk.IsEmpty());

		str_stk.PushBack("String_1");
		str_stk.PushBack("String_2");
		REQUIRE(str_stk.Top() == "String_2");

		REQUIRE(!str_stk.IsEmpty());

		str_stk.PopBack();
		REQUIRE(str_stk.GetSize() == 1);
		str_stk.PushBack("String_2");
		REQUIRE(str_stk.Top() == "String_2");

		str_stk.PopBack();
		str_stk.PopBack();
		REQUIRE(str_stk.IsEmpty());

		// Test contains function
		str_stk.PushBack("Found_Item");
		REQUIRE(str_stk.Contains("Found_Item"));

		///Strain Testing
		Stack<int>			int_stk;

		for (auto i = 0; i < STRESS_NUM; ++i) {
			int_stk.PushBack(i);
			REQUIRE(int_stk.Top() == i);
		}

		REQUIRE(int_stk.GetSize() == STRESS_NUM);
	}

	SECTION("QUEUE") {
		Queue<const char*> str_queue;

		REQUIRE(str_queue.IsEmpty());

		str_queue.PushBack("String_1");
		str_queue.PushBack("String_2");
		REQUIRE(str_queue.Top() == "String_1");

		REQUIRE(!str_queue.IsEmpty());

		str_queue.PopBack();
		REQUIRE(str_queue.GetSize() == 1);
		str_queue.PushBack("String_1");
		REQUIRE(str_queue.Top() == "String_2");

		str_queue.PopBack();
		str_queue.PopBack();								// Pop back with only one element remaining
		REQUIRE(str_queue.IsEmpty());

		///Strain Testing
		Queue<int>			int_queue;

		for (auto i = 0; i < STRESS_NUM; ++i) {
			int_queue.PushBack(i);
			REQUIRE(int_queue.Top() == 0);					// Affirm that the first item pushed back is the first out of the queue
		}

		REQUIRE(int_queue.GetSize() == STRESS_NUM);
	}

	SECTION("DOUBLE_LINKED_LIST") {
		LinkedList<int> int_linklist;

		// Push to back
		for (int i = 0; i < STRESS_NUM; i++) {
			int_linklist.PushBack(i);
		}

		// Cycle forwards
		int count = 0;
		for (auto val : int_linklist) {
			REQUIRE(val == count);
			count++;
		}

		// Clear with erase range
		int_linklist.Erase(int_linklist.begin(), int_linklist.end());
		REQUIRE(int_linklist.IsEmpty());

		// Push to front
		for (int i = 0; i < STRESS_NUM; i++) {
			int_linklist.PushFront(i);
		}

		// Cycle forwards
		count = STRESS_NUM - 1;
		for (auto val : int_linklist) {
			REQUIRE(val == count);
			count--;
		}

		// Clear with pop back
		for (auto i = 0; i < STRESS_NUM; ++i) {
			int_linklist.PopBack();
		}

		REQUIRE(int_linklist.IsEmpty());

		// Fill list again
		for (int i = 0; i < STRESS_NUM; i++) {
			int_linklist.PushBack(i);
		}

		/// Deep copy testing
		LinkedList<int>			int_linklist_copy	= int_linklist;
		LinkedList<int>			int_linklist_copy2(int_linklist);

		count = 0;
		
		// Loop through original, remove from copy, and ensure original is not affected.
		for (auto val : int_linklist) {
			int_linklist_copy.PopBack();
			REQUIRE(val == count);
			++count;
		}

		// Clear with pop front
		for (auto i = 0; i < STRESS_NUM; ++i) {
			int_linklist.PopFront();
		}

		REQUIRE(int_linklist.GetSize() == 0);
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