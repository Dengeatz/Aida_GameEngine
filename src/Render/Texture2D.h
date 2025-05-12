#pragma once
#include <glbinding/gl/types.h>

#include <glbinding/gl/enum.h>

namespace Render
{
	class Texture2D 
	{
	public:
		Texture2D(const gl::GLuint width,
			const gl::GLuint height,
			const unsigned char* data,
			const unsigned int channels,
			const gl::GLenum filter,
			const gl::GLenum wrapMode);
		~Texture2D();
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator = (const Texture2D&) = delete;
		Texture2D& operator = (Texture2D&& texture2d);
		Texture2D(Texture2D&& texture2d);
		void SetMultipleTextures(const Texture2D&, const gl::GLuint id);
		void Bind() const;

	private:
		gl::GLuint m_id;
		gl::GLenum m_mode;
		unsigned int m_width;
		unsigned int m_height;
	};
}