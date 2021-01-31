#pragma once
#include "System.h"

#include <vector>
#include <chrono>
#include <string>
#include <string_view>
#include <mutex>
#include <unordered_map>
#include "glm/glm.hpp"

class GLTEMPLATE_API Stopwatch
{
public:

	Stopwatch(bool started = true);


	~Stopwatch();


	void start();


	void stop();


	double getElapsedInSeconds() ;


	double getElapsedInMilliseconds() ;


	uint64_t getElapsedInNanoSeconds() ;


	uint64_t getElapsedInMicroSeconds();

	glm::vec3 something;

private: 

	typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
	typedef std::pair<TimePoint, TimePoint> TimeSpan;
	std::vector<TimeSpan> mTimePoints;

	TimePoint mStart;

	bool mIsRunning;
};


class ScopedStopwatch
{
public: 
	ScopedStopwatch(std::string_view scopeName);


	~ScopedStopwatch();


	double getElapsedInSeconds();


	double getElapsedInMilliseconds();


	uint64_t getElapsedInMicroSeconds();

private:

	std::string mName;

	Stopwatch mStopwatch;

	struct Registry
	{
		std::mutex accessProtection;
		std::unordered_map<std::string, uint64_t> trackedScopes;

		~Registry();
	};

	static Registry registry;
};