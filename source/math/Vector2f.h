#ifndef __VECTOR2_H__
#define __VECTOR2_H__

struct Vector2f
{
  float x;
  float y;

  Vector2f();
  Vector2f(float x, float y);

  Vector2f operator+(const Vector2f& other);
  Vector2f operator-(const Vector2f& other);
  Vector2f operator*(const float scaleAmount);
  void operator*=(const float scaleAmount);
  void operator=(const Vector2f& other);
  void operator=(const int& setTo);
  void operator=(const float& setTo);

  Vector2f getNormal();
  float getLength();
  void scale(float amount);
  void normalize();

  void LerpTo(Vector2f to, float t);

  static Vector2f Lerp(Vector2f from, Vector2f to, float amount);

};


#endif
