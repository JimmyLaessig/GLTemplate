#pragma once

#include "GLDebugMessageCallback.h"

#include <unordered_map>
#include <iostream>

namespace Rendering
{
namespace GL
{

// Callback function for printing debug statements
void APIENTRY GLDebugMessageCallback(GLenum source, 
                                     GLenum type,
                                     GLuint id,
                                     GLenum severity, 
                                     GLsizei length,
                                     const GLchar* msg, 
                                     const void* data)
{


    static std::unordered_map<GLenum, std::string> sourceToString
    {
        { GL_DEBUG_SOURCE_API,              "API"               },
        { GL_DEBUG_SOURCE_WINDOW_SYSTEM,    "WINDOW SYSTEM"     },
        { GL_DEBUG_SOURCE_SHADER_COMPILER,  "SHADER COMPILER"   },
        { GL_DEBUG_SOURCE_THIRD_PARTY,      "THIRD PARTY"       },
        { GL_DEBUG_SOURCE_APPLICATION,      "APPLICATION"       },
        { GL_DEBUG_SOURCE_OTHER,            "UNKNOWN"           },
    };

    static std::unordered_map<GLenum, std::string> typeToString
    {
        {GL_DEBUG_TYPE_ERROR,               "ERROR"                 },
        {GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "DEPRECATED BEHAVIOR"   },
        {GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,  "UDEFINED BEHAVIOR"     },
        {GL_DEBUG_TYPE_PORTABILITY,         "PORTABILITY"           },
        {GL_DEBUG_TYPE_PERFORMANCE,         "PERFORMANCE"           },
        {GL_DEBUG_TYPE_OTHER,               "OTHER"                 },
        {GL_DEBUG_TYPE_MARKER,              "MARKER"                }
    };

    static std::unordered_map<GLenum, std::string> severityToString
    {                                                 
        {GL_DEBUG_SEVERITY_HIGH,            "HIGH"          },
        {GL_DEBUG_SEVERITY_MEDIUM,          "MEDIUM"        },
        {GL_DEBUG_SEVERITY_LOW,             "LOW"           },
        {GL_DEBUG_SEVERITY_NOTIFICATION,    "NOTIFICATION"  }
    };

    
    const std::string _source   = sourceToString.count(source)      ? sourceToString[source]        : "UNKNOWN";
    const std::string _type     = typeToString.count(type)          ? typeToString[type]            : "UNKNOWN";
    const std::string _severity = severityToString.count(severity)  ? severityToString[severity]    : "UNKNOWN";

    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
    {
        std::cout << "OpenGL error [" << id << "]: " << _type << " of " << _severity << " severity, raised from " << _source << ": " << msg << std::endl;
        __debugbreak();
    }
}
}
}