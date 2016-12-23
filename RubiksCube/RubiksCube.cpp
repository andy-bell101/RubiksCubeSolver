// RubiksCube.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Vector3.h"
#include "Rotation.h"
#include "Piece.h"
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

    return 0;
}

