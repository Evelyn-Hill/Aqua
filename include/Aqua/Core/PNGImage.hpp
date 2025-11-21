#pragma once
#include <Aqua/Core/Types.hpp>
#include <Aqua/Core/Log.hpp>
#include <stb/stb_image.h>
#include <string>

struct PNGImage {
	PNGImage(std::string path) {
		//stbi_set_flip_vertically_on_load(true);
		imageData = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
		if (imageData == nullptr) {
			Aqua::Log::AquaLog()->Error("Could not load PNG Image: ", path);
		}
	};

	~PNGImage() {
		stbi_image_free(imageData);
	};

	int width, height, nrChannels;
	u8* imageData; 
};
