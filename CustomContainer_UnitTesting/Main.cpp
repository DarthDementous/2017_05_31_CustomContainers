// Catch library will supply its own main function
#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <List.hpp>

#define STRESS_NUM		1000

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
	}
	system("pause");
}