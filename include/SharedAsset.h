#pragma once
#include <map>
#include <string>
#include <iostream>
#include <iostream>


class SharedAsset
{
public: 	

	/**
	 * Factory method that creates a runtime asset with the given ID, or returns the cached asset if exists.
	 * If the object failed to create or an object with the same ID with a different type exists in the cache, nullptr is returned.
	 */
	template<class T>
	static std::shared_ptr<T> New(const std::string& ID)
	{
		return ConsctructSharedAsset<T>(ID);
	}

	/**
	 * Factory method that creates a new asset from a file or returns the asset from the cache if the file was loaded previously.
	 * The unique ID of the object will be derived from the path field. If the provided ID field is not an empty string, the ID field will be used as id instead. 
	 * If the object is created for the first time, the load function will be executed. If load failes, the object is discarded and nullptr is returned.
	 */
	template<class T>
	static std::shared_ptr<T> FromFile(const std::string& path, const std::string& ID = "")
	{
		return ConsctructSharedAsset<T>(ID == "" ? path : ID, path);
	}

	/**
	 * Do not create SharedAssets directy, use the static factory functions instead.
	 */
	SharedAsset() = default;

	/**
	 * Delete the copy constructor.
	 */
	SharedAsset(const SharedAsset& other) = delete;

	/**
	 * Returns the path to the file of the asset.
	 */
	const std::string& getAssetPath() const
	{
		return path;
	}

	/**
	 * Returns the ID of the asset.
	 */
	const std::string& getID() const
	{
		return ID;
	}

	/**
	 * Indicates whether or not the asset was created during runtime or loaded from file.
	 */
	bool isRuntimeCreated() const
	{
		return bRuntimeCreated;
	}

	/**
	 * Loads the asset from the path.
	 */
	virtual bool load() = 0;

	/**
	 * Reloads the asset from the file path.
	 */
	virtual bool reload() = 0;

private:

	/**
	 * Constructs the SharedAsset object of derived type T with the given id and path.
	 * If the path argument is an empty string, a runtime object will be created. 
	 */
	template<class T>
	static std::shared_ptr<T> ConsctructSharedAsset(const std::string& ID, const std::string& path = "")
	{
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
		auto asset = std::make_shared<T>();
		asset->ID				= ID;
		asset->path				= path;
		asset->bRuntimeCreated	= path == "";
		
		// Call the load function on non-runtime objects.
		if (!asset->bRuntimeCreated)
		{
			if (!asset->load())
			{
				std::cerr << "Error loading object ID=" << ID << " from " << path << "." << std::endl;
				return nullptr;
			}
		}

		// Push the element to the cache if loading was successfull. 
		AssetCache[ID] = asset;

		return asset;
	}

private:	

	std::string ID;

	std::string path;

	bool bRuntimeCreated;

	static std::map<std::string, std::shared_ptr<SharedAsset>> AssetCache;

};
