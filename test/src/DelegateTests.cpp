#include <catch2/catch.hpp>
#include "Application/Delegates.h"


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


