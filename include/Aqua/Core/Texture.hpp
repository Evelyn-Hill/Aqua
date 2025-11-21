#pragma once
#include <glad/glad.h>
#include <Aqua/Core/Types.hpp>
#include <Aqua/Core/PNGImage.hpp>
#include <string>

namespace Aqua {
class Texture {
public:
	
	enum TextureType : int {
		TWOD = GL_TEXTURE_2D,
	};

	enum TextureWrap : int {
		REPEAT = GL_REPEAT
	};
	
	enum TextureFilering : int {
		MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
		LINEAR = GL_LINEAR,
	};

	enum MipMapLevel : int {
		ZERO = 0,
	};

	enum ColorFormat : int {
		RGB = GL_RGB,
		RGBA = GL_RGBA,
	};

	enum DataFormat : int {
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE
	};

	Texture(PNGImage* image, TextureType type, TextureWrap wrap);
	~Texture();

	void Bind();

	vec2 Size();

	vec2 GetSegments();

	void SetSegmentation(vec2 segments);

private:
	const int textureType = TextureType::TWOD;
	const int wrapX = GL_TEXTURE_WRAP_S;
	const int wrapY = GL_TEXTURE_WRAP_T;
	const int minFilter = GL_TEXTURE_MIN_FILTER;
	const int magFilter = GL_TEXTURE_MAG_FILTER;
	int wrapping = TextureWrap::REPEAT;
	
	// used for sprite sheets.
	vec2 sheetSegments = vec2(1, 1);
	
	PNGImage* image;
	GLuint texture;
};

}
