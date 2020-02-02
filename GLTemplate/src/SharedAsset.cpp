#include "SharedAsset.h"
#include "Components/Mesh.h"

std::map<size_t, std::shared_ptr<SharedAsset>> SharedAsset::AssetCache;
size_t SharedAsset::NumSharedAssetsCreated = 0;


/**
 * Factory method that creates a new asset from a file using the prebuild factory classed.
 * See FromFile<T, TLoader> for more information.
 */
template<>
static std::shared_ptr<Mesh> SharedAsset::FromFile<Mesh>(const std::string_view path, const std::string_view name)
{
	return {};// FromFile<Mesh, MeshLoader>(path, name);
}