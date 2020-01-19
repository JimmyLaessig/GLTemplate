#pragma once


#include "uuid.h"
#include <map>


template<class Callback>
struct Delegate
{
public: 
	/**
	 * The disposable holds a reference to the delegate the callback was subscribed to. It can be used to dynamically remove the callback from the delegate.
	 * It does NOT automatically unsubscribe if the Disposable is destroyed.
	 */
	struct Disposable
	{
		friend struct Delegate<Callback>;
	public: 
		Disposable() = delete;

		Disposable(const Disposable& other) = default;

		Disposable(Disposable&& other) = default;

	private: 

		/**
		 * Private constructor allows only the Delegate to construct disposables to callbacks
		 */
		Disposable(Delegate* delegate) :
			delegate(delegate),
			ID(uuids::uuid_system_generator{}())
		{}

		/**
		 * Pointer to the delegate.
		 */
		Delegate* delegate = nullptr;

		/**
		 * Unique ID of the callback
		 */
		uuids::uuid ID;
	};


	Delegate() = default;
	
	Delegate(const Delegate& other) = delete;
	
	Delegate(Delegate&& other) = default;
	

	/**
	 * Subscribes a callback to the delegate.
	 */
	Delegate<Callback>::Disposable subscribe(const Callback& cb)
	{
		Disposable disposable(this);
		this->subscribers[uuids::to_string(disposable.ID)] = cb;

		return disposable;
	}

	/**

	 * Unsubscribes a callback from the delegate.
	 */
	bool unsubscribe(const Delegate<Callback>::Disposable& disposable)
	{
  		if (disposable.delegate == this)
		{
			this->subscribers.erase(uuids::to_string(disposable.ID));
			return true;
		}
		else
		{
			// TODO LOG ERROR
			return false;
		}
	}

	/**
	 * Broadcasts to all callbacks with the provided value(s).
	 */
	template<class ...Args>
	void broadcast(Args... args)
	{
		for (auto& [id, cb] : subscribers)
		{
			cb(args...);
		}
	}	


private: 

	class std::map<std::string, Callback> subscribers;
};