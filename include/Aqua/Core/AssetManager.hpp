#pragma once
#include <cstddef>
#include <string>
#include <unordered_map>
#include <memory>

#include <Aqua/Core/PNGImage.hpp>

#include <Aqua/Core/Log.hpp>

namespace Aqua {
using PNGMap = std::unordered_map<std::string, PNGImage>;
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

	//TODO: I dont love this API. You should just pass the type as a
	// template argument and it should just work. This is fine for now. -plum
	template<typename T>
	T GetAsset(std::string name) {
		if (std::is_same_v<T, PNGImage>) {
			if (pngMap == NULL) {
				Aqua::Log::AquaLog()->Error("PNGMap doesnt exist, cannot retrieve!");
				return PNGImage();
			}

			if(pngMap->contains(name)) {
				return pngMap->at(name);
			}
		} else {
			Aqua::Log::AquaLog()->Error("Invalid asset type!");
		}

		return T();
	}

private:
	std::string assetRootFolder = "assets/";
	std::unique_ptr<PNGMap> pngMap = NULL;
	LoadResult LoadPNG(std::string path);
};
}
