#pragma once
#include "Libs.h"
// This is a virtual class implementing factory method design pattern

class ShaderFactory {
public:
	template<typename T>
	static std::unique_ptr<Shader> createShader(std::string shaderLocation);
};

class Shader {
public:
	Shader();

};
