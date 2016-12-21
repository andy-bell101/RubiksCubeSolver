#pragma once

#include <array>
#include "Tile.h"

class Piece
{
protected:
	/**
		A member variable to store the piece's position.
	*/
	Vector3 piecePosition{};

public:
	Piece();
	~Piece();

	/**
		Returns a reference to the piece's position so that it can be rotated.
	*/
	Vector3 & GetPiecePositionReference();
};

