#include <catch2/catch.hpp>
#include <Application/Delegate.h>


TEST_CASE("Creating Delegates")
{
	int changeValue = 1;

	DelegateImpl<int> delegate;

	IDelegate<int>& idelegate = delegate;
	
	int callback1CallCount = 0;

	// Subscribe first callback
	delegate.subscribe([&](auto value)
	{
		CHECK(value == changeValue);
		callback1CallCount++;
	});

	delegate.broadcast(changeValue);
	CHECK(callback1CallCount == 1);

	SECTION("Subscribing a second delegate without keeping the handle")
	{		
		int callback2CallCount = 0;
		// Subscribe second callback
		delegate.subscribe([&](auto value)
		{
			CHECK(value == changeValue);
			callback2CallCount++;
		});
		
		delegate.broadcast(changeValue);

		CHECK(callback1CallCount == 2);
		CHECK(callback2CallCount == 1);
	}


	SECTION("Subscribing to a delegate and keeping the handle. Broadcast executed after the handle is destroyed must not call the subscribed callback.")
	{
		SECTION("Unsubscribe via calling reset()")
		{
			int callback2CallCount = 0;
			auto handle = delegate.subscribeKeepHandle([&](auto value)
			{
				CHECK(value == changeValue);
				callback2CallCount++;
			});

			delegate.broadcast(changeValue);
			CHECK(callback2CallCount == 1);
			CHECK(callback1CallCount == 2);

			handle.reset();
			delegate.broadcast(changeValue);
			CHECK(callback2CallCount == 1);
			CHECK(callback1CallCount == 3);
		}

		SECTION("Unsubscribe via the desctructor")
		{
			int callback2CallCount = 0;
			{
				auto handle = delegate.subscribeKeepHandle([&](auto value)
				{
					CHECK(value == changeValue);
					callback2CallCount++;
				});

				delegate.broadcast(changeValue);
				CHECK(callback2CallCount == 1);
				CHECK(callback1CallCount == 2);
			}
			delegate.broadcast(changeValue);
			CHECK(callback2CallCount == 1);
			CHECK(callback1CallCount == 3);
		}

		SECTION("Moving a handle must keep the subscription active")
		{
			int callback2CallCount = 0;
			
			auto handle = delegate.subscribeKeepHandle([&](auto value)
			{
				CHECK(value == changeValue);
				callback2CallCount++;
			});

			delegate.broadcast(changeValue);
			CHECK(callback2CallCount == 1);
			
			auto handleMoved = std::move(handle);
			// Calling reset on the old handle must keep the subscription active
			handle.reset();
			delegate.broadcast(changeValue);
			CHECK(callback2CallCount == 2);


			IDelegate<int>::SubscriptionHandle handleCopied(std::move(handleMoved));
			// Calling reset on the old handle must keep the subscription active
			handleMoved.reset();
			delegate.broadcast(changeValue);
			CHECK(callback2CallCount == 3);
		}
	}
}


