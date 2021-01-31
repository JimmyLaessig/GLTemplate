#include <catch2/catch.hpp>
#include <Base/UUID2.h>

TEST_CASE("Creating a new UUID")
{
	UUID2 uuid;

	SECTION("A copy of the uuid must equal the uuid")
	{
		UUID2 uuid2(uuid);
		
		REQUIRE(uuid == uuid2);
	}

	SECTION("Create copy with assign operator")
	{
		UUID2 uuid2 = uuid;

		REQUIRE(uuid == uuid2);
		SECTION("Moving a uuid must still obtain the uuid informations")
		{
			auto uuidMoved = std::move(uuid2);

			REQUIRE(uuid == uuidMoved);
		}

		SECTION("This must also be true for the move constructor")
		{
			UUID2 uuidMoved(std::move(uuid2));
			REQUIRE(uuid == uuidMoved);
		}
	}
	

	SECTION("A copy of the uuid must equal the uuid")
	{
		UUID2 uuid2(uuid);
		REQUIRE(uuid == uuid2);
	}

	SECTION("A new uuid must not equal the uuid")
	{
		UUID2 uuid2;
		REQUIRE_FALSE(uuid == uuid2);
	}
}