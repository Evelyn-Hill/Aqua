#pragma once
#include <Aqua/Core/Types.hpp>
#include <stb/stb_image.h>
#include <string>

struct PNGImage {
	PNGImage(std::string path) {
		stbi_set_flip_vertically_on_load(true);
		imageData = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	};

	~PNGImage() {
		stbi_image_free(imageData);
	};

	int width, height, nrChannels;
	u8* imageData; 
};
