#pragma once


#include "Rendering/GL/OpenGL.h"

namespace Rendering
{
namespace GL
{
    // Callback function executed when an OpenGL error occured
    void APIENTRY GLDebugMessageCallback(GLenum source, 
                                         GLenum type, 
                                         GLuint id,
                                         GLenum severity, 
                                         GLsizei length,
                                         const GLchar* msg, 
                                         const void* data);

}
}