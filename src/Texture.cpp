#include "Aqua/Core/PNGImage.hpp"
#include <Aqua/Core/Texture.hpp>

Aqua::Texture::Texture(std::shared_ptr<PNGImage> img, TextureType type,
                       TextureWrap wrap) {
  glGenTextures(1, &texture);

  glBindTexture(type, texture);

  glTexParameteri(type, wrapX, wrap);
  glTexParameteri(type, wrapY, wrap);
  glTexParameteri(type, minFilter, TextureFilering::MIPMAP_LINEAR);
  glTexParameteri(type, magFilter, TextureFilering::LINEAR);

  glTexImage2D(TextureType::TWOD, MipMapLevel::ZERO, ColorFormat::RGB,
               img->width, img->height, 0, ColorFormat::RGB,
               DataFormat::UNSIGNED_BYTE, img->imageData);

  // NOTE: Not sure if we need mipmaps for the current game,
  // leaving this in for future proofing even if it has a negative
  // impact on Dif
  glGenerateMipmap(texture);
}

Aqua::Texture::~Texture() {}
