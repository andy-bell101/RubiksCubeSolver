// RubiksCube.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Vector3.h"
#include "Rotation.h"

using namespace std;

int main()
{
	cout << "Hi there!" << endl;
	
	Rotation rotation{ Colour::WHITE, RotationAngles::CLOCKWISE };

	Vector3 testVector{0,0,1};
	Colour testColour = testVector.ToColour();

    return 0;
}

