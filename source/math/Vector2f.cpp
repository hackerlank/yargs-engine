#include "Vector2f.h"
#include <math.h>


Vector2f::Vector2f()
{
  x = 0;
  y = 0;
}
Vector2f::Vector2f(float x, float y)
{
  this->x = x;
  this->y = y;
}

Vector2f Vector2f::operator+(const Vector2f& other)
{
  float X = x + other.x;
  float Y = y + other.y;
  return Vector2f(X, Y);
}
Vector2f Vector2f::operator-(const Vector2f& other)
{
  float X = x - other.x;
  float Y = y - other.y;
  return Vector2f(X, Y);
}
Vector2f Vector2f::operator*(const int scaleAmount)
{
  float X = x * scaleAmount;
  float Y = y * scaleAmount;
  return Vector2f(X, Y);
}

Vector2f Vector2f::getNormal()
{
  float length = getLength();
  return Vector2f(x/length, y/length);
}
float Vector2f::getLength()
{
  return sqrtf(x*x + y*y);
}
void Vector2f::scale(float amount)
{
  this->x = this->x * amount;
  this->y = this->y * amount;
}
void Vector2f::normalize()
{
  float length = getLength();
  this->x = this->x/length;
  this->y = this->y/length;
  return;
}
