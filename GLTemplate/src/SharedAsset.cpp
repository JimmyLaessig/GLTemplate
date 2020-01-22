#include "SharedAsset.h"

#include <chrono>

std::map<size_t, std::shared_ptr<SharedAsset>> SharedAsset::AssetCache;

SharedAsset::UUIDGenerator SharedAsset::gen;


size_t SharedAsset::UUIDGenerator::operator()(const std::string_view s)
{
	auto timeHash = std::to_string((*this)()) + s.data();

	auto hash = std::hash<const char*>()(timeHash.data());

	if (hashes.count(hash))
	{
		throw std::exception("What are the odds");
	}
	hashes.insert(hash);
	return hash;
}

size_t SharedAsset::UUIDGenerator::operator()()
{
	auto ns = std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

	auto hash = std::hash<const char*>()(ns.data());

	if (hashes.count(hash))
	{
		throw std::exception("What are the odds");
	}
	hashes.insert(hash);
	return hash;
}