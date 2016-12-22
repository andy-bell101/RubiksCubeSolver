#pragma once

#include <array>
#include <list>
#include "Tile.h"
#include "Rotation.h"

using namespace std;

class Piece
{
protected:
	/**
	Member variable to define the number of tiles that this piece has.
	*/
	int numTiles{ 1 };

public:
	/**
	Typedef of std::array of colours to contain the piece's colours.
	*/
	using pieceColours_t = list<Colour>;

	/**
	Typedef of a std::array to store the tiles associated with this piece
	*/
	using pieceTiles_t = list<Tile>;

protected:
	/**
	Container for the piece's tiles.
	*/
	pieceTiles_t pieceTiles{};

	/**
	Member variable to define the colours of the piece.
	*/
	pieceColours_t pieceColours{};

	/**
	Member variable to hold the piece's position vector.
	*/
	Vector3 piecePosition{};

public:
	Piece();

	/**
	Class constructor that takes two colours to create the edge piece.
	*/
	Piece(pieceColours_t colours);
	~Piece();

	/**
	Gets a reference to the piece's position vector.
	return Vector& Reference to the piece's position vector.
	*/
	Vector3 & GetPiecePositionReference();

	/**
	Sets the edge piece's colours to the colours passed to the function.
	@param colour1 The first colour to set.
	@param colour2 The second colour to set.
	*/
	void SetPiece(pieceColours_t colours);

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

	/**
	Determine whether this piece is on the face corresponding to the colour passed.
	@param faceColour The colour of the face to check that this piece is on.
	@return bool Returns true if the piece is on the face corresponding to the passed colour, otherwise returns false.
	*/
	bool PieceIsOnFace(Colour faceColour);

	/**
	Rotates the piece using the passed Rotation reference.
	@param &rotation The rotation to perform.
	*/
	void Rotate(Rotation &rotation);
};

