#pragma once

#include "Vector3.h"
#include <array>
#include "RotationAngles.h"

/**
	A typedef of a 3x3 matrix, to be used to perform the matrix multiplication for rotation.
*/
typedef std::array<std::array<int, 3>, 3> rotationMatrix_t;

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
		Gets the colour of the axis the rotation is currently set to.
		@return Colour The colour of the rotation's axis.
	*/
	Colour GetColourAxis();

	/**
		Gets the vector axis of the rotation.
		@return Vector The vector axis of the rotation.
	*/
	Vector3 GetVectorAxis();

private:
	/**
		Member variable to represent the rotation's colour axis.
	*/
	Colour colourAxis{ Colour::NONE };

	/**
		Member variable to represent the rotation's vector axis.
	*/
	Vector3 vectorAxis{ 0, 0, 0 };

	/**
		Performs the matrix multiplication required to rotate the passed reference vector
		@param inputVector A reference to the vector that is to be rotated.
	*/
	void Rotate(Vector3 &inputVector);
	/**
		Member variable to store the rotation amount and direction.
	*/
	RotationAngles rotationAngle;
	/**
		Member variable to hold the generated rotation matrix.
	*/
	rotationMatrix_t rotationMatrix;
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
	std::array<RotationAngles, 3> GlobaliseRotation(Vector3 vectorAxis, RotationAngles inputRotation);

	/**
		Multiplies the passed vector by the rotationMatrix and reassigns the vector to become the rotated vector.
		@param &vectorToRotate A reference to the vector that is desired to be rotated.
	*/
	void Rotate(Vector3 &vectorToRotate);
};