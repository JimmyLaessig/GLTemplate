#pragma once

#include "GpuResource.h"
#include "VectorMath.h"


enum class PixelChannels : uint8_t
{
	R		= 1u,
	RG		= 2u,
	RGB		= 3u,
	RGBA	= 4u
};


template<typename PixelType> inline PixelChannels toPixelChannels()	{return PixelChannels(PixelType().length());}
template<> inline PixelChannels toPixelChannels<float>()			{ return PixelChannels::R; }
template<> inline PixelChannels toPixelChannels<double>()			{ return PixelChannels::R; }
template<> inline PixelChannels toPixelChannels<uint8_t>()			{ return PixelChannels::R; }
template<> inline PixelChannels toPixelChannels<int16_t>()			{ return PixelChannels::R; }
template<> inline PixelChannels toPixelChannels<uint16_t>()			{ return PixelChannels::R; }
template<> inline PixelChannels toPixelChannels<int>()				{ return PixelChannels::R; }
template<> inline PixelChannels toPixelChannels<unsigned int>()		{ return PixelChannels::R; }


enum class PixelDataType
{
	FLOAT,
	//DOUBLE,
	BYTE,
	UNSIGNED_BYTE,
	SHORT,
	UNSIGNED_SHORT,
	INT,
	UNSIGNED_INT
};


template<typename PixelType> inline PixelDataType toPixelDataType(){ return toPixelDataType<decltype(PixelType().x)>();}

template<> inline PixelDataType toPixelDataType<float>()		{ return PixelDataType::FLOAT;}
//template<> inline PixelDataType toPixelDataType<double>()		{ return PixelDataType::DOUBLE;}
template<> inline PixelDataType toPixelDataType<int8_t>()		{ return PixelDataType::BYTE;}
template<> inline PixelDataType toPixelDataType<uint8_t>()		{ return PixelDataType::UNSIGNED_BYTE; }
template<> inline PixelDataType toPixelDataType<int16_t>()		{ return PixelDataType::SHORT;}
template<> inline PixelDataType toPixelDataType<uint16_t>()		{ return PixelDataType::UNSIGNED_SHORT;}
template<> inline PixelDataType toPixelDataType<int>()			{ return PixelDataType::INT;}
template<> inline PixelDataType toPixelDataType<unsigned int>()	{ return PixelDataType::UNSIGNED_INT;}


struct PixelInfo
{
	PixelInfo(PixelChannels channels, PixelDataType dataType) : 
		Channels(channels), 
		DataType(dataType) 
	{}

	PixelInfo(const PixelInfo& other) = default;
	PixelInfo(PixelInfo&& other) = default;

	PixelChannels Channels;
	PixelDataType DataType;
};


class ITexture
{
public: 


	virtual size_t getTextureSizeInBytes() const = 0;


	virtual glm::u32vec2 getTextureSize() const = 0;


	virtual const void* getTextureDataPtr() const = 0;


	virtual PixelInfo getPixelInfo() const = 0;


	virtual const IBackendTexture* getBackendTexture() const = 0;

};