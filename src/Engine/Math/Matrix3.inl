/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
template <class Float>
inline Matrix3<Float>::Matrix3()
{}



template <class Float>
inline Matrix3<Float>::Matrix3(const Vector3<Float>& v1, const Vector3<Float>& v2, const Vector3<Float>& v3)
{
   m[0][0]=v1.x; m[0][1]=v2.x; m[0][2]=v3.x;
   m[1][0]=v1.y; m[1][1]=v2.y; m[1][2]=v3.y;
   m[2][0]=v1.z; m[2][1]=v2.z; m[2][2]=v3.z;
}



//-------------------------------------------------------------------------//
// nine components constructor
template <class Float>
inline Matrix3<Float>::Matrix3(Float a, Float b, Float c,
                               Float d, Float e, Float f,
                               Float g, Float h, Float i)
{
   m[0][0]=a; m[0][1]=b; m[0][2]=c;
   m[1][0]=d; m[1][1]=e; m[1][2]=f;
   m[2][0]=g; m[2][1]=h; m[2][2]=i;
}



//-------------------------------------------------------------------------//
// Array of components constructor
template <class Float>
inline Matrix3<Float>::Matrix3(Float* a)
{
   memcpy(this, a, 9*sizeof(Float));
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float>::Matrix3(const Matrix3<Float>& a)
{
   m[0][0]=(a.m[0][0]); m[0][1]=(a.m[0][1]); m[0][2]=(a.m[0][2]);
   m[1][0]=(a.m[1][0]); m[1][1]=(a.m[1][1]); m[1][2]=(a.m[1][2]);
   m[2][0]=(a.m[2][0]); m[2][1]=(a.m[2][1]); m[2][2]=(a.m[2][2]);
}



//-------------------------------------------------------------------------//
// comparison
template <class Float>
inline bool Matrix3<Float>::operator== (const Matrix3<Float>& a) const
{
   return (m[0][0]==a.m[0][0] && m[0][1]==a.m[0][1] && m[0][2]==a.m[0][2] &&
           m[1][0]==a.m[1][0] && m[1][1]==a.m[1][1] && m[1][2]==a.m[1][2] &&
           m[2][0]==a.m[2][0] && m[2][1]==a.m[2][1] && m[2][2]==a.m[2][2]);
}



//-------------------------------------------------------------------------//
template <class Float>
inline bool Matrix3<Float>::operator!= (const Matrix3<Float>& a) const
{
   return (m[0][0]!=a.m[0][0] || m[0][1]!=a.m[0][1] || m[0][2]!=a.m[0][2] ||
           m[1][0]!=a.m[1][0] || m[1][1]!=a.m[1][1] || m[1][2]!=a.m[1][2] ||
           m[2][0]!=a.m[2][0] || m[2][1]!=a.m[2][1] || m[2][2]!=a.m[2][2]);
}



//-------------------------------------------------------------------------//
// arithmetic updates
template <class Float>
inline Matrix3<Float>& Matrix3<Float>::operator+= (const Matrix3<Float>& a)
{
   m[0][0]+=a.m[0][0] ; m[0][1]+=a.m[0][1] ; m[0][2]+=a.m[0][2] ;
   m[1][0]+=a.m[1][0] ; m[1][1]+=a.m[1][1] ; m[1][2]+=a.m[1][2] ;
   m[2][0]+=a.m[2][0] ; m[2][1]+=a.m[2][1] ; m[2][2]+=a.m[2][2] ;
   return *this;
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float>& Matrix3<Float>::operator-= (const Matrix3<Float>& a)
{
   m[0][0]-=a.m[0][0] ; m[0][1]-=a.m[0][1] ; m[0][2]-=a.m[0][2] ;
   m[1][0]-=a.m[1][0] ; m[1][1]-=a.m[1][1] ; m[1][2]-=a.m[1][2] ;
   m[2][0]-=a.m[2][0] ; m[2][1]-=a.m[2][1] ; m[2][2]-=a.m[2][2] ;
   return *this;
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float>& Matrix3<Float>::operator*= (const Matrix3<Float>& a)
{
   Matrix3 tmp(m[0][0]*a.m[0][0] + m[0][1]*a.m[1][0] + m[0][2]*a.m[2][0],
               m[0][0]*a.m[0][1] + m[0][1]*a.m[1][1] + m[0][2]*a.m[2][1],
               m[0][0]*a.m[0][2] + m[0][1]*a.m[1][2] + m[0][2]*a.m[2][2],

               m[1][0]*a.m[0][0] + m[1][1]*a.m[1][0] + m[1][2]*a.m[2][0],
               m[1][0]*a.m[0][1] + m[1][1]*a.m[1][1] + m[1][2]*a.m[2][1],
               m[1][0]*a.m[0][2] + m[1][1]*a.m[1][2] + m[1][2]*a.m[2][2],

               m[2][0]*a.m[0][0] + m[2][1]*a.m[1][0] + m[2][2]*a.m[2][0],
               m[2][0]*a.m[0][1] + m[2][1]*a.m[1][1] + m[2][2]*a.m[2][1],
               m[2][0]*a.m[0][2] + m[2][1]*a.m[1][2] + m[2][2]*a.m[2][2]);

   return ((*this)=tmp);
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float>& Matrix3<Float>::operator^= (const Matrix3<Float>& a)
{
   m[0][0]*=a.m[0][0] ; m[0][1]*=a.m[0][1] ; m[0][2]*=a.m[0][2] ;
   m[1][0]*=a.m[1][0] ; m[1][1]*=a.m[1][1] ; m[1][2]*=a.m[1][2] ;
   m[2][0]*=a.m[2][0] ; m[2][1]*=a.m[2][1] ; m[2][2]*=a.m[2][2] ;

   return *this;
}



//-------------------------------------------------------------------------//
// arithmetic operations
template <class Float>
inline Matrix3<Float> Matrix3<Float>::operator+ (const Matrix3<Float>& a) const
{
   return Matrix3<Float>(m[0][0]+a.m[0][0] , m[0][1]+a.m[0][1] , m[0][2]+a.m[0][2],
                         m[1][0]+a.m[1][0] , m[1][1]+a.m[1][1] , m[1][2]+a.m[1][2],
                         m[2][0]+a.m[2][0] , m[2][1]+a.m[2][1] , m[2][2]+a.m[2][2]);
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float> Matrix3<Float>::operator- (const Matrix3<Float>& a) const
{
   return Matrix3<Float>(m[0][0]-a.m[0][0] , m[0][1]-a.m[0][1] , m[0][2]-a.m[0][2],
                         m[1][0]-a.m[1][0] , m[1][1]-a.m[1][1] , m[1][2]-a.m[1][2],
                         m[2][0]-a.m[2][0] , m[2][1]-a.m[2][1] , m[2][2]-a.m[2][2]);
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float> Matrix3<Float>::operator* (const Matrix3<Float>& a) const
{
   return Matrix3(m[0][0]*a.m[0][0] + m[0][1]*a.m[1][0] + m[0][2]*a.m[2][0],
                  m[0][0]*a.m[0][1] + m[0][1]*a.m[1][1] + m[0][2]*a.m[2][1],
                  m[0][0]*a.m[0][2] + m[0][1]*a.m[1][2] + m[0][2]*a.m[2][2],

                  m[1][0]*a.m[0][0] + m[1][1]*a.m[1][0] + m[1][2]*a.m[2][0],
                  m[1][0]*a.m[0][1] + m[1][1]*a.m[1][1] + m[1][2]*a.m[2][1],
                  m[1][0]*a.m[0][2] + m[1][1]*a.m[1][2] + m[1][2]*a.m[2][2],

                  m[2][0]*a.m[0][0] + m[2][1]*a.m[1][0] + m[2][2]*a.m[2][0],
                  m[2][0]*a.m[0][1] + m[2][1]*a.m[1][1] + m[2][2]*a.m[2][1],
                  m[2][0]*a.m[0][2] + m[2][1]*a.m[1][2] + m[2][2]*a.m[2][2]);
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float> Matrix3<Float>::operator* (Float a) const
{
   return Matrix3<Float>(m[0][0]*a, m[0][1]*a, m[0][2]*a,
                         m[1][0]*a, m[1][1]*a, m[1][2]*a,
                         m[2][0]*a, m[2][1]*a, m[2][2]*a);
}



//-------------------------------------------------------------------------//
template <class Float>
inline Vector3<Float> Matrix3<Float>::operator* (const Vector3<Float>& v) const
{
   return Vector3<Float>(m[0][0]*v[0] + m[0][1]*v[1] + m[0][2]*v[2],
                         m[1][0]*v[0] + m[1][1]*v[1] + m[1][2]*v[2],
                         m[2][0]*v[0] + m[2][1]*v[1] + m[2][2]*v[2]);
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float> Matrix3<Float>::operator- () const
{
   return Matrix3<Float>(-m[0][0], -m[0][1], -m[0][2],
                         -m[1][0], -m[1][1], -m[1][2],
                         -m[2][0], -m[2][1], -m[2][2]);
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float> operator* (Float a, const Matrix3<Float>& m)
{
   return Matrix3<Float>(m.m[0][0]*a, m.m[0][1]*a, m.m[0][2]*a,
                         m.m[1][0]*a, m.m[1][1]*a, m.m[1][2]*a,
                         m.m[2][0]*a, m.m[2][1]*a, m.m[2][2]*a);
}



//-------------------------------------------------------------------------//
// std output operator
template <class Float>
inline std::ostream& operator<< (std::ostream& s, const Matrix3<Float>& m)
{
   return s
   << '[' << m.m[0][0] << " , " << m.m[0][1] << " , "  << m.m[0][2] << "]\n"
   << '[' << m.m[1][0] << " , " << m.m[1][1] << " , "  << m.m[1][2] << "]\n"
   << '[' << m.m[2][0] << " , " << m.m[2][1] << " , "  << m.m[2][2] << "]\n";
}



//-------------------------------------------------------------------------//
template <class Float>
inline void Matrix3<Float>::set(Float a, Float b, Float c,
                                Float d, Float e, Float f,
                                Float g, Float h, Float i)
{
   m[0][0]=a; m[0][1]=b; m[0][2]=c;
   m[1][0]=d; m[1][1]=e; m[1][2]=f;
   m[2][0]=g; m[2][1]=h; m[2][2]=i;
}



//-------------------------------------------------------------------------//
template <class Float>
inline Float Matrix3<Float>::det() const
{
   return ( m[0][0]*m[1][1]*m[2][2] +
            m[1][0]*m[2][1]*m[0][2] +
            m[0][1]*m[1][2]*m[2][0] )
          -
          ( m[0][2]*m[1][1]*m[2][0] +
            m[1][2]*m[2][1]*m[0][0] +
            m[2][2]*m[1][0]*m[0][1] );
}



//-------------------------------------------------------------------------//
template <class Float>
inline void Matrix3<Float>::neg()
{
   m[0][0] = -m[0][0] ; m[0][1] = -m[0][1] ; m[0][2] = -m[0][2];
   m[1][0] = -m[1][0] ; m[1][1] = -m[1][1] ; m[1][2] = -m[1][2];
   m[2][0] = -m[2][0] ; m[2][1] = -m[2][1] ; m[2][2] = -m[2][2];
}



//-------------------------------------------------------------------------//
template <class Float>
inline void Matrix3<Float>::add(const Matrix3<Float>& a, const Matrix3<Float>& b)
{
   m[0][0]=a.m[0][0]+b.m[0][0]; m[0][1]=a.m[0][1]+b.m[0][1]; m[0][2]=a.m[0][2]+b.m[0][2];
   m[1][0]=a.m[1][0]+b.m[1][0]; m[1][1]=a.m[1][1]+b.m[1][1]; m[1][2]=a.m[1][2]+b.m[1][2];
   m[2][0]=a.m[2][0]+b.m[2][0]; m[2][1]=a.m[2][1]+b.m[2][1]; m[2][2]=a.m[2][2]+b.m[2][2];
}



//-------------------------------------------------------------------------//
template <class Float>
inline void Matrix3<Float>::sub(const Matrix3<Float>& a, const Matrix3<Float>& b)
{
   m[0][0]=a.m[0][0]-b.m[0][0]; m[0][1]=a.m[0][1]-b.m[0][1]; m[0][2]=a.m[0][2]-b.m[0][2];
   m[1][0]=a.m[1][0]-b.m[1][0]; m[1][1]=a.m[1][1]-b.m[1][1]; m[1][2]=a.m[1][2]-b.m[1][2];
   m[2][0]=a.m[2][0]-b.m[2][0]; m[2][1]=a.m[2][1]-b.m[2][1]; m[2][2]=a.m[2][2]-b.m[2][2];
}



//-------------------------------------------------------------------------//
template <class Float>
inline void Matrix3<Float>::mul(const Matrix3<Float>& a, const Matrix3<Float>& b)
{
   m[0][0] = a.m[0][0]*b.m[0][0] + a.m[0][1]*b.m[1][0] + a.m[0][2]*b.m[2][0];
   m[0][1] = a.m[0][0]*b.m[0][1] + a.m[0][1]*b.m[1][1] + a.m[0][2]*b.m[2][1];
   m[0][2] = a.m[0][0]*b.m[0][2] + a.m[0][1]*b.m[1][2] + a.m[0][2]*b.m[2][2];

   m[1][0] = a.m[1][0]*b.m[0][0] + a.m[1][1]*b.m[1][0] + a.m[1][2]*b.m[2][0];
   m[1][1] = a.m[1][0]*b.m[0][1] + a.m[1][1]*b.m[1][1] + a.m[1][2]*b.m[2][1];
   m[1][2] = a.m[1][0]*b.m[0][2] + a.m[1][1]*b.m[1][2] + a.m[1][2]*b.m[2][2];

   m[2][0] = a.m[2][0]*b.m[0][0] + a.m[2][1]*b.m[1][0] + a.m[2][2]*b.m[2][0];
   m[2][1] = a.m[2][0]*b.m[0][1] + a.m[2][1]*b.m[1][1] + a.m[2][2]*b.m[2][1];
   m[2][2] = a.m[2][0]*b.m[0][2] + a.m[2][1]*b.m[1][2] + a.m[2][2]*b.m[2][2];
}



template <class Float>
inline void Matrix3<Float>::reortho()
{
//TODO//
}



//-------------------------------------------------------------------------//
template <class Float>
inline Matrix3<Float> Matrix3<Float>::trans()
{
   return Matrix3<Float>( m[0][0] , m[1][0] , m[2][0] ,
                          m[0][1] , m[1][1] , m[2][1] ,
                          m[0][2] , m[1][2] , m[2][2] );
}



//-------------------------------------------------------------------------//
template <class Float>
inline void Matrix3<Float>::inv()
{
//TODO//
}


      
/*
//-------------------------------------------------------------------------//
template <class Float>
inline void Matrix3::eulerTransform(Float h, Float p, Float r)
{
   //
   //          | cos(r)cos(h)-sin(r)sin(p)sin(h)  -sin(r)cos(p)  cos(r)sin(h)+sin(r)sin(p)cos(h) |
   // E(h,p,r)=| sin(r)cos(h)+cos(r)sin(p)sin(h)   cos(r)cos(p)  sin(r)sin(h)-cos(r)sin(p)cos(h) |
   //          |-cos(p)sin(h),                     sin(p),       cos(p)cos(h)                    |
   //

   m[0][0]=cos(r)*cos(h) - sin(r)*sin(p)*sin(h);
   m[0][1]=-sin(r)*cos(p);
   m[0][2]=cos(r)*sin(h) + sin(r)*sin(p)*cos(h);

   m[1][0]=sin(r)*cos(h) + cos(r)*sin(p)*sin(h);
   m[1][1]=cos(r)*cos(p);
   m[1][2]=sin(r)*sin(h) - cos(r)*sin(p)*cos(h);

   m[2][0]=-cos(p)*sin(h);
   m[2][1]=sin(p);
   m[2][2]=cos(p)*cos(h);
}//--------------------------------------------------------------------------//
*/
