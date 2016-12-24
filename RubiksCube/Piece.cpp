#include "stdafx.h"
#include "Piece.h"


Piece::Piece()
{
	SetPiece({});
}

Piece::Piece(Piece::pieceColours_t colours)
{
	SetPiece(colours);
}

Piece::Piece(Vector3 &buildVector)
{
	SetPiece(Vector3::ColoursFromVector(buildVector));
}

Piece::~Piece()
{
}

Vector3 & Piece::GetPiecePositionReference()
{
	return piecePosition;
}

bool Piece::IsSolved()
{
	for each (Tile tile in pieceTiles)
	{
		if (tile.IsSolved() == false)
		{
			return false;
		}
	}

	return true;
}

bool Piece::PositionSolved()
{
	if (piecePosition.Equals(Vector3::VectorFromColours(pieceColours)) && IsSolved() == false)
	{
		return true;
	}

	return false;
}

bool Piece::HasColour(Colour colourToFind)
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

bool Piece::PieceIsOnFace(Colour faceColour)
{
	return piecePosition.CheckVectorForColour(faceColour);
}

void Piece::Rotate(Rotation &rotation)
{
	rotation.Rotate(piecePosition);

	for (pieceTiles_t::iterator i = pieceTiles.begin(), end = pieceTiles.end(); i != end; ++i)
	{
		(*i).Rotate(rotation);
	}
}

bool Piece::HasColourOnFace(Colour tileColour, Colour faceColour)
{
	for (pieceTiles_t::iterator i = pieceTiles.begin(), end = pieceTiles.end(); i != end; ++i)
	{
		if ((*i).GetTileColour() == tileColour && (*i).GetTileFace() == faceColour)
		{
			return true;
		}
	}

	return false;
}

bool Piece::IsEdgePiece()
{
	if (numTiles == 2) return true;

	return false;
}

bool Piece::IsCornerPiece()
{
	if (numTiles == 3) return true;

	return false;
}

bool Piece::TileIsOnFace(Colour tileColour, Colour faceColour)
{
	for each (Tile tile in pieceTiles)
	{
		if (tile.GetTileColour() == tileColour && tile.GetTileFace() == faceColour)
		{
			return true;
		}
	}

	return false;
}

void Piece::SetPiece(Piece::pieceColours_t colours)
{
	pieceColours = pieceColours_t{};
	pieceTiles = pieceTiles_t{};
	// What the fuck is going on here?! Black magic shit I got from the internet
	// http://www.cplusplus.com/forum/general/22957/

	for (pieceColours_t::const_iterator i = colours.begin(), end = colours.end(); i != end; ++i)
	{
		this->pieceColours.push_back( *i );
		this->pieceTiles.push_back( (Tile( *i )) );
	}

	numTiles = pieceTiles.size();

	SetPiecePosition();
}

void Piece::SetPiecePosition()
{
	piecePosition = Vector3::VectorFromColours(pieceColours);
}