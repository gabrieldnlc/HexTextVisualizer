#include <string>
#include <vector>

#include "catch.hpp"

#include "DataTraverser.hpp"

using std::string;
using std::vector;
using tables::DataTraverser;

const string tag = "DataTraverser";

SCENARIO("DataTraverser can find the start of data on the vector", tag)
{
	GIVEN("A vector with data and a matching DataTraverser")
	{
		vector<int> data
		{
			1, 2, 3,
			0, 0, 0,
			5, 4, 5,
			0, 0, 0,
			8, 8, 8, 8, 8, 8,
			0, 0, 0,
			5, 5,
			0, 0, 0,
			1
		};
		auto traverser = DataTraverser<int>(0, 3);

		THEN("DataTraversal is accurate to vector's contents")
		{
			auto start = traverser.FindFirstData(data);
			REQUIRE(start == 0);
			auto end = traverser.FindEndOfData(data, start);
			REQUIRE(end == 2);

			start = traverser.FindData(data, end + 1);
			REQUIRE(start == 6);
			end = traverser.FindEndOfData(data, start);
			REQUIRE(end == 8);

			start = traverser.FindData(data, end + 1);
			REQUIRE(start == 12);
			end = traverser.FindEndOfData(data, start);
			REQUIRE(end == 17);

			start = traverser.FindData(data, end + 1);
			REQUIRE(start == 21);
			end = traverser.FindEndOfData(data, start);
			REQUIRE(end == 22);

			start = traverser.FindData(data, end + 1);
			REQUIRE(start == 26);
			end = traverser.FindEndOfData(data, start);
			REQUIRE(end == 26);

			start = traverser.FindData(data, end + 1);
			REQUIRE(start == -1);
			
			
		}
	}
}