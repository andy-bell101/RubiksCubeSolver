// RubiksCube.cpp : Defines the entry point for the console application.

/**
	The application is currently hard coded to use the White face as the bottom face and the Yellow face as the top face.
	This should be fixed in future versions to fully generalise the application.
*/

//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Vector3.h"
#include "Cube.h"
#include <list>

using namespace std;

int main()
{
	cout << "Hi there!" << endl;
	
	Rotation rotation{ Colour::BLUE, RotationAngles::DOUBLETURN };

	Vector3 testVector{0,1,0};
	Colour testColour = testVector.ToColour();
	rotation.Rotate(testVector);
	Colour rotatedColour = testVector.ToColour();

	Piece::pieceColours_t pieceColours{Colour::WHITE, Colour::BLUE, Colour::RED};

	Piece redBlueWhite{pieceColours};
	redBlueWhite.Rotate(rotation);
	bool testBool = redBlueWhite.PieceIsOnFace(Colour::RED);

	Cube cube{};
	cube.SolveCube();

    return 0;
}

