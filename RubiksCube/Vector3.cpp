#include "stdafx.h"
#include "Vector3.h"
#include <iostream>
#include <string>


using namespace std;

// Using the convention that the White face is at (0, 0, -1),
// the Red face is at (0, 1, 0) and the Blue face is at (1, 0, 0)

Vector3::Vector3()
{
	X = Y = Z = 0;
}

Vector3::Vector3(int X, int Y, int Z)
{
	SetVectorFromInts(X, Y, Z);
}

Vector3::Vector3(Colour inputColour)
{
	Vector3 tempVector = Vector3::ColourToVector(inputColour);
	this->CloneVector(tempVector);
}

Vector3::~Vector3()
{
}

int Vector3::GetX()
{
	return X;
}

int Vector3::GetY()
{
	return Y;
}

int Vector3::GetZ()
{
	return Z;
}

Colour Vector3::ToColour()
{
	// Check that the vector correctly represents a colour, must only have one non-zero component.
	if (Magnitude() != 1)
	{
		// throw error
		std::cerr << "Vector3::ToColour() - Vector has magnitude not equal to 1: ("
			+ to_string(X) + "," + to_string(Y) + "," + to_string(Z) + ")";
		return Colour::NONE;
	}

	if (X > 0)
	{
		return Colour::BLUE;
	}
	else if (X < 0)
	{
		return Colour::GREEN;
	}
	else if (Y > 0) 
	{
		return Colour::RED;
	}
	else if (Y < 0)
	{
		return Colour::ORANGE;
	}
	else if (Z > 0)
	{
		return Colour::YELLOW;
	}
	else if (Z < 0)
	{
		return Colour::WHITE;
	}
}

void Vector3::CloneVector(Vector3 &inputVector)
{
	this->X = inputVector.GetX();
	this->Y = inputVector.GetY();
	this->Z = inputVector.GetZ();
}

Vector3 Vector3::ColourToVector(Colour inputColour)
{
	switch (inputColour)
	{
	case Colour::WHITE:
		return Vector3{ 0, 0, -1 };
	case Colour::BLUE:
		return Vector3{ 1, 0, 0 };
	case Colour::RED:
		return Vector3{ 0, 1, 0 };
	case Colour::YELLOW:
		return Vector3{ 0, 0, 1 };
	case Colour::GREEN:
		return Vector3{ -1, 0, 0 };
	case Colour::ORANGE:
		return Vector3{ 0, -1, 0 };
	case Colour::NONE:
		return Vector3{ 0, 0, 0 };
	default:
		std::cerr << "Vector3::ColourToVector - Passed Colour::BLANK";
		return Vector3{ 0, 0, 0 };
	}
}

int Vector3::Magnitude()
{
	return abs(X) + abs(Y) + abs(Z);
}

void Vector3::SetVectorFromInts(int X, int Y, int Z)
{
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}

Vector3 Vector3::VectorFromColours(std::list<Colour> inputColours)
{
	int index{};
	Colour colours[3]{Colour::NONE};

	for (std::list<Colour>::const_iterator i = inputColours.begin(), end = inputColours.end(); i != end; ++i)
	{
		colours[index] = *i;
	}

	if (colours[0] == colours[1] || colours[0] == colours[2] || colours[1] == colours[2])
	{
		std::cerr << "Vector3::VectorFromColours passed matching colours";
	}

	Vector3 vector1{ Vector3::ColourToVector( colours[0]) };
	Vector3 vector2{ Vector3::ColourToVector( colours[1]) };
	Vector3 vector3{ Vector3::ColourToVector( colours[2]) };
	
	int X;
	int Y;
	int Z;

	X = vector1.GetX() + vector2.GetX() + vector3.GetX();
	Y = vector1.GetY() + vector2.GetY() + vector3.GetY();
	Z = vector1.GetZ() + vector2.GetZ() + vector3.GetZ();

	return Vector3{ X, Y, Z };
}

bool Vector3::CheckVectorForColour(Colour searchColour)
{
	Vector3 tempVector{ Vector3::ColourToVector(searchColour) };

	if (tempVector.GetX() == X || tempVector.GetY() == Y || tempVector.GetZ() == Z)
	{
		return true;
	}

	return false;
}
