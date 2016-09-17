#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

#include "Utility.h"

//from http://learnopengl.com/#!Getting-started/Shaders
Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
  std::string vertexShaderCode;
  std::string fragmentShaderCode;

  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensures ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);
  try
  {
      // Open files
      vShaderFile.open(vertexShaderPath);
      fShaderFile.open(fragmentShaderPath);
      std::stringstream vShaderStream, fShaderStream;
      // Read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // close file handlers
      vShaderFile.close();
      fShaderFile.close();
      // Convert stream into GLchar array
      vertexShaderCode = vShaderStream.str();
      fragmentShaderCode = fShaderStream.str();
  }
  catch(std::ifstream::failure e)
  {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  const GLchar* vShaderCode = vertexShaderCode.c_str();
  const GLchar* fShaderCode = fragmentShaderCode.c_str();

  GLuint vertexShaderHandle, fragmentShaderHandle;
  GLint success;
  GLchar infoLog[512];

  vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderHandle, 1, &vShaderCode, 0);
  glCompileShader(vertexShaderHandle);


  glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShaderHandle, 512, NULL, infoLog);
    std::cout << "Line: " << __LINE__ << " ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  };

  fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderHandle, 1, &fShaderCode, 0);
  glCompileShader(fragmentShaderHandle);

  glGetShaderiv(fragmentShaderHandle, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(fragmentShaderHandle, 512, NULL, infoLog);
    std::cout << "Line: " << __LINE__ << " ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  };

  this->programID = glCreateProgram();
  glAttachShader(this->programID, vertexShaderHandle);
  glAttachShader(this->programID, fragmentShaderHandle);
  glLinkProgram(this->programID);

  glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
    std::cout << "Line: " << __LINE__ << " ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  // Delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(vertexShaderHandle);
  glDeleteShader(fragmentShaderHandle);
}
void Shader::useShader()
{
  glUseProgram(this->programID);
}


void Shader::setMat4(const GLchar *name, const glm::mat4 &matrix)
{
  this->useShader();
  glUniformMatrix4fv(glGetUniformLocation(this->programID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setInt(const GLchar *name, GLint value)
{
  this->useShader();
  glUniform1i(glGetUniformLocation(this->programID, name), value);
}
