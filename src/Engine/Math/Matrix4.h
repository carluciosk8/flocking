/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef MATRIX4_H
#define MATRIX4_H


#include <iostream>

#include "Vector4.h"


/**
  *This class implements a 4x4 matrix, used to represent homogeneous transforms.
  */
template <class Float>
class Matrix4
{
   public:
      ///  Matrix components  ///////////////////////////////////////////////
      Float m[4][4];
      //-------------------------------------------------------------------//


      ///  Constructors  ////////////////////////////////////////////////////
      Matrix4();      // Default empty constructor
      
      Matrix4(const Vector4<Float>&, const Vector4<Float>&, const Vector4<Float>&, const Vector4<Float>&);  // 4 vec. constructor
      
      Matrix4( Float, Float, Float, Float,
               Float, Float, Float, Float,
               Float, Float, Float, Float,
               Float, Float, Float, Float );      // sixteen components constructor
      
      Matrix4(Float*);      // Array of components constructor
      
      Matrix4(const Matrix4&);      // Copy constructor
      ///-----------------------------------------------------------------///


      ///  Operators  ///////////////////////////////////////////////////////
      // comparison
      bool operator== (const Matrix4&) const;
      bool operator!= (const Matrix4&) const;

      // arithmetic updates
      Matrix4& operator+= (const Matrix4&);
      Matrix4& operator-= (const Matrix4&);
      Matrix4& operator*= (Float);
      Matrix4& operator*= (const Matrix4&);
      Matrix4& operator^= (const Matrix4&);

      // arithmetic operations
      Matrix4 operator+ (const Matrix4&) const;
      Matrix4 operator- (const Matrix4&) const;
      Matrix4 operator* (const Matrix4&) const;
      Matrix4 operator* (Float) const;
      Vector4<Float> operator* (const Vector4<Float>&) const;
      Matrix4 operator- () const;
      //friend Matrix4<Float> operator* (Float, const Matrix4&);

      // std output operator
      //friend std::ostream& operator<<  (std::ostream&, const Matrix4&);
      ///-----------------------------------------------------------------///


      ///  Functions  ///////////////////////////////////////////////////////
      void set(Float, Float, Float, Float,
               Float, Float, Float, Float,
               Float, Float, Float, Float,
               Float, Float, Float, Float);
      Float det() const;
      void neg();
      void add(const Matrix4&);
      void add(const Matrix4&, const Matrix4&);
      void sub(const Matrix4&);
      void sub(const Matrix4&, const Matrix4&);
      void mul(const Matrix4&);
      void mul(const Matrix4&, const Matrix4&);
      ///-----------------------------------------------------------------///


      //void eulerTransform(Float, Float, Float);

      ///  Static Members  //////////////////////////////////////////////////
      static const Matrix4 IDENTITY;
      ///-----------------------------------------------------------------///
};

#include "Matrix4.inl"


typedef Matrix4<float> float4x4;
typedef Matrix4<double> double4x4;


#define FLOAT4X4_IDENTITY  float4x4::IDENTITY
#define DOUBLE4X4_IDENTITY  double4x4::IDENTITY


#endif
