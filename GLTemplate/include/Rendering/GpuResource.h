#pragma once
#include <mutex>
#include <atomic>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>


#include "GpuResourceBackend.h"



class GpuResource
{
public: 

	GpuResource();


	virtual ~GpuResource();

	//GpuResource(GpuResource&& other) noexcept;

	GpuResource(const GpuResource& other) = delete;
	

	GpuResource& operator=(const GpuResource& other) = delete;

	/**
	 * Thread-safe wrapper function around freeGpuMemoryImpl() which holds the actual memory-freeing functionalities.
	 * Must be called explicitly (e.g. in descructor of derived class).
	 */
	virtual void freeGpuMemory()
	{
		gpuResourceLock.lock();
		freeGpuMemoryImpl();
		bIsOutdated = false;
		gpuResourceLock.unlock();
	}

	/**
	 * Thread-safe wrapper function around updateGpuMemoryImpl() which holds the actual update functionalities.
	 */
	virtual void updateGpuMemory()
	{
		gpuResourceLock.lock();
		updateGpuMemoryImpl();
		bIsOutdated = false;
		gpuResourceLock.unlock();
	}

	/**
	 * Marks the resource as outdated, triggering a GPU resource update on the next draw.  This function is thread-safe.
	 */
	virtual void markOutdated()
	{
		gpuResourceLock.lock();
		GpuResourceBackend::get()->markResourceOutdated(this);
		bIsOutdated = true;
		gpuResourceLock.unlock();
	}

	/**
	 *
	 */
	virtual bool isOutdated() const
	{
		return bIsOutdated;
	}


	/**
	 * Returns the resource lock for this resource.
	 */
	virtual std::mutex& getResourceLock()
	{
		return gpuResourceLock;
	}


	GpuResourceBackend* getGpuResourceBackend();

protected: 


	/**
	 * Override this function for your custom gpu update code. DO NOT CALL THIS FUNCTION DIRECTLY, use updateGpuMemory() instead.
	 */
	virtual void updateGpuMemoryImpl() = 0;

	/**
	 * Override this function for your custom gpu free code. DO NOT CALL THIS FUNCTION DIRECTLY, use freeGpuMemory() instead.
	 */
	virtual void freeGpuMemoryImpl() = 0;

private: 

	bool bIsOutdated = false;

	std::mutex gpuResourceLock;
};



//class DrawableGpuResource : public GpuResource
//{
//public: 
//	
//	virtual std::function<void()> getDrawCall() const = 0;
//};