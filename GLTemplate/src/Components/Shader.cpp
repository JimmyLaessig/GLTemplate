#include "Components/Shader.h"

#include <fstream>


bool ShaderLoader::Load(Shader * shader, const std::string_view path)
{
	std::ifstream file(path.data());
	if (file.good())
	{
		shader->setShaderCode(std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()));
		file.close();
		return true;
	}
	return false;
}
