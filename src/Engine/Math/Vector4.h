/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#include <iostream>
//#include "maths.h"



/** This class implements the basic three dimensional vector with most
  * common operations.
  */
template <class Float>
class Vector4
{
   public:
      //  Vector components  ////////////////////////////////////////////////
      Float x; //!< x component
      Float y; //!< y component
      Float z; //!< z component
      Float w; //!< w component
      //-------------------------------------------------------------------//


      //  Constructors   ////////////////////////////////////////////////////
      Vector4();                     //!< Default empty constructor
      Vector4(Float, Float, Float, Float);  //!< Four components constructor
      Vector4(Float[4]);             //!< Array of components constructor
      Vector4(const Vector4&);          //!< Copy constructor
      //-------------------------------------------------------------------//


      //  Operators  ////////////////////////////////////////////////////////
      // comparison
      bool operator== (const Vector4&) const;  //!< Equal operator
      bool operator!= (const Vector4&) const;  //!< Not equal operator

      // arithmetic updates
      Vector4& operator+= (const Vector4&);  //!< Increment operator
      Vector4& operator-= (const Vector4&);  //!< Decrement operator
      Vector4& operator*= (Float);        //!< Multiply operator
      Vector4& operator/= (Float);        //!< Divide operator

      // arithmetic operations
      Vector4 operator+ (const Vector4&) const;   //!< Plus operator
      Vector4 operator- (const Vector4&) const;   //!< Minus operator
      Float operator* (const Vector4&) const;  //!< Equal operator
      Vector4 operator* (Float) const;         //!< Equal operator
      Vector4 operator^ (const Vector4&) const;   //!< Cross operator
      Vector4 operator/ (Float) const;         //!< Equal operator
      Vector4 operator- () const;              //!< Equal operator
      //friend Vector4<Float> operator*  (Float, const Vector4&);   //!< Equal operator

      // access vector V as V[0] = V.x, V[1] = V.y, V[2] = V.z
      //
      // WARNING.  These member functions rely on
      // (1) Vector4 not having virtual functions
      // (2) the data packed in a 3*sizeof(Float) memory block
      Float& operator[] (int) const;
      operator Float* ();

      // std output operator
      //friend std::ostream& operator<<  (std::ostream&, const Vector4&);
      //-------------------------------------------------------------------//


      //   Functions  ///////////////////////////////////////////////////////
      void set(Float, Float, Float, Float);
      Float norm() const;
      Float norm2() const;
      Float dot(const Vector4&) const;
      void neg();
      void normalize();
      void add(const Vector4&, const Vector4&);
      void sub(const Vector4&, const Vector4&);
      void cross(const Vector4&, const Vector4&);
      //-------------------------------------------------------------------//


      //   Static Members  //////////////////////////////////////////////////
      static const Vector4 ms_vZero;
      static const Vector4 ms_vUnitX;
      static const Vector4 ms_vUnitY;
      static const Vector4 ms_vUnitZ;
      static const Vector4 ms_vUnitW;
      //-------------------------------------------------------------------//

}; // End Class Vector4

#include "Vector4.inl"


typedef Vector4<float> float4;
typedef Vector4<double> double4;



#define FLOAT4_ZERO    float4::ms_vZero
#define FLOAT4_UNITX   float4::ms_vUnitX
#define FLOAT4_UNITY   float4::ms_vUnitY
#define FLOAT4_UNITZ   float4::ms_vUnitZ
#define FLOAT4_UNITW   float4::ms_vUnitW

#define DOUBLE4_ZERO    double4::ms_vZero
#define DOUBLE4_UNITX   double4::ms_vUnitX
#define DOUBLE4_UNITY   double4::ms_vUnitY
#define DOUBLE4_UNITZ   double4::ms_vUnitZ
#define DOUBLE4_UNITW   double4::ms_vUnitW


#endif // #ifndef FLICK_VECTOR4_H
