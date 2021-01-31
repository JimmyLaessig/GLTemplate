#pragma once
#include "System.h"

#include <string>
#include <memory>

// Implementation of a 128-bit Universally Unique Identifier. 
class GLTEMPLATE_API UUID2
{
public :
	// Creates a new unique identifier
	UUID2();


	~UUID2();


	UUID2(const UUID2& other);


	UUID2(UUID2&& other) noexcept;


	UUID2& operator=(const UUID2& other);


	UUID2& operator=(UUID2&& other) noexcept;


	// Returns true if the UUID matches the other
	bool operator==(const UUID2& other) const;


	bool operator!=(const UUID2& other) const;


	// Returns the UUID as a readable string
	const std::string_view string() const;

private:

	struct Impl;
	std::unique_ptr<Impl> mImpl;
};


namespace std
{
	template<>
	struct hash<UUID2>
	{
		std::size_t operator()(const UUID2& uuid) const
		{
			std::hash<std::string_view> hasher;
			return hasher(uuid.string());
		}
	};
}