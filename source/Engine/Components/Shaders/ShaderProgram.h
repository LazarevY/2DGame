#pragma once
#include <Engine/Utils/types.h>
#include "ShaderProgramException.h"
#include <unordered_map>

class ShaderProgram
{
public:
	enum class ShaderType
	{
		Vertex, Fragment
	};
	ShaderProgram();
	~ShaderProgram();

	void attachShader(ShaderType shader_type, const std::string& shaderSource);
	void link();

	u_int getProgramId();
	void useProgram();

	void setUniformId(const std::string& uniform_variable_name);
	u_int getUniformId(const std::string& uniform_variable_name);

	void setUniformParameter(const std::string& name, const matrix3& parameter);
	void setUniformParameter(const std::string& name, const matrix4& parameter);
	void setUniformParameter(const std::string& name, bool parameter);
	void setUniformParameter(const std::string& name, int parameter);

private:
	u_int id_shader_program;
	u_int id_vertex_shader;
	u_int id_fragment_shader;

	std::unordered_map<std::string, u_int> uniforms_location;
};
