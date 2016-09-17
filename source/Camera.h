#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"


#include "GameObject.h"
#include "Shader.h"

class Camera : public GameObject
{
public:
  Camera(Shader& shader);
  virtual void Update(const float dt, InputHandler* inputHandler);
private:
  glm::vec3 cameraPosition;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;
  glm::mat4 viewMatrix;
  Shader& shader;
};

#endif
