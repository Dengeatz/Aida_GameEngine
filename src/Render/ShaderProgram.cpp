#include "ShaderProgram.h"
#include <glbinding/gl/functions.h>
#include <glbinding/gl/enum.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

namespace Render {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
        gl::GLuint vertexShaderID;
        if (!CreateShader(vertexShader, gl::GL_VERTEX_SHADER, vertexShaderID))
        {
            std::cerr << "VERTEX SHADER NOT COMPILED" << std::endl;
            system("pause");
        }
        
        //Fragment Shader
        unsigned int fragmentShaderID;
        if (!CreateShader(fragmentShader, gl::GL_FRAGMENT_SHADER, fragmentShaderID))
        {
            std::cerr << "FRAGMENT SHADER NOT COMPILED" << std::endl;
            system("pause");
        }


        //Program Shader
        m_id = gl::glCreateProgram();
        gl::glAttachShader(m_id, vertexShaderID);
        gl::glAttachShader(m_id, fragmentShaderID);
        gl::glLinkProgram(m_id);

        gl::GLint success;
        gl::glGetProgramiv(m_id, gl::GL_LINK_STATUS, &success);

        if (!success) 
        {
            gl::GLchar infoLog[1024];
            gl::glGetShaderInfoLog(m_id, 1024, nullptr, infoLog);
            std::cerr << "ERROR LINK SHADER: \n" << infoLog;
        }
        else 
        {
            m_isCompiled = true;
        }

        gl::glDeleteShader(vertexShaderID);
        gl::glDeleteShader(fragmentShaderID);
	}

    ShaderProgram::~ShaderProgram() {
        gl::glDeleteProgram(m_id);
    }

    bool ShaderProgram::CreateShader(const std::string& source, const gl::GLenum shaderType, gl::GLuint& shaderID) 
    {
        shaderID = gl::glCreateShader(shaderType);
        const char* code = source.c_str();
        gl::glShaderSource(shaderID, 1, &code, NULL);
        gl::glCompileShader(shaderID);

        gl::GLint success;
        gl::glGetShaderiv(shaderID, gl::GL_COMPILE_STATUS, &success);

        if (!success)
        {
            gl::GLchar infoLog[1024];
            gl::glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cerr << "ERROR SHADER: \n" << infoLog;
            return false;
        }
        return true;
    }

    void ShaderProgram::Use() const {
        gl::glUseProgram(m_id);
    }

    void ShaderProgram::SetTexture(const std::string& name, const gl::GLint value)
    {
        gl::glUniform1i(gl::glGetUniformLocation(m_id, name.c_str()), value);
    }

    void ShaderProgram::SetUniformMax4fv(const std::string& name, const glm::mat4& matrix)
    {
        gl::glUniformMatrix4fv(gl::glGetUniformLocation(m_id, name.c_str()), 1, gl::GL_FALSE, glm::value_ptr(matrix));
    }
}
