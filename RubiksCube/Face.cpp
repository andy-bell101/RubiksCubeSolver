#include "stdafx.h"
#include "Face.h"


Face::Face(Colour faceColour)
{
	this->faceColour = faceColour;
}


Face::~Face()
{
}

void Face::AddPiecesToFace(piecesRef_t &inputPieces)
{
	piecesRef.clear();

	for (piecesRef_t::const_iterator i = inputPieces.begin(), end = inputPieces.end(); i != end; ++i)
	{
		if ( ( *i )->PieceIsOnFace( faceColour ) == true )
		{
			piecesRef.push_back(*i);
		}
	}
}

Colour Face::GetFaceColour()
{
	return faceColour;
}

void Face::Rotate(Rotation &rotation)
{
	for (piecesRef_t::iterator i = piecesRef.begin(), end = piecesRef.end(); i != end; ++i)
	{
		(*i)->Rotate(rotation);
	}
}

bool Face::IsSolved()
{
	for (piecesRef_t::iterator i = piecesRef.begin(), end = piecesRef.end(); i != end; ++i)
	{
		if ((*i)->IsSolved() == false)
		{
			return false;
		}
	}

	return true;
}
