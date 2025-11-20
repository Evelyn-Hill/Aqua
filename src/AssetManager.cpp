#include <Aqua/Core/AssetManager.hpp>
//#include <Aqua/Core/Log.hpp>
#include <memory>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


Aqua::AssetManager::AssetManager(std::string assetRootFolder) {
	this->assetRootFolder = assetRootFolder;
}

Aqua::AssetManager::~AssetManager() {
	pngMap->clear();
	texMap->clear();
}

Aqua::AssetManager::LoadResult Aqua::AssetManager::Load(Aqua::AssetManager::AssetType type, std::string name) {
	switch(type) {
		case Aqua::AssetManager::AssetType::PNG_IMG:
			return LoadPNG(name);
			break;
		case Aqua::AssetManager::AssetType::TEXTURE:
			return LoadTexture(name);
			break;
		default:
			Aqua::Log::AquaLog()->Error("Invalid asset type!");
			return AssetManager::FAILURE;
	}
}

Aqua::AssetManager::LoadResult Aqua::AssetManager::LoadPNG(std::string name) {	
	if (pngMap == nullptr) {
		pngMap = std::make_unique<PNGMap>();
	}

	std::shared_ptr<PNGImage> png = std::make_shared<PNGImage>();
	
	std::string loadPath = std::string(assetRootFolder + name + ".png");

	png->imageData = stbi_load(loadPath.c_str(), &png->width, &png->height, &png->nrChannels, 0);

	if (!png->imageData || !png->width || !png->height || !png->nrChannels) {
		Aqua::Log::AquaLog()->Error("PNGERR: Could not load image: ", name);
		return AssetManager::FAILURE;
	}

	pngMap->emplace(name, png);
	Aqua::Log::AquaLog()->Info("Loaded image: ", name);
	return AssetManager::SUCCESS;
}

Aqua::AssetManager::LoadResult Aqua::AssetManager::LoadTexture(std::string name) {
	if (LoadPNG(name) == AssetManager::LoadResult::FAILURE) {
		Aqua::Log::AquaLog()->Error("Could not create texture: ", name, " failed to load image!");
		return AssetManager::FAILURE;
	}
		
	std::shared_ptr<PNGImage> img = pngMap->at(name);

	if (img == nullptr) {
		Aqua::Log::AquaLog()->Error("Could not load texture: ", name);
		return AssetManager::FAILURE;
	};

	if (texMap == nullptr) {
		texMap = std::make_unique<TEXMap>();
	}

	std::shared_ptr<Texture> tex = std::make_shared<Texture>(img, Texture::TextureType::TWOD, Texture::TextureWrap::REPEAT);
	
	if (tex == nullptr) {
		Aqua::Log::AquaLog()->Error("Could not load texture: ", name);
		return AssetManager::FAILURE;
	}

	texMap->emplace(name, tex);
	Aqua::Log::AquaLog()->Info("Loaded texture: ", name);
	return AssetManager::SUCCESS;
}
