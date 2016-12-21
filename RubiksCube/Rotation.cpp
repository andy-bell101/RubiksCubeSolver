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

	vectorToRotate.SetVectorFromInts(rotatedArray[0], rotatedArray[1], rotatedArray[2]);
}

void Rotation::GenerateRxMatrix(RotationAngles rotation)
{
	Rx = {{
		{ 1, 0               , 0                 },
		{ 0, cosDeg(rotation), -sinDeg(rotation) },
		{ 0, sinDeg(rotation),  cosDeg(rotation) }
	}};
}

void Rotation::GenerateRyMatrix(RotationAngles rotation)
{
	Ry = {{
		{ cosDeg(rotation), 0, -sinDeg(rotation) },
		{ 0               , 1, 0                 },
		{ sinDeg(rotation), 0,  cosDeg(rotation) }
	}};
}

void Rotation::GenerateRzMatrix(RotationAngles rotation)
{
	Rz = {{
		{ cosDeg(rotation), -sinDeg(rotation), 0 },
		{ sinDeg(rotation),  cosDeg(rotation), 0 },
		{ 0				  , 0				 , 1 }
	}};
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

	// Generate the rotations about the individual axes
	GenerateRxMatrix(xAxisRotation);
	GenerateRyMatrix(yAxisRotation);
	GenerateRzMatrix(zAxisRotation);

	// Perform calculations to set up the rotationMatrix
	rotationMatrix = MatrixMultiply(Rz, MatrixMultiply(Ry, Rx));
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
		std::cerr << "Rotation::sinDeg passed RotationAngles::BLANK";
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

array<RotationAngles, 3> Rotation::GlobaliseRotation(Vector3 &vectorAxis, RotationAngles inputRotation)
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

matrix3x3_t Rotation::MatrixMultiply(matrix3x3_t &leftMatrix, matrix3x3_t &rightMatrix)
{
	matrix3x3_t resultMatrix{};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			resultMatrix[i][j] = leftMatrix[i][j] * rightMatrix[j][i];
		}
	}

	return resultMatrix;
}