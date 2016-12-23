#pragma once

#include "Vector3.h"
#include <array>
#include "RotationAngles.h"

/**
	A typedef of a 3x3 matrix, to be used to perform the matrix multiplication for rotation.
*/
using matrix3x3_t = std::array<std::array<int, 3>, 3>;

class Rotation
{
public:
	Rotation();
	/**
		Class constructor that takes in a colour corresponding to a cube face and a rotation angle indicating which way and how much 
		the rotation should operate.
		@param colourAxis The face axis that this rotation will operate about, represented in the form of the face's colour.
		@param rotationAngle The amount of rotation that will be performed by the class.
	*/
	Rotation(Colour colourAxis, RotationAngles rotationAngle);

	/**
		Class constructor that takes in a vector corresponding to a cube face and a rotation angle indicating which way and how much
		the rotation should operate.
		@param vectorAxis The face axis that this rotation will operate about, represented in the form of the face's vector axis.
		@param rotationAngle The amount of rotation that will be performed by the class.
	*/
	Rotation(Vector3 vectorAxis, RotationAngles rotationAngle);

	/**
		Gets the vector axis of the rotation.
		@return Vector The vector axis of the rotation.
	*/
	Vector3 GetVectorAxis();

	/**
		Multiplies the passed vector by the rotationMatrix and reassigns the vector to become the rotated vector.
		@param &vectorToRotate A reference to the vector that is desired to be rotated.
	*/
	void Rotate(Vector3 &vectorToRotate);

private:
	/**
		Member variable to represent the rotation's vector axis.
	*/
	Vector3 vectorAxis{ 0, 0, 0 };

	/**
		Member variable to store the rotation amount and direction.
	*/
	RotationAngles rotationAngle;

	/**
		Member variable to hold the Rx rotation matrix.
	*/
	matrix3x3_t Rx{};

	/**
		Member variable to hold the Ry rotation matrix.
	*/
	matrix3x3_t Ry{};

	/**
		Member variable to hold the Rz rotation matrix.
	*/
	matrix3x3_t Rz{};

	/**
		Member variable to hold the generated rotation matrix.
	*/
	matrix3x3_t rotationMatrix;

	/**
		Method called to correctly assign the colourAxis, vectorAxis, and rotationAngle member variables.
		@param vectorAxis The vector about which we wish to rotate.
		@param rotationAngle The amount we wish to rotate by.
	*/

	void SetupRotation(Vector3 vectorAxis, RotationAngles rotationAngle);

	/**
		Overloaded version of SetupRotation that accepts a colour instead of a vector.
	*/
public:
	void SetupRotation(Colour colourAxis, RotationAngles rotationAngle);

	/**
		Method to get the rotation's colour axis.
		@return Colour The rotation's colour axis.
	*/
	Colour GetRotationColourAxis();

private:
	/**
		Generates the desired rotation matrix in global coordinates based on the instance's vectorAxis and rotationAngle.
	*/
	void GenerateRotationMatrix();

	/**
		cos function that only returns integers. These numbers are created based on the desired rotation angle.
		@param rotationAngle The rotation angle that will be used in the calculation.
	*/

	int cosDeg(RotationAngles rotationAngle);

	/**
		sin function that only returns integers. These numbers are created based on the desired rotation angle.
		@param rotationAngle The rotation angle that will be used in the calculation.
	*/
	int sinDeg(RotationAngles rotationAngle);

	/**
		Reverses the rotation direction. This is used in the GlobaliseRotation method to ensure that all rotations are performed
		in global coordinates.
		@param inputRotation If required this parameter will be inverted to account for changing from local to global coordinates.
	*/
	RotationAngles InvertRotation(RotationAngles inputRotation);

	/**
		Converts the rotation to be about the global axes in case we try to rotate about a negative axis (i.e. ensure we rotate about
		+x rather than -x to make sure we calculate the rotation correctly).
		@param &vectorAxis A reference to the vector we wish to rotate about.
		@param inputRotation The amount we wish to rotate by.
	*/
	std::array<RotationAngles, 3> GlobaliseRotation(Vector3 &vectorAxis, RotationAngles inputRotation);

	/**
		Performs a matrix multiplication operation of the form [leftMatrix][rightMatrix] on 3x3 matrices.
		@param leftMatrix A reference to the matrix on the left of the multiplication.
		@param rightMatrix A reference to the matrix on the right of the multiplication.
		@return matrix3x3_t Returns the result of the multiplication as a 3x3 matrix.
	*/
	matrix3x3_t MatrixMultiply(matrix3x3_t &leftMatrix, matrix3x3_t &rightMatrix);

	/**
		Generates the correct Rx rotation matrix based on a passed rotation angle.
		@param rotation The desired rotation.
	*/
	void GenerateRxMatrix(RotationAngles rotation);

	/**
		Generates the correct Ry rotation matrix based on a passed rotation angle.
		@param rotation The desired rotation.
	*/
	void GenerateRyMatrix(RotationAngles rotation);

	/**
		Generates the correct Rz rotation matrix based on a passed rotation angle.
		@param rotation The desired rotation.
	*/
	void GenerateRzMatrix(RotationAngles rotation);
};