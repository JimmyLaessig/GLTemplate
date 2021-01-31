#pragma once

#include "Base/Enum.h"


namespace Rendering
{

	ENUM_CLASS(Alignment,
		BYTE,
		EVEN_BYTES,
		WORD,
		DOUBLE_WORD,
	);

	
	ENUM_CLASS(Usage,
		CPU_W_GPU_R,
		CPU_W_GPU_RW,
		CPU_RW_GPU_RW,
		GPU_RW
	);
}