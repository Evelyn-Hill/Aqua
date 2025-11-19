#include <Aqua/Core/AssetManager.hpp>
#include <Aqua/Core/Log.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace Aqua;

AssetManager::AssetManager(std::string assetRootFolder) {
	this->assetRootFolder = assetRootFolder;
}

AssetManager::~AssetManager() {
	pngMap->clear();
}

AssetManager::LoadResult AssetManager::Load(AssetManager::AssetType type, std::string name) {
	switch(type) {
		case Aqua::AssetManager::AssetType::PNG_IMG:
			return LoadPNG(name);
			break;
		default:
			Aqua::Log::AquaLog()->Error("Invalid asset type!");
			return AssetManager::LoadResult::FAILURE;
	}
}

AssetManager::LoadResult AssetManager::LoadPNG(std::string name) {	
	if (pngMap == NULL) {
		pngMap = std::make_unique<PNGMap>();
	}

	PNGImage png;
	
	std::string loadPath = std::string(assetRootFolder + name + ".png");

	png.imageData = stbi_load(loadPath.c_str(), &png.width, &png.height, &png.nrChannels, 0);

	if (!png.imageData || !png.width || !png.height || !png.nrChannels) {
		Aqua::Log::AquaLog()->Error("PNGERR: Could not load image: ", name);
		return AssetManager::LoadResult::FAILURE;
	}

	pngMap->emplace(name, png);
	Aqua::Log::AquaLog()->Info("Loaded image: ", name);
	return AssetManager::LoadResult::SUCCESS;
}
