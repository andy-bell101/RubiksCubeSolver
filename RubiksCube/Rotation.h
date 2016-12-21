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
	Rotation(Colour colourAxis, RotationAngles rotationAngle);
	Rotation(Vector3 vectorAxis, RotationAngles rotationAngle);
	Vector3 PerformRotations(std::array<Vector3, 6> inputVectors );
	Colour GetColourAxis();
	Vector3 GetVectorAxis();

private:
	Colour colourAxis{ Colour::NONE };
	Vector3 vectorAxis{ 0, 0, 0 };
	Vector3 Rotate(Vector3 inputVector);
	RotationAngles rotationAngle;
	rotationMatrix_t rotationMatrix;
	void SetupRotation( Vector3 vectorAxis, RotationAngles rotationAngle);
	void GenerateRotationMatrix(Colour colourAxis, RotationAngles rotationAngle);
	void GenerateRotationMatrix(Vector3 vectorAxis, RotationAngles rotationAngle);
	int cosDeg(RotationAngles rotationAngle);
	int sinDeg(RotationAngles rotationAngle);
	RotationAngles InvertRotation(RotationAngles inputRotation);
	std::array<RotationAngles, 3> GlobaliseRotation(Vector3 vectorAxis, RotationAngles inputRotation);
};