#include "stdafx.h"
#include "Rotation.h"

#include <iostream>
#include <string>

using namespace std;

// Constructor that will build the rotation from a colour direction and a rotation angle
Rotation::Rotation(Colour colourAxis, RotationAngles rotationAngle)
{
	Vector3 vectorAxis{ Vector3::ColourToVector(colourAxis) };
	SetupRotation(vectorAxis, rotationAngle);
}
// Constructor that will build the rotation from a vector direction and a rotation angle
Rotation::Rotation(Vector3 vectorAxis, RotationAngles rotationAngle)
{
	SetupRotation(vectorAxis, rotationAngle);
}

Colour Rotation::GetColourAxis()
{
	return colourAxis;
}

Vector3 Rotation::GetVectorAxis()
{
	return vectorAxis;
}

void Rotation::Rotate(Vector3 &vectorToRotate)
{
	int arrayToRotate[3] = { vectorToRotate.GetX(), vectorToRotate.GetY(), vectorToRotate.GetZ() };
	int rotatedArray[3] = { 0, 0, 0 };
	
	// i represents rows in the rotatedArray
	for (int i = 0; i < 3; i++)
	{
		// j represents rows in the rotationMatrix
		for (int j = 0; j < 3; j++)
		{
			// k represents columns in the rotationMatrix
			for (int k = 0; k < 3; k++)
			{
				rotatedArray[i] += rotationMatrix[j][k] * arrayToRotate[k];
			}
		}
	}

	&vectorToRotate.VectorFromInts();
}

void Rotation::SetupRotation(Vector3 vectorAxis, RotationAngles rotationAngle)
{
	this->vectorAxis = vectorAxis;
	this->colourAxis = vectorAxis.ToColour();
	this->rotationAngle = rotationAngle;
}

void Rotation::GenerateRotationMatrix()
{
	// Check that the vectorAxis is a valid colour vector. If not throw error.
	if (vectorAxis.Magnitude()!= 1)
	{
		std::cerr << "Rotation::GenerateRotationMatrix() - Vector has magnitude not equal to 1: ("
			+ to_string(vectorAxis.GetX()) + "," + to_string(vectorAxis.GetY()) + "," + to_string(vectorAxis.GetZ()) + ")";
		return;
	}

	array<RotationAngles, 3> normalisedRotations{RotationAngles::NONE};

	// Ensure that the x, y, and z axis rotations represent rotations about the global axes rather their inverses (i.e. stop rotations about
	// the -x axis)
	normalisedRotations = GlobaliseRotation(vectorAxis, rotationAngle);
	RotationAngles xAxisRotation{ normalisedRotations[0] };
	RotationAngles yAxisRotation{ normalisedRotations[1] };
	RotationAngles zAxisRotation{ normalisedRotations[2] };

	// Perform calculations to set up the rotationMatrix
	rotationMatrix[0][0] = cosDeg(yAxisRotation) * cosDeg(zAxisRotation);
	rotationMatrix[0][1] = cosDeg(zAxisRotation) * sinDeg(xAxisRotation) * sinDeg(yAxisRotation) - cosDeg(xAxisRotation) * sinDeg(zAxisRotation);
	rotationMatrix[0][2] = cosDeg(xAxisRotation) * cosDeg(zAxisRotation) * sinDeg(yAxisRotation) + sinDeg(xAxisRotation) * sinDeg(zAxisRotation);
	rotationMatrix[1][0] = cosDeg(yAxisRotation) * sinDeg(zAxisRotation);
	rotationMatrix[1][1] = cosDeg(xAxisRotation) * cosDeg(zAxisRotation) + sinDeg(xAxisRotation) * sinDeg(yAxisRotation) * sinDeg(zAxisRotation);
	rotationMatrix[1][2] = cosDeg(xAxisRotation) * sinDeg(yAxisRotation) * sinDeg(zAxisRotation) - cosDeg(zAxisRotation) * sinDeg(xAxisRotation);
	rotationMatrix[2][0] = -sinDeg(yAxisRotation);
	rotationMatrix[2][1] = cosDeg(yAxisRotation) * sinDeg(xAxisRotation);
	rotationMatrix[2][2] = cosDeg(xAxisRotation) * cosDeg(yAxisRotation);
}



int Rotation::cosDeg(RotationAngles rotationAngle)
{
	switch (rotationAngle)
	{
	case RotationAngles::CLOCKWISE:
		return 0;
	case RotationAngles::DOUBLETURN:
		return -1;
	case RotationAngles::ANTICLOCKWISE:
		return 0;
	case RotationAngles::NONE:
		return 1;
	default:
		std::cerr << "Rotation::cosDeg passed RotationAngles::BLANK";
		return -2;
	}
}

int Rotation::sinDeg(RotationAngles rotationAngle)
{
	switch (rotationAngle)
	{
	case RotationAngles::CLOCKWISE:
		return 1;
	case RotationAngles::DOUBLETURN:
		return 0;
	case RotationAngles::ANTICLOCKWISE:
		return -1;
	case RotationAngles::NONE:
		return 0;
	default:
		std::cerr << "Rotation::cosDeg passed RotationAngles::BLANK";
		return -2;
	}
}

RotationAngles Rotation::InvertRotation(RotationAngles inputRotation)
{
	if (inputRotation == RotationAngles::ANTICLOCKWISE)
	{
		return RotationAngles::CLOCKWISE;
	}
	else if (inputRotation == RotationAngles::CLOCKWISE)
	{
		return RotationAngles::ANTICLOCKWISE;
	}
	else
	{
		return inputRotation;
	}
}

array<RotationAngles, 3> Rotation::GlobaliseRotation(Vector3 vectorAxis, RotationAngles inputRotation)
{
	array<RotationAngles, 3> returnArray{ RotationAngles::NONE };

	if (vectorAxis.GetX() > 0)
	{
		returnArray[0] = inputRotation;
	}
	else if (vectorAxis.GetX() < 0)
	{
		returnArray[0] = InvertRotation(inputRotation);
	}
	else if (vectorAxis.GetY() > 0)
	{
		returnArray[1] = inputRotation;
	}
	else if (vectorAxis.GetY() < 0)
	{
		returnArray[1] = InvertRotation(inputRotation);
	}
	else if (vectorAxis.GetZ() > 0)
	{
		returnArray[2] = inputRotation;
	}
	else if (vectorAxis.GetZ() < 0)
	{
		returnArray[2] = InvertRotation(rotationAngle);
	}

	return returnArray;
}