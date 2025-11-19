#pragma once
#include <Aqua/Core/Types.hpp>
#include <stb/stb_image.h>

struct PNGImage {
	PNGImage() {};
	~PNGImage() {
		stbi_image_free(imageData);
	};

	int width, height, nrChannels;
	u8* imageData; 
};
