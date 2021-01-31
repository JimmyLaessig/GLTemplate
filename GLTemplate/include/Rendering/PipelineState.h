#pragma once
#include "Rendering/internal/BaseObject.h"

#include "Base/Enum.h"
#include "Base/Rectangle.h"

#include <optional>
#include <memory>



namespace Rendering
{

// -----------------------------------------
//
//    Back-/Front-Face Culling
//
// -----------------------------------------

ENUM_CLASS(CullMode,
	FRONT,
	BACK,
	FRONT_AND_BACK
);


ENUM_CLASS(FrontFaceOrientation,
	CW,
	CCW
);


struct FaceCullingMode
{
	CullMode cullMode{ CullMode::BACK };
	FrontFaceOrientation orientation{ FrontFaceOrientation::CCW };
};

// -----------------------------------------
//
//    BlendMode
//
// -----------------------------------------

ENUM_CLASS(BlendFactor,
	ZERO,
	ONE,
	SRC_COLOR,
	ONE_MINUS_SRC_COLOR,
	DST_COLOR,
	ONE_MINUS_DST_COLOR,
	SRC_ALPHA,
	ONE_MINUS_SRC_ALPHA,
	DST_ALPHA,
	ONE_MINUS_DST_ALPHA,
	CONSTANT_COLOR,
	ONE_MINUS_CONSTANT_COLOR,
	CONSTANT_ALPHA,
	ONE_MINUS_CONSTANT_ALPHA,
	SRC_ALPHA_SATURATE,
	SRC1_COLOR,
	ONE_MINUS_SRC1_COLOR,
	SRC1_ALPHA,
	ONE_MINUS_SRC1_ALPHA
);


ENUM_CLASS(BlendFunc,
	ADD,
	SUBTRACT,
	REVERSE_SUBTRACT,
	MIN,
	MAX
);


struct BlendMode
{
	BlendFactor sourceFactor{ BlendFactor::ONE };
	BlendFactor destFactor{ BlendFactor::ZERO };
	BlendFunc blendFunc{ BlendFunc::ADD };
};

// -----------------------------------------
//
//    Stencil Test
//
// -----------------------------------------

ENUM_CLASS(StencilTestFunc,
	NEVER,
	LESS,
	LESS_OR_EQUAL,
	GREATER,
	GREATER_OR_EQUAL,
	NOT_EQUAL,
	ALWAYS
);


ENUM_CLASS(StencilOp,
	KEEP,
	ZERO,
	REPLACE,
	INCREMENT,
	INCREMENT_WRAP,
	DECREMENT,
	DECREMENT_WRAP,
	INVERT
);



struct StencilOperation
{
	StencilOp stencilFail{ StencilOp::KEEP };
	StencilOp depthFail{ StencilOp::KEEP };
	StencilOp depthPass{ StencilOp::KEEP };
};


struct StencilFunction
{
	StencilTestFunc func{ StencilTestFunc::ALWAYS };
	int32_t ref{ 0 };
	uint8_t mask{ 0xFF };
};


struct StencilTestMode
{
	StencilOperation compareFront;
	StencilOperation compareBack;

	StencilFunction operationFront;
	StencilFunction operationBack;
};


// -----------------------------------------
//
//    DepthTest
//
// -----------------------------------------

ENUM_CLASS(DepthFunc,
	NEVER,
	LESS,
	LESS_OR_EQUAL,
	GREATER,
	GREATER_OR_EQUAL,
	NOT_EQUAL,
	ALWAYS
);


struct DepthRange
{
	float min{ 0.0f };
	float max{ 1.0f };
};


struct PolygonOffset
{
	float factor{ 0.0f };
	float units{ 0.0f };
	bool fill{ false };
	bool line{ false };
	bool point{ false };
};


struct DepthTestMode
{
	bool depthMask{ true };
	DepthFunc depthFunc{ DepthFunc::LESS };
	DepthRange depthRange;
	PolygonOffset polygonOffset;
};


// -----------------------------------------
// Pipe
//    
//
// -----------------------------------------
class GLTEMPLATE_API IPipelineState : public Rendering::BaseObject
{
public:
	using Rendering::BaseObject::BaseObject;
	using Ptr = std::shared_ptr<IPipelineState>;

	
	struct Config
	{
		std::optional<BlendMode> mBlendState;
		std::optional<StencilTestMode> mStencilMode;
		std::optional<DepthTestMode> mDepthTestMode;
		std::optional<Base::RectangleF> mScissorRectangle;

		Base::RectangleF mViewport;
	};
	

};
} // namespace Rendering