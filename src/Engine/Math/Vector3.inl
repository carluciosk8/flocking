/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Math.h"


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float>::Vector3()
:
   x(0.0),
   y(0.0),
   z(0.0)
{}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float>::Vector3(Float vx, Float vy, Float vz)
:
   x(vx),
   y(vy),
   z(vz)
{}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float>::Vector3(Float v[3])
:
   x(v[0]),
   y(v[1]),
   z(v[2])
{}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float>::Vector3(const Vector3& v)
:
   x(v.x),
   y(v.y),
   z(v.z)
{}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector3<Float>::set(Float fx, Float fy, Float fz)
{
   x=fx;
   y=fy;
   z=fz;
}


//-------------------------------------------------------------------------//
template <class Float>
inline Float& Vector3<Float>::operator[] (int i) const
{
   return ((Float*)this)[i];
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float>::operator Float* ()
{
   return (Float*)this;
}


//-------------------------------------------------------------------------//
template <class Float>
inline bool Vector3<Float>::operator== (const Vector3& v) const
{
   return (x==v.x && y==v.y && z==v.z);
}


//-------------------------------------------------------------------------//
template <class Float>
inline bool Vector3<Float>::operator!= (const Vector3& v) const
{
   return (x!=v.x || y!=v.y || z!=v.z);
}




//-------------------------------------------------------------------------//
template <class Float>
        inline Vector3<Float>& Vector3<Float>::operator+= (const Vector3<Float>& v)
{
    x+=v.x;
    y+=v.y;
    z+=v.z;
    return *this;
}


template <class Float>
        inline Vector3<Float>& Vector3<Float>::operator-= (const Vector3<Float>& v)
{
    x-=v.x;
    y-=v.y;
    z-=v.z;
    return *this;
}


template <class Float>
        inline Vector3<Float>& Vector3<Float>::operator*= (const Vector3<Float>& v)
{
    x*=v.x;
    y*=v.y;
    z*=v.z;
    return *this;
}


template <class Float>
        inline Vector3<Float>& Vector3<Float>::operator/= (const Vector3<Float>& v)
{
    x/=v.x;
    y/=v.y;
    z/=v.z;
    return *this;
}


template <class Float>
inline Vector3<Float>& Vector3<Float>::operator*= (Float a)
{
    x*=a;
    y*=a;
    z*=a;
    return *this;
}


template <class Float>
inline Vector3<Float>& Vector3<Float>::operator/= (Float a)
{
   x/=a;
   y/=a;
   z/=a;
   return *this;
}




//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float> Vector3<Float>::operator+(const Vector3<Float>& v) const
{
    return Vector3(x+v.x, y+v.y, z+v.z);
}


template <class Float>
inline Vector3<Float> Vector3<Float>::operator-(const Vector3<Float>& v) const
{
    return Vector3(x-v.x, y-v.y, z-v.z);
}


template <class Float>
inline Vector3<Float> Vector3<Float>::operator*(const Vector3<Float>& V) const
{
    return Vector3(x*V.x, y*V.y, z*V.z);
}


template <class Float>
inline Vector3<Float> Vector3<Float>::operator/(const Vector3<Float>& v) const
{
    return Vector3(x/v.x, y/v.y, z/v.z);
}




//-------------------------------------------------------------------------//
template <class Float>
inline Float Vector3<Float>::operator^ (const Vector3<Float>& v) const
{
   return (x*v.x + y*v.y + z*v.z);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float> Vector3<Float>::operator% (const Vector3<Float>& v) const
{
   return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float> Vector3<Float>::operator* (Float a) const
{
   return Vector3(a*x, a*y, a*z);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float> Vector3<Float>::operator/ (Float a) const
{
   return Vector3(x/a, y/a, z/a);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float> Vector3<Float>::operator- () const
{
   return Vector3<Float>(-x,-y,-z);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float> operator* (Float a, const Vector3<Float>& v)
{
   return Vector3<Float>(a*v.x, a*v.y, a*v.z);
}


//-------------------------------------------------------------------------//
template <class Float>
inline std::ostream& operator<< (std::ostream& s, const Vector3<Float>& v)
{
   return s << '(' << v.x << ", " << v.y << ", "  << v.z << ')';
}

//-------------------------------------------------------------------------//
template <class Float>
inline Float Vector3<Float>::norm() const
{
   return fSqrt(x*x + y*y + z*z);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Float Vector3<Float>::norm2() const
{
   return (x*x + y*y + z*z);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Float Vector3<Float>::dot(const Vector3<Float>& v) const
{
   return (x*v.x + y*v.y + z*v.z);
}


//-------------------------------------------------------------------------//
template <class Float>
inline Float dot(const Vector3<Float>& v, const Vector3<Float>& u)
{
   return (v.x*u.x + v.y*u.y + v.z*u.z);
}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector3<Float>::neg()
{
   x = -x;
   y = -y;
   z = -z;
}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector3<Float>::normalize()
{
   Float n=(Float)fSqrt(x*x + y*y + z*z);

   x /= n;
   y /= n;
   z /= n;
}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector3<Float>::add(const Vector3<Float>& v, const Vector3<Float>& u)
{
   x = v.x + u.x;
   y = v.y + u.y;
   z = v.z + u.z;
}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector3<Float>::sub(const Vector3& v, const Vector3& u)
{
   x = v.x - u.x;
   y = v.y - u.y;
   z = v.z - u.z;
}


//-------------------------------------------------------------------------//
template <class Float>
inline void Vector3<Float>::cross(const Vector3<Float>& u, const Vector3<Float>& v)
{
   x = u.y*v.z - u.z*v.y;
   y = u.z*v.x - u.x*v.z;
   z = u.x*v.y - u.y*v.x;
}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float> fLerp(Vector3<Float> a, Vector3<Float> b, float t)
{
    return a + (b-a)*t;
}
