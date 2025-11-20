#pragma once

#include <memory>
#include <string>

#include <unordered_map>

#include <Aqua/Core/Assert.hpp>

#include <Aqua/Core/Log.hpp>
#include <Aqua/Core/PNGImage.hpp>
#include <Aqua/Core/Texture.hpp>


namespace Aqua {
class AssetManager {
public:
  using PNGMap = std::unordered_map<std::string, std::shared_ptr<PNGImage>>;
  using TEXMap = std::unordered_map<std::string, std::shared_ptr<Texture>>;

  AssetManager(std::string assetRootFolder);
  ~AssetManager();

  enum AssetType {
    PNG_IMG,
    TEXTURE,
  };

  enum LoadResult {
    SUCCESS,
    FAILURE,
  };

  LoadResult Load(AssetType type, std::string name);

  template <typename T> std::shared_ptr<T> GetAsset(std::string name) {
    if (std::is_same_v<T, PNGImage>) {
      ASSERT(pngMap != nullptr, "PNG Map Doesnt exist!");
      if (pngMap->contains(name)) {
        return pngMap->at(name);
      }
    } else if (std::is_same_v<T, Texture>) {
      ASSERT(texMap != nullptr, "texMap doesnt exist!");
      if (texMap->contains(name)) {
        return texMap->at(name);
      }
    } else {
      Aqua::Log::AquaLog()->Error("Invalid asset type!");
    }

    return nullptr;
  }

private:
  std::string assetRootFolder = "assets/";
  std::unique_ptr<PNGMap> pngMap = nullptr;
  std::unique_ptr<TEXMap> texMap = nullptr;

  LoadResult LoadPNG(std::string path);
  LoadResult LoadTexture(std::string name);
};
}
