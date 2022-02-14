/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <iostream>


/** This class implements the basic two dimensional vector with most
  * common operations.
  */
template <class Float>
class Vector2
{
   public:
      //  Vector components  ////////////////////////////////////////////////
      Float x; //!< x component
      Float y; //!< y component
      //-------------------------------------------------------------------//


      //  Constructors   ////////////////////////////////////////////////////
      Vector2();                       //!< Default empty constructor
      Vector2(Float, Float);    //!< Two components constructor
      Vector2(Float[2]);               //!< Array of components constructor
      Vector2(const Vector2&);         //!< Copy constructor
      //-------------------------------------------------------------------//

      //  Operators  ////////////////////////////////////////////////////////
      // comparison
      bool operator== (const Vector2&) const;  //!< Equal operator
      bool operator!= (const Vector2&) const;  //!< Not equal operator

      // arithmetic updates
      Vector2& operator+= (const Vector2&);  //!< Increment operator
      Vector2& operator-= (const Vector2&);  //!< Decrement operator
      Vector2& operator*= (Float);           //!< Multiply operator
      Vector2& operator/= (Float);           //!< Divide operator

      // arithmetic operations
      Vector2 operator+ (const Vector2&) const;   //!< Plus operator
      Vector2 operator- (const Vector2&) const;   //!< Minus operator
      Float operator^ (const Vector2&) const;     //!< dot operator
      Vector2 operator* (Float) const;            //!< Mult operator
      Vector2 operator/ (Float) const;            //!< Division operator
      Vector2 operator- () const;                 //!< Negation operator
      //friend Vector2 operator* (Float, const  Vector2&);   //!< Equal operator

      // access vector V as V[0] = V.x, V[1] = V.y, V[2] = V.z
      //
      // WARNING.  These member functions rely on
      // (1) Vector2 not having virtual functions
      // (2) the data packed in a 2*sizeof(Float) memory block
      Float& operator[] (int) const;
      operator Float* ();

      // std output operator
      //friend std::ostream& operator<< (std::ostream&, const Vector2&);
      //-------------------------------------------------------------------//


      //   Functions  ///////////////////////////////////////////////////////
      void set(Float, Float);
      Float norm() const;
      Float norm2() const;
      Float dot(const Vector2&) const;
      void neg();
      void normalize();
      void add(const Vector2&, const Vector2&);
      void sub(const Vector2&, const Vector2&);
      //-------------------------------------------------------------------//


      //   Static Members  //////////////////////////////////////////////////
      static const Vector2 ZERO;
      static const Vector2 UNIT_X;
      static const Vector2 UNIT_Y;
      //-------------------------------------------------------------------//

}; //class Vector2


#include "Vector2.inl"


typedef Vector2<float> float2;
typedef Vector2<double> double2;


#define FLOAT2_ZERO    float2::ms_vZero
#define FLOAT2_UNITX   float2::ms_vUnitX
#define FLOAT2_UNITY   float2::ms_vUnitY

#define DOUBLE2_ZERO    double2::ms_vZero
#define DOUBLE2_UNITX   double2::ms_vUnitX
#define DOUBLE2_UNITY   double2::ms_vUnitY


#endif // #ifndef VECTOR2_H
