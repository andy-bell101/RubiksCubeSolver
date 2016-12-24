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
		Class constructor that takes a list of colours to create the piece.
	*/
	Piece(pieceColours_t colours);

	/**
		Class constructor that takes a vector and builds the piece.
	*/
	Piece(Vector3 &buildVector);

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
		Determines whether this piece is in the correct position but NOT fully solved. Returns true if and only if
		the piece is in the right place.
		@return bool Returns true if the piece is solved, false otherwise.
	*/
	bool PositionSolved();

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

	/**
		Returns whether the piece both has a colour and whether that colour is on the face of the passed colour.
		@param tileColour The colour of the tile to search for.
		@param faceColour The colour of the face to search for.
		@return bool Returns true if the piece has the tileColour and that tile is on the face corresponding to the passed face colour.
	*/
	bool HasColourOnFace(Colour tileColour, Colour faceColour);

	/**
		Returns true if the piece is an edge piece.
		@return bool Returns true if the piece is an edge piece, returns false otherwise.
	*/
	bool IsEdgePiece();

	/**
		Returns true if the piece is a corner piece.
		@return bool Returns true if the piece is a corner piece, returns false otherwise.
	*/
	bool IsCornerPiece();

	/**
		Returns true if the piece has a tile of the passed colour that is on the face of the passed colour.
	*/
	bool TileIsOnFace(Colour tileColour, Colour faceColour);
};

