/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef MATRIX3_H
#define MATRIX3_H


#include <iostream>

#include "Vector3.h"


/**This class implements the basic 3x3 matrix, used to represent rotations.
*@author Carlucio Santos
*/
template <class Float>
class Matrix3
{
    public:
        ///  Matrix components  ///////////////////////////////////////////////
        Float m[3][3];
        //-------------------------------------------------------------------//


        ///  Constructors  ////////////////////////////////////////////////////
        Matrix3();  //

        Matrix3(const Vector3<Float>&, const Vector3<Float>&, const Vector3<Float>&);  //!< 3 vec. constructor

        Matrix3(Float, Float, Float,
                Float, Float, Float,
                Float, Float, Float);   //!< nine components constructor
                                            
        Matrix3(Float* a);              //!< Array of components constructor

        Matrix3(const Matrix3& a);      //!< Copy constructor
        ///-----------------------------------------------------------------///


        ///  Operators  ///////////////////////////////////////////////////////
        // comparison
        bool operator== (const Matrix3&) const;
        bool operator!= (const Matrix3&) const;

        // arithmetic updates
        Matrix3& operator+= (const Matrix3&);
        Matrix3& operator-= (const Matrix3&);
        Matrix3& operator*= (Float);
        Matrix3& operator*= (const Matrix3& a);
        Matrix3& operator^= (const Matrix3& a);

        // arithmetic operations
        Matrix3 operator+ (const Matrix3&) const;
        Matrix3 operator- (const Matrix3&) const;
        Matrix3 operator* (const Matrix3&) const;
        Matrix3 operator* (Float) const;
        Vector3<Float> operator* (const Vector3<Float>&) const;
        Matrix3 operator- () const;
        //friend Matrix3<Float> operator* (Float, const Matrix3&);

        // std output operator
        //friend std::ostream& operator<<  (std::ostream&, const Matrix3&);
        ///-----------------------------------------------------------------///


        ///  Functions  ///////////////////////////////////////////////////////
        void set(Float, Float, Float,
                 Float, Float, Float,
                 Float, Float, Float);
        Float det() const;
        void neg();
        void add(const Matrix3&, const Matrix3&);
        void sub(const Matrix3&, const Matrix3&);
        void mul(const Matrix3&, const Matrix3&);
        void reortho();
        Matrix3 trans();
        void inv();
        ///-----------------------------------------------------------------///



        ///  Static Members  //////////////////////////////////////////////////
        static const Matrix3 IDENTITY;
        ///-----------------------------------------------------------------///
};

#include "Matrix3.inl"


typedef Matrix3<float> float3x3;
typedef Matrix3<double> double3x3;


#define FLOAT3X3_IDENTITY  float3x3::IDENTITY
#define DOUBLE3X3_IDENTITY  double3x3::IDENTITY


#endif
