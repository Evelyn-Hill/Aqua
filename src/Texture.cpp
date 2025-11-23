#include "Aqua/Core/PNGImage.hpp"
#include <Aqua/Core/Assert.hpp>
#include <Aqua/Core/Texture.hpp>

Aqua::Texture::Texture(PNGImage *img, TextureType type, TextureWrap wrap) {
  image = img;

  ASSERT(img != nullptr, "Null image data passed to texture constructor!");

  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, minFilter, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, magFilter, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, img->imageData);

  size.x = img->width;
  size.y = img->height;
}

Aqua::Texture::~Texture() { delete image; }

void Aqua::Texture::Bind() { glBindTexture(GL_TEXTURE_2D, texture); }

vec2 Aqua::Texture::Size() {
  return vec2((float)image->width, (float)image->height);
}

vec2 Aqua::Texture::GetSegments() { return sheetSegments; }
int Aqua::Texture::GetActiveSprite() { return activeSprite; }

void Aqua::Texture::SetSegmentation(vec2 segments) {
  sheetSegments = segments;
  bool zeroSegmentError = false;
  if (segments.x == 0) {
    segments.x = 1;
    zeroSegmentError = true;
  }
  if (segments.y == 0) {
    segments.y = 1;
    zeroSegmentError = true;
  }

  if (zeroSegmentError) {
    Aqua::Log::AquaLog()->Warn("Cannot have 0 sprite segments, incremented 0 to 1");
  }

  size = vec2(image->width / segments.x, image->height / segments.y);
  segmentCount = segments.x * segments.y;
}

void Aqua::Texture::SetActiveSprite(int idx) {
  // NOTE: This allows us to just always count up when we're doing animations
  // while still being able to pick any given sprite and never going out of
  // range. - eph
  activeSprite = idx % segmentCount;
}
