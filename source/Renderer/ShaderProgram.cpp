#include "ShaderProgram.h"

#include <iostream>

using namespace std;

namespace Renderer {
	ShaderProgram::ShaderProgram(const string& vertexShader, const string& fragmentShader) {

		GLuint vertexShaderID;

		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
			cerr << "VERTEX SHADER Complite-time error:\n" << endl;
			return;
		}

		GLuint fragmentShaderID;

		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
			cerr << "fragment SHADER Complite-time error:\n" << endl;
			glDeleteShader(vertexShaderID);
			return;
		}
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar infolog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infolog);
			cerr << "ERROR::SHADER Link-time error:\n" << infolog << endl;

		}
		else {
			m_isComplited = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infolog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infolog);
			cerr << "ERROR::SHADER; Complite-time error:\n" << infolog << endl;
			return false;
		}
		return true;
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_ID);
	}

	void ShaderProgram::use()const {
		glUseProgram(m_ID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept {

		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isComplited = shaderProgram.m_isComplited;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isComplited = false;
		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept {

		m_ID = shaderProgram.m_ID;
		m_isComplited = shaderProgram.m_isComplited;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isComplited = false;
	}
}