#include <Aqua/Core/AssetManager.hpp>
#include <memory>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Aqua {
AssetManager::AssetManager() {}

AssetManager::~AssetManager() {
	texMap->clear();
	shadMap->clear();
}

PNGImage* AssetManager::LoadPng(std::string path) {
	PNGImage* png = new PNGImage(path);
	return png;
}

Texture* AssetManager::CreateTexture(std::string pngPath, std::string name) {
	PNGImage* img = LoadPng(pngPath);

	if (img == nullptr) {
		Aqua::Log::AquaLog()->Error("Could not load png: ", pngPath);
	}


	if (texMap == nullptr) {
		texMap = std::make_unique<TEXMap>();
	}

	Texture* tex = new Texture(img, Texture::TextureType::TWOD, Texture::TextureWrap::REPEAT);

	texMap->insert(std::pair<std::string, Texture*>(name, tex));
	ASSERT(texMap->contains(name), "Could not insert texture into map!");
	Aqua::Log::AquaLog()->Info("Loaded texture: ", name);
	return texMap->at(name);
}

Texture* AssetManager::GetTexture(std::string name) {
	ASSERT(texMap != nullptr, "Texture Map not initialized!");
	if (texMap->contains(name)) {
		return texMap->at(name);
	}

	Aqua::Log::AquaLog()->Error("Invalid texture name: ", name);
	return nullptr;
}

Shader* AssetManager::CreateShader(std::string vertexPath, std::string fragmentPath, std::string name) {
	Shader* shader = new Shader(vertexPath, fragmentPath);

	if (shadMap == nullptr) {
		shadMap = std::make_unique<ShaderMap>();
	}
	
	// NOTE: This may look like a silly way of doing things when emplace exists. The reason I am using insert
	// is due to explicit copying of the underlying data so that this stack allocated
	// shader can be copied into the map and I can later retrieve a reference to it. -plum
	shadMap->insert(std::pair<std::string, Shader*>(name, shader));
	ASSERT(shadMap->contains(name), "Could not insert shader into map!");
	//Aqua::Log::AquaLog()->Info("Loaded shader: ", name);
	return shadMap->at(name);
}

Shader* AssetManager::GetShader(std::string name) {
	ASSERT(shadMap != nullptr, "Shader Map not initialized!");
	if (shadMap->contains(name)) {
		return shadMap->at(name);
	}

	Aqua::Log::AquaLog()->Error("Invalid shader name: ", name);
	return nullptr;
}

}
