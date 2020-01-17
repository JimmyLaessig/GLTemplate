#pragma once

#include <functional>
#include "uuid.h"
#include <map>


typedef std::function<void(float)> OnUpdateCallback;
typedef std::function<void(size_t, size_t)> OnResizedDelegate;
typedef std::function<void(size_t, size_t)> OnWindowCloseDelegate;





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
		this->callbacks[uuids::to_string(disposable.ID)] = cb;

		return disposable;
	}

	/**
	 * Unsubscribes a callback from the delegate.
	 */
	void unsubscribe(const Delegate<Callback>::Disposable& disposable)
	{
		if (disposable->delegate == this)
		{
			this->callbacks.erase(disposable.getID());
		}
	}

	/**
	 * Broadcasts to all callbacks with the provided value(s).
	 */
	template<class ...Args>
	void broadcast(Args... args)
	{
		for (auto& cb : callbacks)
		{
			//cb(...args);
		}
	}	


private: 

	std::map<std::string, Callback> callbacks;
};