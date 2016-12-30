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

	for each (Tile tile in pieceTiles)
	{
		tile.Rotate(rotation);
	}
}

bool Piece::HasColourOnFace(Colour tileColour, Colour faceColour)
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

list<Colour> Piece::GetPieceColours()
{
	return pieceColours;
}

Colour Piece::GetFaceTileIsOn(Colour tileColour)
{
	if (HasColour(tileColour) == false)
	{
		std::cerr << "Piece::GetFaceTileIsOn() was passed a colour that is not on the piece.";
		return Colour::NONE;
	}

	for each (Tile tile in pieceTiles)
	{
		if (tile.GetTileColour() == tileColour)
		{
			return tile.GetTileFace();
		}
	}
}

void Piece::SetPiece(Piece::pieceColours_t colours)
{
	for each (Colour colour in colours)
	{
		this->pieceColours.push_back(colour);
		this->pieceTiles.push_back(Tile(colour));
	}

	numTiles = pieceTiles.size();

	SetPiecePosition();
}

void Piece::SetPiecePosition()
{
	piecePosition = Vector3::VectorFromColours(pieceColours);
}