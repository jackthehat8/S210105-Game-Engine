#pragma once
#include <math.h>

/// This stores an x and y component for use in positions
///
/// This allows for vector maths
struct Vector2f {
    float x;
    float y;
	/// makes a vector with x and y values
	Vector2f(float x_= 0.0f, float y_ = 0.0f) { x = x_; y = y_; }
};

//This section is from the SFML library found at: https://www.sfml-dev.org/

/// inverts the values 
inline Vector2f operator -(const Vector2f& right)
{
    return Vector2f(-right.x, -right.y);
}

/// adds 2 vectors together (x1 to x2 and y1 to y2)
inline Vector2f& operator +=(Vector2f& left, const Vector2f& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}

/// subtracts a vector from another (x1-x2 and y1-y2)
inline Vector2f& operator -=(Vector2f& left, const Vector2f& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}

/// adds 2 vectors together (x1 to x2 and y1 to y2)
inline Vector2f operator +(const Vector2f& left, const Vector2f& right)
{
    return Vector2f(left.x + right.x, left.y + right.y);
}

/// subtracts a vector from another (x1-x2 and y1-y2)
inline Vector2f operator -(const Vector2f& left, const Vector2f& right)
{
    return Vector2f(left.x - right.x, left.y - right.y);
}

/// multiplies 2 vectors together
inline Vector2f operator *(const Vector2f& left, float right)
{
    return Vector2f(left.x * right, left.y * right);
}

/// multiplies a vector by a float
inline Vector2f operator *(float left, const Vector2f& right)
{
    return Vector2f(right.x * left, right.y * left);
}

/// multiplies a vector by a float
inline Vector2f& operator *=(Vector2f& left, float right)
{
    left.x *= right;
    left.y *= right;

    return left;
}

/// divides a vector by a float
inline Vector2f operator /(const Vector2f& left, float right)
{
    return Vector2f(left.x / right, left.y / right);
}

/// divides a vector by a float
inline Vector2f& operator /=(Vector2f& left, float right)
{
    left.x /= right;
    left.y /= right;

    return left;
}
/// multiplies a vector by a int
inline Vector2f operator *(const Vector2f& left, int right)
{
    return Vector2f(left.x * right, left.y * right);
}

/// multiplies a vector by a int
inline Vector2f operator *(int left, const Vector2f& right)
{
    return Vector2f(right.x * left, right.y * left);
}

/// multiplies a vector by a int
inline Vector2f& operator *=(Vector2f& left, int right)
{
    left.x *= right;
    left.y *= right;

    return left;
}

/// divides a vector by a int
inline Vector2f operator /(const Vector2f& left, int right)
{
    return Vector2f(left.x / right, left.y / right);
}

/// divides a vector by a int
inline Vector2f& operator /=(Vector2f& left, int right)
{
    left.x /= right;
    left.y /= right;

    return left;
}

/// checks if an vector is equal to another
inline bool operator ==(const Vector2f& left, const Vector2f &right)
{
    return (left.x == right.x) && (left.y == right.y);
}

/// checks if an vector is NOT equal to another
inline bool operator !=(const Vector2f& left, const Vector2f& right)
{
    return (left.x != right.x) || (left.y != right.y);
}
//end reference

//This is from Chris'  AIFramework code from the AI For Games Module

/// calculates the distance between 2 vectors
inline float Distance(const Vector2f& a, const Vector2f& b)
{
    Vector2f c = a - b;

    return sqrtf(c.x * c.x + c.y * c.y);
}

///calculates the magnitude of a vector
inline float Magnitude(const Vector2f& a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}
//end reference