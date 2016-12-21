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
// 
Vector3 Rotation::PerformRotations(std::array<Vector3, 6> inputVectors)
{
	return Vector3();
}

Colour Rotation::GetColourAxis()
{
	return colourAxis;
}

Vector3 Rotation::GetVectorAxis()
{
	return vectorAxis;
}

Vector3 Rotation::Rotate(Vector3 inputVector)
{
	return Vector3();
}

void Rotation::SetupRotation(Vector3 vectorAxis, RotationAngles rotationAngle)
{
	this->vectorAxis = vectorAxis;
	this->colourAxis = vectorAxis.ToColour();
	this->rotationAngle = rotationAngle;
}

void Rotation::GenerateRotationMatrix(Colour colourAxis, RotationAngles rotationAngle)
{
	GenerateRotationMatrix(Vector3::ColourToVector(colourAxis), rotationAngle);
}

void Rotation::GenerateRotationMatrix(Vector3 vectorAxis, RotationAngles rotationAngle)
{
	if (vectorAxis.Magnitude()!= 1)
	{
		std::cerr << "Vector3::ToColour() - Vector has magnitude not equal to 1: ("
			+ to_string(vectorAxis.GetX()) + "," + to_string(vectorAxis.GetY()) + "," + to_string(vectorAxis.GetZ()) + ")";
		return;
	}

	array<RotationAngles, 3> normalisedRotations{RotationAngles::NONE};
	normalisedRotations = GlobaliseRotation(vectorAxis, rotationAngle);

	RotationAngles xAxisRotation{ normalisedRotations[0] };
	RotationAngles yAxisRotation{ normalisedRotations[1] };
	RotationAngles zAxisRotation{ normalisedRotations[2] };

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