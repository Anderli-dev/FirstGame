#pragma once

#include <glad/glad.h>
#include <string>

using namespace std;

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const string& vertexShader, const string& fragmentShader);
		~ShaderProgram();
		bool isComplited()const {
			return m_isComplited;
		}
		void use()const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

	private:
		bool createShader(const string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isComplited = false;
		GLuint m_ID = 0;
	};
}