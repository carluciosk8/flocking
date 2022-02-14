/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
//-------------------------------------------------------------------------//
template <class Float>
inline Vector4<Float>::Vector4()
{}


//-------------------------------------------------------------------------//
template <class Float>
inline Vector4<Float>::Vector4(Float vx, Float vy, Float vz, Float vw)
:
   x(vx),
   y(vy),
   z(vz),
   w(vw)
{}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float>::Vector4(Float v[4])
:
   x(v[0]),
   y(v[1]),
   z(v[2]),
   w(v[3])
{}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float>::Vector4(const Vector4<Float>& v)
:
   x(v.x),
   y(v.y),
   z(v.z),
   w(v.w)
{}


//-------------------------------------------------------------------------//

template <class Float>
inline void Vector4<Float>::set(Float vx, Float vy, Float vz, Float vw)
{
   x=vx;
   y=vy;
   z=vz;
   w=vw;
}


//-------------------------------------------------------------------------//

template <class Float>
inline Float& Vector4<Float>::operator[] (int i) const
{
   return ((Float*)this)[i];
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float>::operator Float* ()
{
   return (Float*)this;
}


//-------------------------------------------------------------------------//

template <class Float>
inline bool Vector4<Float>::operator== (const Vector4<Float>& v) const
{
   return (x==v.x && y==v.y && z==v.z && w==v.w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline bool Vector4<Float>::operator!= (const Vector4<Float>& v) const
{
   return (x!=v.x || y!=v.y || z!=v.z || w!=v.w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float>& Vector4<Float>::operator+= (const Vector4<Float>& v)
{
   x+=v.x;
   y+=v.y;
   z+=v.z;
   w+=v.w;
   return *this;
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float>& Vector4<Float>::operator-= (const Vector4<Float>& v)
{
   x-=v.x;
   y-=v.y;
   z-=v.z;
   w-=v.w;
   return *this;
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float>& Vector4<Float>::operator*= (Float a)
{
    x*=a;
    y*=a;
    z*=a;
    w*=a;
    return *this;
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float>& Vector4<Float>::operator/= (Float a)
{
   x/=a;
   y/=a;
   z/=a;
   w/=a;
   return *this;
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float> Vector4<Float>::operator+ (const Vector4<Float>& v) const
{
   return Vector4<Float>(x+v.x, y+v.y, z+v.z, w+v.w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float> Vector4<Float>::operator- (const Vector4<Float>& v) const
{
   return Vector4<Float>(x-v.x, y-v.y, z-v.z, w-v.w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Float Vector4<Float>::operator* (const Vector4<Float>& v) const
{
   return (x*v.x + y*v.y + z*v.z + w*v.w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float> Vector4<Float>::operator* (Float a) const
{
   return Vector4<Float>(a*x, a*y, a*z, a*w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float> Vector4<Float>::operator^ (const Vector4<Float>& v) const
{
   return Vector4<Float>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x, 1.0);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float> Vector4<Float>::operator/ (Float a) const
{
   return Vector4<Float>(x/a, y/a, z/a, w/a);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float> Vector4<Float>::operator- () const
{
   return Vector4<Float>(-x, -y, -z, -w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Vector4<Float> operator* (Float a, const Vector4<Float>& v)
{
   return Vector4<Float>(a*v.x, a*v.y, a*v.z, a*v.w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline std::ostream& operator<< (std::ostream& s, const Vector4<Float>& v)
{
   return s << '(' << v.x << ", " << v.y << ", "  << v.z << ", "  << v.w << ')';
}

//-------------------------------------------------------------------------//

template <class Float>
inline Float Vector4<Float>::norm() const
{
   return fSqrt(x*x + y*y + z*z + w*w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Float Vector4<Float>::norm2() const
{
   return (x*x + y*y + z*z + w*w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Float Vector4<Float>::dot(const Vector4<Float>& v) const
{
   return (x*v.x + y*v.y + z*v.z + w*v.w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline Float dot(const Vector4<Float>& v, const Vector4<Float>& u)
{
   return (v.x*u.x + v.y*u.y + v.z*u.z + v.w*u.w);
}


//-------------------------------------------------------------------------//

template <class Float>
inline void Vector4<Float>::neg()
{
   x = -x;
   y = -y;
   z = -z;
   w = -w;
}


//-------------------------------------------------------------------------//

template <class Float>
inline void Vector4<Float>::normalize()
{
   Float n=fSqrt(x*x + y*y + z*z + w*w);

   x /= n;
   y /= n;
   z /= n;
   w /= n;
}


//-------------------------------------------------------------------------//

template <class Float>
inline void Vector4<Float>::add(const Vector4<Float>& v, const Vector4<Float>& u)
{
   x = v.x + u.x;
   y = v.y + u.y;
   z = v.z + u.z;
   w = v.w + u.w;
}


//-------------------------------------------------------------------------//

template <class Float>
inline void Vector4<Float>::sub(const Vector4<Float>& v, const Vector4<Float>& u)
{
   x = v.x - u.x;
   y = v.y - u.y;
   z = v.z - u.z;
   w = v.w - u.w;
}


//-------------------------------------------------------------------------//

template <class Float>
inline void Vector4<Float>::cross(const Vector4<Float>& u, const Vector4<Float>& v)
{
   x = u.y*v.z - u.z*v.y;
   y = u.z*v.x - u.x*v.z;
   z = u.x*v.y - u.y*v.x;
   w = 1.0;
}
