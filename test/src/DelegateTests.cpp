#include <catch2/catch.hpp>
#include "Application/Delegates.h"
#include "SharedAsset.h"
#include <set>
#include <random>
#include <uuid.h>

TEST_CASE("Subscribing to delegates...")
{
	
	Delegate <std::function<void(int)>> delegate;

	int cbValue0 = 0;
	
	auto disposable1 = delegate.subscribe([&](int value) 
	{
		cbValue0 = value;
	});

	SECTION("Subscribing to a delegate must call the callback function with the correct value passed to the broadcast function")
	{
		delegate.broadcast(1);
		REQUIRE(cbValue0 == 1);
	}

	int cbValue1 = 0;
	auto disposable2 = delegate.subscribe([&](int value)
	{
		cbValue1 = value;
	});

	SECTION("Subscribing a second callback to the delegate must call the callback function for both subscribers")
	{
		delegate.broadcast(2);
		REQUIRE(cbValue0 == 2);
		REQUIRE(cbValue1 == 2);

		SECTION("Unsubscribing a callback must not call the function anymore")
		{
			delegate.unsubscribe(disposable2);
			delegate.broadcast(3);
			REQUIRE(cbValue0 == 3);
			REQUIRE(cbValue1 == 2);
		}
	}


	SECTION("Moving delegates must keep all subscritions...")
	{
		auto delegateMoved = std::move(delegate);

		delegateMoved.broadcast(1);
		REQUIRE(cbValue0 == 1);
		REQUIRE(cbValue1 == 1);

		delegate.broadcast(5);

		REQUIRE(cbValue0 == 1);
		REQUIRE(cbValue1 == 1);
	}
}




TEST_CASE("UUIDGenerator Tests")
{
	//std::string a = "a";
	//auto ptr = a.data();

	
	//std::mt19937_64 gen(seed);
	//auto uuidGen = uuids::uuid_random_generator_

	
	//auto seed_data = std::array<size_t, std::mt19937::state_size> {};
	//std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
	//std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
	//std::mt19937 generator(seq);
	//uuid const guid = uuids::uuid_random_generator{ generator }();



	//UUIDGenerator g;
	//for (int i = 0; i < 1000000;i++)
	//{
	//	g();
	//}
}
