/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Math.h"


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float>::Vector2()
:
   x(0.0),
   y(0.0)
{}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float>::Vector2(Float vx, Float vy)
:
   x(vx),
   y(vy)
{}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float>::Vector2(Float v[2])
:
   x(v[0]),
   y(v[1])
{}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float>::Vector2(const Vector2& v)
:
   x(v.x),
   y(v.y)
{}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector2<Float>::set(Float fx, Float fy)
{
   x=fx;
   y=fy;
}


//-------------------------------------------------------------------------//
template <class Float>
inline Float& Vector2<Float>::operator[] (int i) const
{
   return ((Float*)this)[i];
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float>::operator Float* ()
{
   return (Float*)this;
}


//-------------------------------------------------------------------------//
template <class Float>
inline bool Vector2<Float>::operator== (const Vector2& v) const
{
   return (x==v.x && y==v.y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline bool Vector2<Float>::operator!= (const Vector2& v) const
{
   return (x!=v.x || y!=v.y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float>& Vector2<Float>::operator+= (const Vector2<Float>& v)
{
   x+=v.x;
   y+=v.y;
   return *this;
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float>& Vector2<Float>::operator-= (const Vector2<Float>& v)
{
   x-=v.x;
   y-=v.y;
   return *this;
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float>& Vector2<Float>::operator*= (Float a)
{
    x*=a;
    y*=a;
    return *this;
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float>& Vector2<Float>::operator/= (Float a)
{
   x/=a;
   y/=a;
   return *this;
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float> Vector2<Float>::operator+ (const Vector2<Float>& v) const
{
   return Vector2(x+v.x, y+v.y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float> Vector2<Float>::operator- (const Vector2<Float>& v) const
{
   return Vector2(x-v.x, y-v.y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Float Vector2<Float>::operator^ (const Vector2<Float>& v) const
{
   return (x*v.x + y*v.y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float> Vector2<Float>::operator* (Float a) const
{
   return Vector2(a*x, a*y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float> Vector2<Float>::operator/ (Float a) const
{
   return Vector2(x/a, y/a);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float> Vector2<Float>::operator- () const
{
   return Vector2<Float>(-x,-y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float> operator* (Float a, const Vector2<Float>& v)
{
   return Vector2<Float>(a*v.x, a*v.y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline std::ostream& operator<< (std::ostream& s, const Vector2<Float>& v)
{
   return s << '(' << v.x << ", " << v.y << ')';
}

//-------------------------------------------------------------------------//
template <class Float>
inline Float Vector2<Float>::norm() const
{
   return fSqrt(x*x + y*y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Float Vector2<Float>::norm2() const
{
   return (x*x + y*y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Float Vector2<Float>::dot(const Vector2<Float>& v) const
{
   return (x*v.x + y*v.y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Float dot(const Vector2<Float>& v, const Vector2<Float>& u)
{
   return (v.x*u.x + v.y*u.y);
}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector2<Float>::neg()
{
   x = -x;
   y = -y;
}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector2<Float>::normalize()
{
   Float n=fSqrt(x*x + y*y);

   x /= n;
   y /= n;
}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector2<Float>::add(const Vector2<Float>& v, const Vector2<Float>& u)
{
   x = v.x + u.x;
   y = v.y + u.y;
}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector2<Float>::sub(const Vector2& v, const Vector2& u)
{
   x = v.x - u.x;
   y = v.y - u.y;
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector2<Float> fLerp(Vector2<Float> a, Vector2<Float> b, float t)
{
    return a + (b-a)*t;
}
