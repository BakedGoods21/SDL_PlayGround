#pragma once

#include <string>
#include <GL/glew.h>

namespace BakedEngine
{

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	bool compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	bool linkShaders();

	void addAttribute(const std::string& attributeName);

	GLuint getUniformLocation(const std::string& uniformName);

	void use();
	void unuse();

private:
	GLuint _programId;

	GLuint _vertexShaderId;
	GLuint _fragmentShaderId;

	int _numberOfAttributes;

	bool compileShader(const std::string& shaderFilePath, GLuint shaderId);
	bool checkShaderStatus(GLuint shaderId, GLenum type, bool compileStatus);
};

} // End of namespace BakedEngine
