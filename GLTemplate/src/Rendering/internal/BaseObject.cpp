#include "Rendering/internal/BaseObject.h"
#include "Rendering/Context.h"

namespace Rendering
{

BaseObject::BaseObject(std::shared_ptr<Rendering::IContext> ctx) :
mContext(ctx) 
{}


std::shared_ptr<Rendering::IContext> 
BaseObject::getContext()
{
	return mContext; 
}

}