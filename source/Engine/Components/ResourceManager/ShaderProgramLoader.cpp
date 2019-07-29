#include "ShaderProgramLoader.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <Engine/Components/GL.h>

BaseResource * ShaderProgramLoader::load_resource(const std::string & path)
{
	return load_resource(path, std::optional<std::any>());
}

BaseResource * ShaderProgramLoader::load_resource(const std::string & path, std::optional<std::any> options)
{
	std::ifstream programCodeFile(path);

	if (!programCodeFile.is_open())
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::ProblemFile, "File didn't open", __FILE__, __LINE__, __FUNCTION__);
	}

	std::string shaderCodeSource{ std::istreambuf_iterator<char>(programCodeFile),
		std::istreambuf_iterator<char>() };

	std::smatch vertexShaderCodeMatch;
	std::regex vertexShaderCodeRegex("\\[vertex\\]([^]*)\\[\\/vertex\\]");
	std::regex_search(shaderCodeSource, vertexShaderCodeMatch, vertexShaderCodeRegex);
	if (vertexShaderCodeMatch.size() < 2)
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::InvalidData, "Shader source has unknow format",
			__FILE__, __LINE__, __FUNCTION__);
	}
	std::string vertexShaderCode = vertexShaderCodeMatch[1].str();

	std::smatch fragmentShaderCodeMatch;
	std::regex fragmentShaderCodeRegex("\\[fragment\\]([^]*)\\[\\/fragment\\]");
	std::regex_search(shaderCodeSource, fragmentShaderCodeMatch, fragmentShaderCodeRegex);

	if (fragmentShaderCodeMatch.size() < 2)
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::InvalidData, "Shader source has unknow format",
			__FILE__, __LINE__, __FUNCTION__);
	}
	std::string fragmentShaderCode = fragmentShaderCodeMatch[1].str();

	ShaderProgram* shader_program = new ShaderProgram();

	try
	{
		shader_program->attachShader(ShaderProgram::ShaderType::Vertex, vertexShaderCode);
		shader_program->attachShader(ShaderProgram::ShaderType::Fragment, fragmentShaderCode);
		shader_program->link();
	}
	catch (ShaderProgramException& exception)
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::InvalidData, exception.getMessage(),
			__FILE__, __LINE__, __FUNCTION__);
	}
	return new Resource<ShaderProgram>(shader_program);
}
