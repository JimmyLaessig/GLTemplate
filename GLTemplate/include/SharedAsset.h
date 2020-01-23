#pragma once


#include <string>
#include <iostream>
#include <map>
#include <set>

#include "Application/Log.h"

class SharedAsset
{
public: 	

	virtual ~SharedAsset() = default;

	/**
	 * Delete the copy constructor.
	 */
	SharedAsset(const SharedAsset& other) = delete;

	/**
	 * Returns the ID of the asset.
	 */
	virtual const size_t& getID() const
	{
		return ID;
	}

	/**
	 * Returns the human-readable name of the asset.
	 */
	virtual const std::string_view getName() const
	{
		return name;
	}


protected: 

	SharedAsset() = default;

private:

	
	/**
	 * The unique ID of the asset.
	 */
	size_t ID;

	/**
	 * The (readable) name of the asset.
	 */
	std::string name;

public: 

	/**
	 * Factory method that creates a runtime asset with the given name or returns the cached instance.
	 * If the asset with the same name was creted previously, the cached instances is returned.
	 * If the cached asset#s type is not T nullptr is returned.
	 */
	template<class T, class ...Args>
	static std::shared_ptr<T> New(const std::string_view name, Args... args)
	{
		// Construct an alternative name of the object
		std::string alterativeName = std::string(typeid(T).name()) + "_" + std::to_string(NumSharedAssetsCreated);

		// Create the (hopefully) unique ID from either the name (if set) or the class name + a global counter
		size_t ID = std::hash<const char*>()(name.empty() ? alterativeName.data() : name.data());

		// Return cached element
		if (AssetCache.count(ID))
		{
			// Assure that the type of the object is actually the same as the templated type T.
			if (auto asset = std::dynamic_pointer_cast<T>(AssetCache[ID]))
			{
				return asset;
			}
			// Else, log the error and return nullptr.
			else
			{
				std::cerr << "Type Conflict: An object with ID=" << ID << " already exists in the cache. Target type: "
					<< typeid(T).name() << ", found type: " << typeid(*AssetCache[ID].get()).name() << "." << std::endl;

				return nullptr;
			}
		}

		// Construct element in cache
		
		auto asset = std::shared_ptr<T>(new T(args...));
		asset->name = name;
		asset->ID = ID;

		NumSharedAssetsCreated++;
		// Push the element to the cache if loading was successfull. 
		AssetCache[asset->ID] = asset;

		return asset;
	}

	/**
	 * Factory method that creates a new asset from a file using the prebuild factory classed.
	 * See FromFile<T, TLoader> for more information.
	 */
	template<class T, class ...Args>
	static std::shared_ptr<T> FromFile(const std::string_view path, const std::string_view name, Args... args)
	{
		T::no_implementation;
	}

	/**
	 * Factory method that creates a new asset from a file  using the provided Factory class.
	 * If the file was loaded previously, the cached instances is returned.
	 * If the cached asset is of other type than T nullptr is returned.
	 * If the factory method fails to load a nullptr is returned.
	 */
	template<class T, class TLoader, class ...Args>
	static std::shared_ptr<T> FromFile(const std::string_view path, const std::string_view name, Args... args)
	{
		if (auto asset = New<T>(path))
		{
			asset->name = name;
			
			if (TLoader::Load(asset.get(), path))
			{
				return asset;
			}
			else
			{
				std::cerr << "Error loading object ID=" << asset->ID << " from " << path << "." << std::endl;
				AssetCache.erase(asset->ID);
				return nullptr;
			}
		}
		else
		{
			return {};
		}
	
	}

private: 

	/**
	 * Holds all created assets.
	 */
	static std::map<size_t, std::shared_ptr<SharedAsset>> AssetCache;

	/**
	 * Counts the total number of created assets.
	 */
	static size_t NumSharedAssetsCreated;
};

