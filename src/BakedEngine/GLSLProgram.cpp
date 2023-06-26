// C++ Libraries
#include <fstream>
#include <vector>
#include <iostream>

// My Libraries
#include "BakedEngine/GLSLProgram.h"
#include "BakedEngine/SdlError.h"

namespace BakedEngine
{

GLSLProgram::GLSLProgram() : _programId(0), _vertexShaderId(0), _fragmentShaderId(0), _numberOfAttributes(-1)
{ }

GLSLProgram::~GLSLProgram() { }

bool GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	std::cerr << "compileShaders" << std::endl;
	_programId = glCreateProgram();

	_vertexShaderId =  glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderId == 0)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Shader Error", "Vertex shader failed to be created!");
		return false;
	}

	_fragmentShaderId =  glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderId == 0)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Shader Error", "Fragment shader failed to be created!");
		return false;
	}

	if (compileShader(vertexShaderFilePath, _vertexShaderId) == false)
	{
		return false;
	}

	if (compileShader(fragmentShaderFilePath, _fragmentShaderId) == false)
	{
		return false;
	}
	std::cerr << "compiled Shaders" << std::endl;

	return true;
}

bool GLSLProgram::compileShader(const std::string& shaderFilePath, GLuint shaderId)
{
	std::ifstream file(shaderFilePath);
	if (file.fail())
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Shader Error", "Shader file failed to open: " + shaderFilePath);
		return false;
	}

	std::string fileContents = "";
	std::string line = "";

	while (std::getline(file, line))
	{
		fileContents += line + "\n";
	}

	file.close();

	const char* fileContentsPointer = fileContents.c_str();
	glShaderSource(shaderId, 1, &fileContentsPointer, nullptr);
	glCompileShader(shaderId);

	if (checkShaderStatus(shaderId, GL_COMPILE_STATUS, true) == false)
	{
		// Provide the infolog in whatever manor you deem best.
		// Exit with failure
		glDeleteShader(shaderId);
		return false;
	}
	return true;
}

bool GLSLProgram::linkShaders()
{
	// Vertex and fragmant shaders are successfully compiled.
	// Now time to link them together into a program

	// Attach our shaders to our program
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);

	// Link our program
	glLinkProgram(_programId);

	// Check the status of our linking
	if (checkShaderStatus(_programId, GL_LINK_STATUS, false) == false)
	{
		// We don't need the program anymore
		glDeleteProgram(_programId);

		// Don't leak shaders either
		glDeleteShader(_vertexShaderId);
		glDeleteShader(_fragmentShaderId);

		return false;
	}

	// Always detach shaders after a successful link
	glDetachShader(_programId, _vertexShaderId);
	glDetachShader(_programId, _fragmentShaderId);
	glDeleteShader(_vertexShaderId);
	glDeleteShader(_fragmentShaderId);

	return true;
}

void GLSLProgram::addAttribute(const std::string& attributeName)
{
	glBindAttribLocation(_programId, ++_numberOfAttributes, attributeName.c_str());
}

GLuint GLSLProgram::getUniformLocation(const std::string& uniformName)
{
	GLuint location = glGetUniformLocation(_programId, uniformName.c_str());

	if (location == GL_INVALID_INDEX)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "GLSL Error: " , "Couldn't get Uniform Variable " + uniformName);
		return GL_INVALID_INDEX;
	}
	return location;
}

bool GLSLProgram::checkShaderStatus(GLuint shaderId, GLenum type, bool compileStatus)
{
	std::string error = "Unknown Error";
	GLint success = 0;

	if (compileStatus)
	{
		glGetShaderiv(shaderId, type, &success);
	}
	else
	{
		glGetProgramiv(shaderId, type, &success);
	}

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		if (compileStatus)
		{
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
		}
		else
		{
			glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
		}

		if (maxLength > 0)
		{
			// The maxLenth includes the NULL character
			std::vector<char> errorLog(maxLength);

			if (compileStatus)
			{
				glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
			}
			else
			{
				glGetProgramInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
			}
			error = std::string(&(errorLog[0]));
		}

		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Shader Error", "Shader Status: " + error);

		return false;
	}

	return true;
}

void GLSLProgram::use()
{
	glUseProgram(_programId);

	for (int i = 0; i < _numberOfAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);

	for (int i = 0; i < _numberOfAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

} // End of namespace BakedEngine
