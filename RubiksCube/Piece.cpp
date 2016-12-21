#include "stdafx.h"
#include "Piece.h"


Piece::Piece()
{
}

Piece::~Piece()
{
}

Vector3 & Piece::GetPiecePositionReference()
{
	return piecePosition;
}
