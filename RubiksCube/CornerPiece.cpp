#include "stdafx.h"
#include "CornerPiece.h"


bool CornerPiece::IsSolved()
{
	return false;
}

CornerPiece::CornerPiece()
{
	SetPiece(Colour::NONE, Colour::NONE, Colour::NONE);
}

CornerPiece::CornerPiece(Colour colour1, Colour colour2, Colour colour3)
{
	SetPiece(colour1, colour2, colour3);
}


CornerPiece::~CornerPiece()
{
}

void CornerPiece::SetPiece(Colour colour1, Colour colour2, Colour colour3)
{
	this->pieceColours[0] = colour1;
	this->pieceColours[1] = colour2;
	this->pieceColours[2] = colour3;
	SetPiecePosition();
}

void CornerPiece::SetPiecePosition()
{
	piecePosition = Vector3::VectorFromColours(pieceColours[0], pieceColours[1], pieceColours[2]);
}
