#include "Texture2D.h"
#include <glbinding/gl/functions.h>
#include <iostream>

namespace Render {
	Texture2D::Texture2D(const gl::GLuint width,
		const gl::GLuint height,
		const unsigned char* data,
		const unsigned int channels,
		const gl::GLenum filter,
		const gl::GLenum wrapMode) : m_width(width), m_height(height)
	{
		switch (channels) {
		case 4:
			m_mode = gl::GL_RGBA;
			break;
		case 3:
			m_mode = gl::GL_RGB;
			break;
		default:
			m_mode = gl::GL_RGB;
			break;
		}


		gl::glGenTextures(1, &m_id);
		gl::glBindTexture(gl::GL_TEXTURE_2D, m_id);
		gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, gl::GL_RGB, m_width, m_height, 0, m_mode, gl::GL_UNSIGNED_BYTE, data);

		gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_S, wrapMode);
		gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_T, wrapMode);
		gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, filter);
		gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, filter);

		gl::glGenerateMipmap(gl::GL_TEXTURE_2D);
		gl::glBindTexture(gl::GL_TEXTURE_2D, 0);

	}

	Texture2D& Texture2D::operator = (Texture2D&& texture2d) {
		gl::glDeleteTextures(1, &m_id);
		m_id = texture2d.m_id;
		texture2d.m_id = 0;
		m_mode = texture2d.m_mode;
		m_width = texture2d.m_width;
		m_height = texture2d.m_height;
		
		return *this;
	}

	Texture2D::Texture2D(Texture2D&& texture2d)
	{
		m_id = texture2d.m_id;
		texture2d.m_id = 0;
		m_mode = texture2d.m_mode;
		m_width = texture2d.m_width;
		m_height = texture2d.m_height;
	}

	Texture2D::~Texture2D() 
	{
		gl::glDeleteTextures(1, &m_id);
	}

	void Texture2D::Bind() const 
	{
		switch (m_id) {
		case 1:
			gl::glActiveTexture(gl::GL_TEXTURE0);
			break;
		case 2:
			gl::glActiveTexture(gl::GL_TEXTURE1);
			break;
		}
		gl::glBindTexture(gl::GL_TEXTURE_2D, m_id);
	}

}