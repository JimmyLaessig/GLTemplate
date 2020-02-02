#include <catch2/catch.hpp>
#include "Rendering/GL/GLResourceBackend.h"
#include "Components/Texture2D.h"
#include <algorithm>
#include "Application/Log.h"


TEST_CASE("Initializing the GpuResourceBackend must return a GLResourceBackend")
{
	
	GpuResourceBackend::init<GLResourceBackend>();

	auto backend = GpuResourceBackend::get();
	REQUIRE(backend);
	REQUIRE(dynamic_cast<GLResourceBackend*>(backend));


	SECTION("Creating a texture2D...")
	{
		const glm::u8vec4 defaultColor(255, 0, 255, 255);
		const glm::u32vec2 size(4, 4);


		Texture2D<glm::u8vec4> tex(size, defaultColor);
		SECTION("The size of of the texture must match")
		{
			CHECK(tex.getTextureSize() == size);
			CHECK(tex.getData().size() == size.x * size.y);
		}
		SECTION("The textureData must be filled with the defaultValue...")
		{
			CHECK(std::all_of(std::begin(tex.getData()), std::end(tex.getData()), [&](const auto& px) {return px == defaultColor; }));
		}
		SECTION("The PixelInfo must match the templated pixel type")
		{
			auto pixelInfo = tex.getPixelInfo();
			CHECK(pixelInfo.Channels == PixelChannels::RGBA);
			CHECK(pixelInfo.DataType == PixelDataType::UNSIGNED_BYTE);
		}

		REQUIRE(tex.getBackendTexture());
	}
}


