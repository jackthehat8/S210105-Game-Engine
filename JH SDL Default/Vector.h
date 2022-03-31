#pragma once
#include <math.h>

struct Vector2f {
    float x;
    float y;
	Vector2f(float x_= 0.0f, float y_ = 0.0f) { x = x_; y = y_; }
};

//This section is from the SFML library found at: https://www.sfml-dev.org/
inline Vector2f operator -(const Vector2f& right)
{
    return Vector2f(-right.x, -right.y);
}

inline Vector2f& operator +=(Vector2f& left, const Vector2f& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}

inline Vector2f& operator -=(Vector2f& left, const Vector2f& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}

inline Vector2f operator +(const Vector2f& left, const Vector2f& right)
{
    return Vector2f(left.x + right.x, left.y + right.y);
}


inline Vector2f operator -(const Vector2f& left, const Vector2f& right)
{
    return Vector2f(left.x - right.x, left.y - right.y);
}


inline Vector2f operator *(const Vector2f& left, float right)
{
    return Vector2f(left.x * right, left.y * right);
}

inline Vector2f operator *(float left, const Vector2f& right)
{
    return Vector2f(right.x * left, right.y * left);
}


inline Vector2f& operator *=(Vector2f& left, float right)
{
    left.x *= right;
    left.y *= right;

    return left;
}


inline Vector2f operator /(const Vector2f& left, float right)
{
    return Vector2f(left.x / right, left.y / right);
}


inline Vector2f& operator /=(Vector2f& left, float right)
{
    left.x /= right;
    left.y /= right;

    return left;
}

inline Vector2f operator *(const Vector2f& left, int right)
{
    return Vector2f(left.x * right, left.y * right);
}


inline Vector2f operator *(int left, const Vector2f& right)
{
    return Vector2f(right.x * left, right.y * left);
}


inline Vector2f& operator *=(Vector2f& left, int right)
{
    left.x *= right;
    left.y *= right;

    return left;
}

inline Vector2f operator /(const Vector2f& left, int right)
{
    return Vector2f(left.x / right, left.y / right);
}


inline Vector2f& operator /=(Vector2f& left, int right)
{
    left.x /= right;
    left.y /= right;

    return left;
}


inline bool operator ==(const Vector2f& left, const Vector2f &right)
{
    return (left.x == right.x) && (left.y == right.y);
}


inline bool operator !=(const Vector2f& left, const Vector2f& right)
{
    return (left.x != right.x) || (left.y != right.y);
}
//end reference

//This is from Chris'  AIFramework code from the AI For Games Module

inline float Distance(const Vector2f& a, const Vector2f& b)
{
    Vector2f c = a - b;

    return sqrtf(c.x * c.x + c.y * c.y);
}

inline float Magnitude(const Vector2f& a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}
//end reference