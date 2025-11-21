#pragma once

#include <memory>
#include <string>

#include <unordered_map>

#include <Aqua/Core/Assert.hpp>

#include <Aqua/Core/Log.hpp>
#include <Aqua/Core/PNGImage.hpp>
#include <Aqua/Core/Texture.hpp>
#include <Aqua/Core/Shader.hpp>


namespace Aqua {
class AssetManager {
public:
  using TEXMap    = std::unordered_map<std::string, Texture>;
  using ShaderMap = std::unordered_map<std::string, Shader>;

  AssetManager();
  ~AssetManager();

  // Takes a path to a PNG image and returns an OpenGL Texturel
  Texture*  CreateTexture(std::string pngPath, std::string name);
  Shader*   CreateShader(std::string vertexPath, std::string fragmentPath, std::string name);


  Texture*  GetTexture(std::string name);
  Shader*   GetShader(std::string name);

private:
  std::string assetRootFolder = "assets/";

  std::unique_ptr<TEXMap>    texMap  = nullptr;
  std::unique_ptr<ShaderMap> shadMap = nullptr;
  
  // This should not be used aside from as a helper function for Load Texture.
  // FIXME: This should maybe become a unique_ptr at some point???
  PNGImage* LoadPng(std::string path);

};
}
