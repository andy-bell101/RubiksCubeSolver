#pragma once
#include "Piece.h"

class EdgePiece :
	public Piece
{
private:
	/**
		Member variable to define the number of tiles that this piece has.
	*/
	static const int numTiles{ 2 };

	/**
		Typedef of std::array of colours to contain the piece's colours.
	*/
	using edgeColours_t = std::array<Colour, numTiles>;

	/**
		Member variable to define the colours of the piece.
	*/
	edgeColours_t pieceColours{};

public:
	/**
		Typedef of a std::array to store the tiles associated with this piece
	*/
	using edgeTiles_t = std::array<Tile, numTiles>;

private:
	/**
		Container for the piece's tiles.
	*/
	edgeTiles_t pieceTiles{};

public:
	EdgePiece();
	
	/**
		Class constructor that takes two colours to create the edge piece.
	*/
	EdgePiece(Colour colour1, Colour colour2);
	~EdgePiece();

	/**
		Sets the edge piece's colours to the colours passed to the function.
		@param colour1 The first colour to set.
		@param colour2 The second colour to set.
	*/
	void SetPiece(Colour colour1, Colour colour2);

	/**
		Sets the edge piece's position based on the colours passed in SetEdgePiece(), such that the piece is in 
		the solved position.
	*/
	void SetPiecePosition();

	/**
		Determines whether this piece is solved or not by checking whether each associated tile is solved.
		@return bool Returns true if the piece is solved, false otherwise.
	*/
	bool IsSolved();

	/**
		Determines whether this piece has a tile which matches the passed colour.
		@param colourToFind The colour to search the piece for.
		@return bool Returns true if the colour is found, false otherwise.
	*/
	bool HasColour(Colour colourToFind);
};

