#include <Base/UUID2.h>
#include <uuid.h>
#include <random>
#include <array>
#include <cassert>
#include <mutex>
#include <thread>

namespace
{
	std::random_device rnd;
	auto seed = std::array<int, std::mt19937::state_size>{};

	std::seed_seq seq(std::begin(seed), std::end(seed));
	std::mt19937 generator(seq);
	uuids::uuid_random_generator uuidGenerator(generator);
	std::mutex uuidGeneratorProtection;


	uuids::uuid generate()
	{
		std::lock_guard<std::mutex> lock(uuidGeneratorProtection);
		return uuidGenerator();
	}

}


struct UUID2::Impl
{
public:

	Impl():
		mID(generate()),
		readableID(uuids::to_string(mID))
	{}


	bool operator==(const UUID2::Impl& other) const
	{
		return mID == other.mID;
	}


	const std::string_view string() const
	{
		return readableID;
	}

private:

	const uuids::uuid mID;

	const std::string readableID;
};


UUID2::UUID2():
	mImpl(new UUID2::Impl)
{}


UUID2::UUID2(const UUID2& other):
	mImpl(new Impl(*other.mImpl))
{}


UUID2::UUID2(UUID2&& other) noexcept:
	mImpl(std::move(other.mImpl))
{}


UUID2::~UUID2() = default;


UUID2&
UUID2::operator=(const UUID2& other)
{
	assert(other.mImpl);

	mImpl.reset(new Impl(*other.mImpl));
	return *this;
}


UUID2&
UUID2::operator=(UUID2&& other) noexcept
{
	assert(other.mImpl);

	mImpl = std::move(other.mImpl);

	return *this;
}


bool
UUID2::operator==(const UUID2& other) const
{
	assert(mImpl);
	assert(other.mImpl);

	return *mImpl == *other.mImpl;
}


bool
UUID2::operator!=(const UUID2& other) const
{
	return !(*this == other);
}


const std::string_view
UUID2::string() const
{
	assert(mImpl);

	return mImpl->string();
}