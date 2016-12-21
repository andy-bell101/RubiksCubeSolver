#pragma once
#include "Piece.h"

class CornerPiece :
	public Piece
{
private:
	/**
		Member variable to define the number of tiles that this piece has.
	*/
	static const int numTiles{ 3 };

	/**
		Typedef of std::array of colours to contain the piece's colours.
	*/
	using cornerColours_t = std::array<Colour, numTiles>;

	/**
		Member variable to define the colours of the piece.
	*/
	cornerColours_t pieceColours{};

public:
	/**
		Typedef of a std::array to store the tiles associated with this piece
	*/
	using cornerTiles_t = std::array<Tile, numTiles>;

private:
	/**
	Container for the piece's tiles.
	*/
	cornerTiles_t pieceTiles{};

public:
	CornerPiece();

	/**
		Class constructor that takes three colours to create the edge piece.
	*/
	CornerPiece(Colour colour1, Colour colour2, Colour colour3);
	~CornerPiece();

	/**
		Sets the edge piece's colours to the colours passed to the function.
		@param colour1 The first colour to set.
		@param colour2 The second colour to set.
		@param colour3 The third colour to set.
	*/
	void SetPiece(Colour colour1, Colour colour2, Colour colour3);

	/**
		Sets the piece's position based on the colours passed in SetCornerPiece(), such that the piece is in
		the solved position.
	*/
	void SetPiecePosition();

	/**
		Determines whether this piece is solved or not by checking whether each associated tile is solved.
		@return bool Returns true if the piece is solved, false otherwise.
	*/
	bool IsSolved();
};

