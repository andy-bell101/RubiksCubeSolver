#include "stdafx.h"
#include "Face.h"


Face::Face(Colour faceColour)
{
	this->faceColour = faceColour;
}


Face::~Face()
{
}

void Face::AddPiecesToFace(pieces_t &inputPieces)
{
	for (pieces_t::const_iterator i = inputPieces.begin(), end = inputPieces.end(); i != end; ++i)
	{
		if ( ( *i )->PieceIsOnFace( faceColour ) == true )
		{
			pieces.push_back(*i);
		}
	}
}

Colour Face::GetFaceColour()
{
	return faceColour;
}

void Face::Rotate(Rotation &rotation)
{
	for (pieces_t::iterator i = pieces.begin(), end = pieces.end(); i != end; ++i)
	{
		(*i)->Rotate(rotation);
	}
}
