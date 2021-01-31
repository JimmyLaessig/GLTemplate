#pragma once

#include "Base/System.h"
#include "Base/UUID2.h"
#include "Base/NonCopyable.h"

#include <unordered_map>
#include <functional>
#include <mutex>


template<typename ...ValueTypes>
class GLTEMPLATE_API IDelegate : public Base::NonCopyable
{
public:
	
	// The lifetime of the handle controls the duration of the delegate subscription
	// Once the handle is destroyed or reset() is called, the callback is removed 
	// from the delegate.
	class GLTEMPLATE_API SubscriptionHandle : public Base::NonCopyable
	{

	public:

		// Creates an unset DelegateSubscription
		SubscriptionHandle() = default;


		SubscriptionHandle(IDelegate<ValueTypes...>* delegate, const UUID2& subscriptionID) :
			mDelegate(delegate),
			mCallbackID(subscriptionID)
		{}


		SubscriptionHandle(SubscriptionHandle&& other) noexcept
		{
			this->mCallbackID = std::move(other.mCallbackID);
			this->mDelegate = other.mDelegate;
			other.mDelegate = nullptr;
		}


		SubscriptionHandle& operator=(SubscriptionHandle&& other) noexcept
		{
			this->mCallbackID = std::move(other.mCallbackID);
			this->mDelegate = other.mDelegate;
			other.mDelegate = nullptr;

			return *this;
		}


		~SubscriptionHandle()
		{
			reset();
		}


		// Rests the subscription, thus removing the callback from the delegate.
		void reset()
		{
			if (isSubscribed())
			{
				mDelegate->unsubscribe(*this);
				mDelegate = nullptr;
			}
		}


		// Return whether the handle holds an active subscription to a delegate.
		bool isSubscribed() const
		{
			return mDelegate;
		}


		// Get the id of the subscription
		const UUID2& getID() const
		{
			return mCallbackID;
		}

	private:

		// The subscribed delegate
		IDelegate<ValueTypes...>* mDelegate{ nullptr };

		// The id of the subscription used to identify the callback
		UUID2 mCallbackID;
	};


	// Subscribes the functor to the delegate.
	// The callback is executed until Delegate is destroyed.
	virtual void subscribe(const std::function<void(ValueTypes...)>& callback) = 0;


	// Subscribes the callback to the delegate and returns the subscription object handle.
	// The callback is executed as long as the returned handle and the Delegate aren´t destroyed.
	virtual SubscriptionHandle subscribeKeepHandle(const std::function<void(ValueTypes...)>& callback) = 0;

protected:

	// Unsubscribes the callback with this handle from the delegate. Called from SubscriptionHandle
	virtual void unsubscribe(const SubscriptionHandle& subscription) = 0;
};


template<typename ...ValueTypes>
class GLTEMPLATE_API DelegateImpl : public IDelegate<ValueTypes...>
{
public: 

	// Broadcasts the changed value to all subscribed callbacks.
	void 
	broadcast(const ValueTypes&... values)
	{
		std::lock_guard lock(mSubscriberProtection);

		for (auto& [_, cb] : mSubscribers)
		{
			cb(values...);
		}
	}


	void 
	subscribe(const std::function<void(ValueTypes...)>& callback) override
	{
		std::lock_guard lock(mSubscriberProtection);

		mSubscribers.emplace(UUID2(), callback);
	}


	IDelegate<ValueTypes...>::SubscriptionHandle 
	subscribeKeepHandle(const std::function<void(ValueTypes...)>& callback) override
	{
		std::lock_guard lock(mSubscriberProtection);
	
		UUID2 id;
		mSubscribers.emplace(id, callback);

		return {this, id};
	}

protected:

	void 
	unsubscribe(const IDelegate<ValueTypes...>::SubscriptionHandle& subscription) override
	{
		std::lock_guard<std::recursive_mutex> lock(mSubscriberProtection);
	
		mSubscribers.erase(mSubscribers.find(subscription.getID()));
	}

private:

	std::unordered_map<UUID2, std::function<void(const ValueTypes&...)>> mSubscribers;

	std::recursive_mutex mSubscriberProtection;
};