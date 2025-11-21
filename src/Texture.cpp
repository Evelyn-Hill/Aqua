#include "Aqua/Core/PNGImage.hpp"
#include <Aqua/Core/Texture.hpp>
#include <Aqua/Core/Assert.hpp>

Aqua::Texture::Texture(PNGImage* img, TextureType type,
                       TextureWrap wrap) {
  image = img;

  ASSERT(img != nullptr, "Null image data passed to texture constructor!");

  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, minFilter, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, magFilter, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
               img->width, img->height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, img->imageData);

  // NOTE: Not sure if we need mipmaps for the current game,
  // leaving this in for future proofing even if it has a negative
  // impact on Dif
 // glGenerateMipmap(texture);

}

Aqua::Texture::~Texture() {
    delete image;
}


void Aqua::Texture::Bind() {
  glBindTexture(GL_TEXTURE_2D, texture);
}

vec2 Aqua::Texture::Size() {
  return vec2((float)image->width, (float)image->height);
}

