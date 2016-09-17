#include "Vector2f.h"
#include <math.h>

#include "../debug.h"

Vector2f::Vector2f()
{
  x = 0.0f;
  y = 0.0f;
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
Vector2f Vector2f::operator*(const float scaleAmount)
{
  float X = x*scaleAmount;
  float Y = y*scaleAmount;
  return Vector2f(X, Y);
}
void Vector2f::operator*=(const float scaleAmount)
{
  x *= scaleAmount;
  y *= scaleAmount;
}
void Vector2f::operator=(const Vector2f& other)
{
  x = other.x;
  y = other.y;
}
void Vector2f::operator=(const int& setTo)
{
  x = setTo;
  y = setTo;
}
void Vector2f::operator=(const float& setTo)
{
  x = setTo;
  y = setTo;
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
  if(length > 0){
    this->x = this->x/length;
    this->y = this->y/length;
  }
}

float max(float first, float second)
{
  if(first > second) return first;
  return second;
}
float min(float first, float second)
{
  if(first < second) return first;
  return second;
}

void Vector2f::LerpTo(Vector2f to, float amount)
{

}

Vector2f Vector2f::Lerp(Vector2f from, Vector2f to, float t)
{
  t = max(0.0f, min(t, 1.0f)); //clamp amount between 0 and 1
  //t = t*t*t * (t * (6.0f*t - 15.0f) + 10.0f);
  float x = from.x*(1-t) + to.x*t;  //interpolate x
  float y = from.y*(1-t) + to.y*t;  //interpolate y

  return Vector2f(x, y);
}
