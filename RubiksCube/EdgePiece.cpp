#include "stdafx.h"
#include "EdgePiece.h"


bool EdgePiece::IsSolved()
{
	return false;
}

bool EdgePiece::HasColour(Colour colourToFind)
{
	for each (Colour colour in pieceColours)
	{
		if (colour == colourToFind)
		{
			return true;
		}
	}

	return false;
}

EdgePiece::EdgePiece()
{
	SetPiece(Colour::NONE, Colour::NONE);
}

EdgePiece::EdgePiece(Colour colour1, Colour colour2)
{
	SetPiece(colour1, colour2);
}


EdgePiece::~EdgePiece()
{
}

void EdgePiece::SetPiece(Colour colour1, Colour colour2)
{
	this->pieceColours[0] = colour1;
	this->pieceColours[1] = colour2;
	SetPiecePosition();

	this->pieceTiles = { {colour1, colour2} };
}

void EdgePiece::SetPiecePosition()
{
	piecePosition = Vector3::VectorFromColours(pieceColours[0], pieceColours[1]);
}
