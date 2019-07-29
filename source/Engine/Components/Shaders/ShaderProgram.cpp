#include "ShaderProgram.h"
#include "ShaderProgramException.h"
#include <Engine/Components/GL.h>
#include <glm/gtc/type_ptr.inl>

ShaderProgram::ShaderProgram()
{
	id_shader_program = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id_shader_program);
}

void ShaderProgram::attachShader(ShaderType shader_type, const std::string & shaderSource)
{
	const char* shader_source = shaderSource.c_str();
	GLenum type = shader_type == ShaderType::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

	GLuint shader_id;
	GLint success;

	shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &shader_source, NULL);
	glCompileShader(shader_id);

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint log_length;
		glGetProgramiv(id_shader_program, GL_INFO_LOG_LENGTH, &log_length);
		char* log = new char[log_length];
		glGetShaderInfoLog(shader_id, log_length, NULL, log);
		std::string message("Failed shader compile");
		if(shader_type == ShaderType::Vertex)
		{
			message += "(vertex shader):\n";
		}
		else
		{
			message += "(fragment shader):\n";
		}
		message.append(log);

		delete[] log;
		throw ShaderProgramException(message, __FILE__, __LINE__, __FUNCTION__);

	}
	glAttachShader(id_shader_program, shader_id);
	if (shader_type == ShaderType::Vertex)
	{
		id_vertex_shader = shader_id;
	}
	else
	{
		id_fragment_shader = shader_id;
	}
}

void ShaderProgram::link()
{
	glLinkProgram(id_shader_program);

	GLint success;
	glGetProgramiv(id_shader_program, GL_LINK_STATUS, &success);

	if (!success)
	{
		GLint log_length;
		glGetProgramiv(id_shader_program, GL_INFO_LOG_LENGTH, &log_length);
		char* log = new char[log_length];
		glGetProgramInfoLog(id_shader_program, log_length, NULL, log);
		std::string message = "Link shader program failed\n";
		message.append(log);
		delete[] log;
		throw ShaderProgramException(message, __FILE__, __LINE__, __FUNCTION__);
	}

	glDeleteShader(id_vertex_shader);
	glDeleteShader(id_fragment_shader);
}

u_int ShaderProgram::getProgramId()
{
	return id_shader_program;
}

void ShaderProgram::useProgram()
{
	glUseProgram(id_shader_program);
}

void ShaderProgram::setUniformId(const std::string& uniform_variable_name)
{
	u_int uniform_id = glGetUniformLocation(id_shader_program, uniform_variable_name.c_str());
	if(!uniform_id)
	{
		//throw ShaderProgramException(("Variable " + uniform_variable_name + "didn't founded"),
		//	__FILE__, __LINE__, __FUNCTION__);
	}

	uniforms_location.insert(std::pair<std::string, u_int>(uniform_variable_name, uniform_id));
}

u_int ShaderProgram::getUniformId(const std::string& uniform_variable_name)
{
	return uniforms_location[uniform_variable_name];
}

void ShaderProgram::setUniformParameter(const std::string & name, const matrix3 & parameter)
{
	glUniformMatrix3fv(getUniformId(name), 1, false, glm::value_ptr(parameter));
}

void ShaderProgram::setUniformParameter(const std::string& name, const matrix4& parameter)
{
	glUniformMatrix4fv(getUniformId(name), 1, false, glm::value_ptr(parameter));
}


void ShaderProgram::setUniformParameter(const std::string & name, bool parameter)
{
	glUniform1i(uniforms_location[name], parameter);
}

void ShaderProgram::setUniformParameter(const std::string & name, int parameter)
{
	glUniform1i(uniforms_location[name], parameter);
}
