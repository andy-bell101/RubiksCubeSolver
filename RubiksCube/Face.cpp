#include "stdafx.h"
#include "Face.h"


Face::Face(Colour faceColour)
{
	this->faceColour = faceColour;
}


Face::~Face()
{
}

void Face::AddPieceToFace(Piece* inputPiece)
{
	if (inputPiece->PieceIsOnFace(faceColour) == true)
	{
		piecesPtr.push_back(inputPiece);
	}
}

void Face::ResetPieces()
{
	piecesPtr.clear();
}

Colour Face::GetFaceColour()
{
	return faceColour;
}

void Face::Rotate(Rotation &rotation)
{
	for each (Piece* piecePtr in piecesPtr)
	{
		piecePtr->Rotate(rotation);
	}
}

bool Face::IsSolved()
{
	for each (Piece* piecePtr in piecesPtr)
	{
		piecePtr->IsSolved();
	}

	return true;
}

bool Face::TileIsOnFace(Piece* piece, Colour tileColour)
{
	if (PieceIsOnFace(piece) == true)
	{
		if (piece->HasColour(tileColour))
		{
			piece->TileIsOnFace(tileColour, faceColour);
		}
	}

	return false;
}

bool Face::PieceIsOnFace(Piece* piece)
{
	for each (Piece* piecePtr in piecesPtr)
	{
		if (piecePtr->GetPieceColours() == piece->GetPieceColours())
		{
			return true;
		}
	}

	return false;
}
