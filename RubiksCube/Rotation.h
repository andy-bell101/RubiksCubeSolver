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
		Method called from constructors to correctly assign the colourAxis, vectorAxis, and rotationAngle member variables.
	*/

	void SetupRotation( Vector3 vectorAxis, RotationAngles rotationAngle);
	/**
		Generates the desired rotation matrix in global coordinates based on the instance's vectorAxis and rotationAngle.
	*/

	void GenerateRotationMatrix();
	/**
		cos function that only returns integers. These numbers are created based on the desired rotation angle.
	*/

	int cosDeg(RotationAngles rotationAngle);

	/**
		sin function that only returns integers. These numbers are created based on the desired rotation angle.
	*/
	int sinDeg(RotationAngles rotationAngle);

	/**
		Reverses the rotation direction. This is used in the GlobaliseRotation method to ensure that all rotations are performed
		in global coordinates.
	*/
	RotationAngles InvertRotation(RotationAngles inputRotation);

	/**
		Converts the rotation to be about the global axes in case we try to rotate about a negative axis (i.e. ensure we rotate about
		+x rather than -x to make sure we calculate the rotation correctly).
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
		Generates the correct Rx rotation matrix.
	*/
	void GenerateRxMatrix(RotationAngles rotation);

	/**
		Generates the correct Ry rotation matrix.
	*/
	void GenerateRyMatrix(RotationAngles rotation);

	/**
		Generates the correct Rz rotation matrix.
	*/
	void GenerateRzMatrix(RotationAngles rotation);
};