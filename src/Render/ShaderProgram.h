#pragma once

#include <string>
#include <glbinding/gl/types.h>
#include <glbinding/gl/enum.h>

namespace Render {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool IsCompiled() const { return m_isCompiled; }
		void Use() const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;


	private:
		bool CreateShader(const std::string& source, const gl::GLenum shaderType, gl::GLuint& shaderID);
		bool m_isCompiled = false;
		gl::GLuint m_id = 0;
	};
}