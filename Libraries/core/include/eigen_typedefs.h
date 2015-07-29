#ifndef EIGEN_TYPEDEFS_H
#define EIGEN_TYPEDEFS_H

#ifdef USE_EIGEN

/* Eigen includes. ************************************************************/
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SVD>

/******************************************************************************/
/* Shorcuts for Eigen data structures. */
#define _MatrixNxM(template_type, n, m)         Eigen::Matrix<template_type, n, m>
#define _Matrix2x2(template_type)               _MatrixNxM(template_type, 2, 2)
#define _Matrix2x3(template_type)               _MatrixNxM(template_type, 2, 3)
#define _Matrix2x4(template_type)               _MatrixNxM(template_type, 2, 4)
#define _Matrix2xX(template_type)               _MatrixNxM(template_type, 2, Eigen::Dynamic)
#define _MatrixXx2(template_type)               _MatrixNxM(template_type, Eigen::Dynamic, 2)
#define _Matrix3x2(template_type)               _MatrixNxM(template_type, 3, 2)
#define _Matrix3x3(template_type)               _MatrixNxM(template_type, 3, 3)
#define _Matrix3x4(template_type)               _MatrixNxM(template_type, 3, 4)
#define _Matrix3xX(template_type)               _MatrixNxM(template_type, 3, Eigen::Dynamic)
#define _MatrixXx3(template_type)               _MatrixNxM(template_type, Eigen::Dynamic, 3)
#define _Matrix4x2(template_type)               _MatrixNxM(template_type, 4, 2)
#define _Matrix4x3(template_type)               _MatrixNxM(template_type, 4, 3)
#define _Matrix4x4(template_type)               _MatrixNxM(template_type, 4, 4)
#define _Matrix4xX(template_type)               _MatrixNxM(template_type, 4, Eigen::Dynamic)
#define _MatrixXx4(template_type)               _MatrixNxM(template_type, Eigen::Dynamic, 4)
#define _MatrixX(template_type)                 _MatrixNxM(template_type, Eigen::Dynamic, Eigen::Dynamic)

#define _SparseMatrix(template_type)            Eigen::SparseMatrix<template_type>

#define _SparseVector(template_type)            Eigen::SparseVector<template_type>

#define _TransformN(template_type, dim, type)   Eigen::Transform<template_type, dim, type>
#define _AffineN(template_type, n)              _TransformN(template_type, n, Eigen::Affine)
#define _Affine2(template_type)                 _AffineN(template_type, 2)
#define _Affine3(template_type)                 _AffineN(template_type, 3)
#define _Affine4(template_type)                 _AffineN(template_type, 4)

#define _Triplet(template_type)                 Eigen::Triplet<template_type>

#define _VectorN(template_type, n)              Eigen::Matrix<template_type, n, 1>
#define _Vector2(template_type)                 _VectorN(template_type, 2)
#define _Vector3(template_type)                 _VectorN(template_type, 3)
#define _Vector4(template_type)                 _VectorN(template_type, 4)
#define _VectorX(template_type)                 _VectorN(template_type, Eigen::Dynamic)

#define _AngleAxis(template_type)               Eigen::AngleAxis<template_type>

#define _Quaternion(template_type)              Eigen::Quaternion<template_type>

/******************************************************************************/
/* Typedefs. */
typedef _Affine2(double)                            _Affine2d;
typedef _Affine3(double)                            _Affine3d;
typedef _Affine4(double)                            _Affine4d;
typedef _AngleAxis(double)                          _AngleAxisd;
typedef _Matrix2x2(double)                          _Matrix2x2d;
typedef _Matrix2x3(double)                          _Matrix2x3d;
typedef _Matrix2x4(double)                          _Matrix2x4d;
typedef _Matrix2xX(double)                          _Matrix2xXd;
typedef _MatrixXx2(double)                          _MatrixXx2d;
typedef _Matrix3x2(double)                          _Matrix3x2d;
typedef _Matrix3x3(double)                          _Matrix3x3d;
typedef _Matrix3x4(double)                          _Matrix3x4d;
typedef _Matrix3xX(double)                          _Matrix3xXd;
typedef _Matrix3xX(unsigned char)                   _Matrix3xXuc;
typedef _MatrixXx3(double)                          _MatrixXx3d;
typedef _Matrix4x2(double)                          _Matrix4x2d;
typedef _Matrix4x3(double)                          _Matrix4x3d;
typedef _Matrix4x4(double)                          _Matrix4x4d;
typedef _Matrix4xX(double)                          _Matrix4xXd;
typedef _MatrixXx4(double)                          _MatrixXx4d;
typedef _MatrixX(double)                            _MatrixXd;
typedef _Vector2(double)                            _Vector2d;
typedef _Vector3(double)                            _Vector3d;
typedef _Vector4(double)                            _Vector4d;
typedef _VectorX(double)                            _VectorXd;
typedef _VectorX(int)                               _VectorXi;
typedef _SparseMatrix(double)                       _SparseMatrixd;
typedef _SparseMatrix(int)                          _SparseMatrixi;
typedef _SparseVector(double)                       _SparseVectord;
typedef _SparseVector(int)                          _SparseVectori;
typedef _Triplet(double)                            _Tripletd;
typedef _Quaternion(double)                         _Quaterniond;

#endif // USE_EIGEN

#endif // EIGEN_TYPEDEFS_H
