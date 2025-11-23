#pragma once
#include <glad/glad.h>
#include <Aqua/Core/Types.hpp>
#include <Aqua/Core/PNGImage.hpp>
#include <array>

namespace Aqua {
// NOTE: For all intents and purposes right now a "sprite" and "texture" are the same thing.
// until I need to separate them they will stay interlinked as they are. -eph
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
	int GetActiveSprite();
	
	// This sets the segmentation for sprite sheets, updates the TexCoords,
	// and updates the size of the texture.
	void SetSegmentation(vec2 segments);

	void SetActiveSprite(int idx);

private:
	const int textureType = TextureType::TWOD;

	// NOTE: Im not sure yet if these can be constexpr bc of the external dependency.
	// will look into it if it becomes a problem -eph
	const int wrapX = GL_TEXTURE_WRAP_S;
	const int wrapY = GL_TEXTURE_WRAP_T;
	const int minFilter = GL_TEXTURE_MIN_FILTER;
	const int magFilter = GL_TEXTURE_MAG_FILTER;
	constexpr static int TEX_COORD_ARR_LEN = 6;
	int wrapping = TextureWrap::REPEAT;

	vec2 size;
	
	/* used for sprite sheets. */
	vec2 sheetSegments = vec2(1, 1);
	int activeSprite = 0;
	int segmentCount = 1;
		
	PNGImage* image;
	GLuint texture;
};

}
