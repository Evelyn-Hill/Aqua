#pragma once
#include <cstddef>
#include <string>
#include <unordered_map>
#include <memory>

#include <Aqua/Core/PNGImage.hpp>
#include <Aqua/Core/Log.hpp>
#include <Aqua/Core/Assert.hpp>

namespace Aqua {
using PNGMap = std::unordered_map<std::string, PNGImage*>;
class AssetManager {
public:
	AssetManager(std::string assetRootFolder);
	~AssetManager();

	enum AssetType {
		PNG_IMG,
	};

	enum LoadResult {
		SUCCESS,
		FAILURE,
	};

	LoadResult Load(AssetType type, std::string name);

	template<typename T>
	T* GetAsset(std::string name) {
		T* result = NULL;
		if (std::is_same_v<T, PNGImage>) {
			ASSERT(pngMap != NULL, "PNG Map Doesnt exist!");
			if(pngMap->contains(name)) {
				Aqua::Log::AquaLog()->Info("Loading PNG: ", name);
				result = pngMap->at(name);
			} else {
				result = NULL;
			}
		} 
		
		if (result == NULL) {
			Aqua::Log::AquaLog()->Error("Cannot retrieve image: ", name);
		}

		return result;
	}

private:
	std::string assetRootFolder = "assets/";
	std::unique_ptr<PNGMap> pngMap = NULL;
	LoadResult LoadPNG(std::string path);
};
}
