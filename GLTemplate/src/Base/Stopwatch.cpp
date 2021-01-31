#include <Base/Stopwatch.h>
#include <Base/Log.h>
#include <iostream>

Stopwatch::Stopwatch(bool shouldStart):
	mTimePoints(),
	mIsRunning(false)
{
	if (shouldStart)
	{
		start();
	}
}

Stopwatch::~Stopwatch()
{}


void
Stopwatch::start()
{
	if (!mIsRunning)
	{
		auto now = std::chrono::high_resolution_clock::now();
		mTimePoints.emplace_back(now, now);
		mIsRunning = true;
	}
}


void 
Stopwatch::stop()
{
	if (mIsRunning)
	{
		mTimePoints.back().second	= std::chrono::high_resolution_clock::now();
		mIsRunning					= false;
	}
}


double 
Stopwatch::getElapsedInSeconds() 
{
	return (double)getElapsedInMicroSeconds() / 1000000.0;
}


double 
Stopwatch::getElapsedInMilliseconds() 
{
	return (double)getElapsedInMicroSeconds() / 1000.0;
}


uint64_t 
Stopwatch::getElapsedInMicroSeconds()
{	

	if (mIsRunning)
	{
		mTimePoints.back().second = std::chrono::high_resolution_clock::now();
	}

	uint64_t elapsed = 0;
	
	for (auto& span : mTimePoints)
	{
		elapsed +=  std::chrono::duration_cast<std::chrono::microseconds>(span.second - span.first).count();
	}
	return elapsed;
}


ScopedStopwatch::ScopedStopwatch(std::string_view scopeName):
	mName(scopeName),
	mStopwatch(Stopwatch(true))
{}


ScopedStopwatch::~ScopedStopwatch()
{
	mStopwatch.stop();
	std::scoped_lock lock(registry.accessProtection);
	if (registry.trackedScopes.count(mName))
	{
		registry.trackedScopes[mName] += getElapsedInMicroSeconds();
	}
	else
	{
		registry.trackedScopes[mName] = getElapsedInMicroSeconds();
	}
}


double ScopedStopwatch::getElapsedInSeconds()
{
	return mStopwatch.getElapsedInSeconds();
}


double ScopedStopwatch::getElapsedInMilliseconds()
{
	return mStopwatch.getElapsedInMilliseconds();
}


uint64_t ScopedStopwatch::getElapsedInMicroSeconds()
{
	return mStopwatch.getElapsedInMicroSeconds();
}


ScopedStopwatch::Registry::~Registry()
{
	for (auto& [name, elapsed] : trackedScopes)
	{
		//std::cout << "ScopedStopwatch::" << name << " took " << elapsed << "microseconds" << std::endl;
		//std::cout << "ScopedStopwatch::" << name << " took " << elapsed / 1000.f << "milliseconds" << std::endl;
		//std::cout << "ScopedStopwatch::" << name << " took " << elapsed / 1000000.f << "seconds" << std::endl;
		//SPDLOG_INFO("ScopeStopwatch::%s: %fms", name.c_str(), elapsed / 1000.0f);
	}
}

ScopedStopwatch::Registry ScopedStopwatch::registry;