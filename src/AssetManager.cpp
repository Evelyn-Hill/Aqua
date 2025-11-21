#include <Aqua/Core/AssetManager.hpp>
//#include <Aqua/Core/Log.hpp>
#include <memory>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Aqua {
AssetManager::AssetManager() {
}

AssetManager::~AssetManager() {
	texMap->clear();
	shadMap->clear();
}

PNGImage* AssetManager::LoadPng(std::string path) {
	PNGImage* png = new PNGImage();
	
	std::string loadPath = std::string(path);

	png->imageData = stbi_load(loadPath.c_str(), &png->width, &png->height, &png->nrChannels, 0);

	if (!png->imageData || !png->width || !png->height || !png->nrChannels) {
		return nullptr;
	}

	return png;
}

std::shared_ptr<Texture> AssetManager::LoadTexture(std::string pngPath, std::string name) {
	PNGImage* img = LoadPng(pngPath);
	if (img == nullptr) {
		Aqua::Log::AquaLog()->Error("Could not load png: ", pngPath);
		return nullptr;
	}

	std::shared_ptr<Texture> tex = std::make_shared<Texture>(img, Texture::TextureType::TWOD, Texture::TextureWrap::REPEAT);
	
	if (tex == nullptr) {
		Aqua::Log::AquaLog()->Error("Could not load texture: ", name);
		return nullptr;
	}

	if (texMap == nullptr) {
		texMap = std::make_unique<TEXMap>();
	}

	texMap->emplace(name, tex);
	ASSERT(texMap->contains(name), "Could not insert texture into map!");
	Aqua::Log::AquaLog()->Info("Loaded texture: ", name);
	return tex;
}

std::shared_ptr<Texture> AssetManager::GetTexture(std::string name) {
	ASSERT(texMap != nullptr, "Texture Map not initialized!");
	if (texMap->contains(name)) {
		return texMap->at(name);
	}

	Aqua::Log::AquaLog()->Error("Invalid texture name: ", name);
	return nullptr;
}


std::shared_ptr<Shader> AssetManager::LoadShader(std::string vertexPath, std::string fragmentPath, std::string name) {
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexPath, fragmentPath);
	if (shader == nullptr) {
		Aqua::Log::AquaLog()->Error("Could not load shader: ", name);
		return nullptr;
	}

	if (shadMap == nullptr) {
		shadMap = std::make_unique<ShaderMap>();
	}
	
	shadMap->emplace(name, shader);
	ASSERT(shadMap->contains(name), "Could not insert shader into map!");
	Aqua::Log::AquaLog()->Info("Loaded shader: ", name);
	return shader;
}

std::shared_ptr<Shader> AssetManager::GetShader(std::string name) {
	ASSERT(shadMap != nullptr, "Shader Map not initialized!");
	if (shadMap->contains(name)) {
		return shadMap->at(name);
	}

	Aqua::Log::AquaLog()->Error("Invalid shader name: ", name);
	return nullptr;
}
 
}
