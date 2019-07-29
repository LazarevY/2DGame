//#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <Components/GraphicsComponents.h>
// TODO: need to improve this code!!

std::string loadShaderCode(std::string filePath);

class Shader
{
public:
	// Идентификатор программы
	GLuint program;
	// Конструктор считывает и собирает шейдер
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader(std::string vertexShaderCode, std::string fragmentShaderCode);
	// Использование программы
	void use_shader_program();
};

#endif
