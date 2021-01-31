#pragma once

#include "Base/System.h"
#include "Base/NonCopyable.h"

#include <memory>


namespace Rendering
{
class IContext;

class GLTEMPLATE_API BaseObject : public Base::NonCopyable
{
public: 
	
	BaseObject(std::shared_ptr<Rendering::IContext> ctx);


	virtual ~BaseObject() = default;


	std::shared_ptr<Rendering::IContext> getContext();

private:

	std::shared_ptr<Rendering::IContext> mContext;
};

}