/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

//#include "maths.h"


/** This class implements the basic three dimensional vector with most
  * common operations.
  */
template <class Float>
class Vector3
{
   public:
      //  Vector components  ////////////////////////////////////////////////
      Float x; //!< x component
      Float y; //!< y component
      Float z; //!< z component
      //-------------------------------------------------------------------//


      //  Constructors   ////////////////////////////////////////////////////
      Vector3();                       //!< Default empty constructor
      Vector3(Float, Float, Float);    //!< Three components constructor
      Vector3(Float[3]);               //!< Array of components constructor
      Vector3(const Vector3&);         //!< Copy constructor
      //-------------------------------------------------------------------//

      //  Operators  ////////////////////////////////////////////////////////
      // comparison
      bool operator== (const Vector3&) const;  //!< Equal operator
      bool operator!= (const Vector3&) const;  //!< Not equal operator

      // arithmetic updates
      Vector3& operator+= (const Vector3&);
      Vector3& operator-= (const Vector3&);
      Vector3& operator*= (const Vector3&);
      Vector3& operator/= (const Vector3&);
      Vector3& operator*= (Float);
      Vector3& operator/= (Float);

      // arithmetic operations
      Vector3 operator+ (const Vector3&) const;   //!< Plus operator
      Vector3 operator- (const Vector3&) const;   //!< Minus operator
      Vector3 operator* (const Vector3&) const;   //!< mult operator
      Vector3 operator/ (const Vector3&) const;   //!< div operator
      Vector3 operator* (Float) const;            //!< mult by constant operator
      Vector3 operator/ (Float) const;            //!< divide by constant operator
      Float operator^ (const Vector3&) const;     //!< dot operator
      Vector3 operator% (const Vector3&) const;   //!< cross operator
      Vector3 operator- () const;                 //!< negation operator
      //friend Vector3 operator* (Float, const  Vector3&);   //!< Equal operator

      // access vector V as V[0] = V.x, V[1] = V.y, V[2] = V.z
      //
      // WARNING.  These member functions rely on
      // (1) Vector3 not having virtual functions
      // (2) the data packed in a 3*sizeof(Float) memory block
      Float& operator[] (int) const;
      operator Float* ();

      // std output operator
      //friend std::ostream& operator<< (std::ostream&, const Vector3&);
      //-------------------------------------------------------------------//


      //   Functions  ///////////////////////////////////////////////////////
      void set(Float, Float, Float);
      Float norm() const;
      Float norm2() const;
      Float dot(const Vector3&) const;
      void neg();
      void normalize();
      void add(const Vector3&, const Vector3&);
      void sub(const Vector3&, const Vector3&);
      void cross(const Vector3&, const Vector3&);
      //-------------------------------------------------------------------//


      //   Static Members  //////////////////////////////////////////////////
      static const Vector3 ZERO;
      static const Vector3 UNIT_X;
      static const Vector3 UNIT_Y;
      static const Vector3 UNIT_Z;
      //-------------------------------------------------------------------//

}; //class Vector3


#include "Vector3.inl"


typedef Vector3<float> float3;
typedef Vector3<double> double3;


#define FLOAT3_ZERO    float3::ms_vZero
#define FLOAT3_UNITX   float3::ms_vUnitX
#define FLOAT3_UNITY   float3::ms_vUnitY
#define FLOAT3_UNITZ   float3::ms_vUnitZ

#define DOUBLE3_ZERO    double3::ms_vZero
#define DOUBLE3_UNITX   double3::ms_vUnitX
#define DOUBLE3_UNITY   double3::ms_vUnitY
#define DOUBLE3_UNITZ   double3::ms_vUnitZ


#endif // #ifndef VECTOR3_H
