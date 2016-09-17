#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>

//NOTE: Texture2D will be responsible for loading the data into the GPU and
//      keeping track of it's attributes (width, height, id)

class Texture2D
{
public:
  Texture2D(std::string textureAssetPath);
  ~Texture2D();
  void bind();
  GLuint ID;
  int width;
  int height;
private:
  int components;
};


#endif
