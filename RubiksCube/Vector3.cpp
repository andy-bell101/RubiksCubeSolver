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
	Colour colours[3]{Colour::NONE, Colour::NONE, Colour::NONE};

	for (std::list<Colour>::const_iterator i = inputColours.begin(), end = inputColours.end(); i != end; ++i)
	{
		colours[index] = *i;
		index++;
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

Vector3 Vector3::CrossProduct(Vector3 & leftVector, Vector3 & rightVector)
{
	int x{ 0 }, y{ 0 }, z{ 0 };

	x = leftVector.GetY() * rightVector.GetZ() - leftVector.GetZ() * rightVector.GetY();
	y = leftVector.GetZ() * rightVector.GetX() - leftVector.GetX() * rightVector.GetZ();
	z = leftVector.GetX() * rightVector.GetY() - leftVector.GetY() * rightVector.GetX();

	return Vector3{ x,y,z };
}

Colour Vector3::CrossProduct(Colour & leftColour, Colour & rightColour)
{
	return CrossProduct(ColourToVector(leftColour), ColourToVector(rightColour)).ToColour();
}

std::list<Colour> Vector3::ColoursFromVector(Vector3 &inputVector)
{
	int X = inputVector.GetX();
	int Y = inputVector.GetY();
	int Z = inputVector.GetZ();

	std::list<Colour> outputList{};

	Vector3 testVector{ 0, 0, 0 };
	Colour tempColour{ Colour::NONE };

	testVector.SetVectorFromInts(X, 0, 0);
	tempColour = testVector.ToColour();

	if ( tempColour != Colour::NONE )
	{
		outputList.push_back(tempColour);
	}

	testVector.SetVectorFromInts(0, Y, 0);
	tempColour = testVector.ToColour();

	if (tempColour != Colour::NONE)
	{
		outputList.push_back(tempColour);
	}

	testVector.SetVectorFromInts(0, 0, Z);
	tempColour = testVector.ToColour();

	if (tempColour != Colour::NONE)
	{
		outputList.push_back(tempColour);
	}

	return outputList;
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

bool Vector3::Equals(Vector3 & comparisonVector)
{
	if (X == comparisonVector.GetX() && Y == comparisonVector.GetY() && Z == comparisonVector.GetZ())
	{
		return true;
	}

	return false;
}
