#include "Camera.h"

#include "debug.h"

Camera::Camera(Shader& shader) : cameraPosition(0.0f, 0.0f, 0.0f),
                   cameraFront(0.0f, 0.0f, -1.0f),
                   cameraUp(0.0f, 1.0f, 0.0f),
                   shader(shader)
{
  viewMatrix = glm::lookAt(cameraPosition,
  		                     cameraPosition+cameraFront,
  		                     cameraUp);
}

void Camera::Update(const float dt, InputHandler* inputHandler)
{
  debug("here");
  float cameraSpeed = 600.0f;
  if(inputHandler->isKeyHeldDown(KEY_LEFT)) {
    cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed*dt);
  }
  if(inputHandler->isKeyHeldDown(KEY_RIGHT)) {
    cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed*dt);
  }
  if(inputHandler->isKeyHeldDown(KEY_UP)) {
    cameraPosition -= cameraSpeed*dt * cameraUp;
  }
  if(inputHandler->isKeyHeldDown(KEY_DOWN)) {
    cameraPosition += cameraSpeed*dt * cameraUp;
  }


  debug("pos x %f", cameraPosition.x);
  viewMatrix = glm::lookAt(cameraPosition,
  		                     cameraPosition+cameraFront,
  		                     cameraUp);

  //TODO: Move shader out of this class, it really should be 
  //      something else setting this. Maybe the renderer? or shader?
  shader.setMat4("view", viewMatrix);
}
