#pragma once
#include <Aqua/Core/Types.hpp>

struct PNGImage {
	PNGImage() {};

	int width, height, nrChannels;
	u8* imageData; 
};
