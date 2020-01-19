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
	 * Thread-safe wrapper function around freeGpuMemory_Internal() which holds the actual memory-freeing functionalities.
	 * Must be called explicitly (e.g. in descructor of derived class).
	 */
	virtual void freeGpuMemory()
	{
		gpuResourceLock.lock();
		freeGpuMemory_Internal();
		bIsOutdated = false;
		gpuResourceLock.unlock();
	}

	/**
	 * Thread-safe wrapper function around updateGpuMemory_Internal() which holds the actual update functionalities.
	 */
	virtual void updateGpuMemory()
	{
		gpuResourceLock.lock();
		updateGpuMemory_Internal();
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
	virtual void updateGpuMemory_Internal() = 0;

	/**
	 * Override this function for your custom gpu free code. DO NOT CALL THIS FUNCTION DIRECTLY, use freeGpuMemory() instead.
	 */
	virtual void freeGpuMemory_Internal() = 0;

private: 

	bool bIsOutdated = false;

	std::mutex gpuResourceLock;
};



class DrawableGpuResource : public GpuResource
{
public: 
	
	virtual std::function<void()> getDrawCall() const = 0;
};