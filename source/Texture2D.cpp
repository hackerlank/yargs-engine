#include "Texture2D.h"

#include "debug.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#include "libs/stb_image.h"

Texture2D::Texture2D(std::string textureAssetPath)
{
  glGenTextures(1, &this->ID);
  unsigned char* image_data = stbi_load(textureAssetPath.c_str(),
                                        &this->width,
                                        &this->height,
                                        &this->components,
                                        0);

  glBindTexture(GL_TEXTURE_2D, this->ID);

  if(this->components == 3) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width,
                 this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
  }
  else if(this->components == 4) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width,
                 this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
  }
  else {
    debug("ERROR loading texture at %s. Components %d", textureAssetPath.c_str(), components);
    stbi_image_free(image_data);
    return;
  }
  debug("Loaded image: %s, with %d components, %d x %d",
        textureAssetPath.c_str(), components, width, height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, 0); //unbind texture

  stbi_image_free(image_data);
}

Texture2D::~Texture2D()
{
  //Free the texture
  glDeleteTextures(1, &this->ID);
}

void Texture2D::bind()
{
  glBindTexture(GL_TEXTURE_2D, this->ID);
}
