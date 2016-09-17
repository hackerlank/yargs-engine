#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"

class Shader
{
private:
  void checkCompileErrors(GLuint object, std::string type);
public:
  GLuint programID;

  Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
  void useShader();

  void setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
  void setInt(const GLchar *name, GLint value);

  void setVec2(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
  void setVec2(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);

  void setVec3(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
  void setVec3(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);

  void setVec4(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
  void setVec4(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);

  void setMat4(const GLchar *name, const glm::mat4 &matrix);
};


#endif
