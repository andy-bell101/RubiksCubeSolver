#pragma once

#include <list>
#include "Piece.h"
#include "RotationAngles.h"

class Face
{
public:
	/**
		Class constructor that takes a colour to set the face's colour.
		@param faceColour The desired colour of the face.
	*/
	Face(Colour faceColour);
	~Face();

	/**
		Typedef of a list to hold the face's pieces.
	*/
	using piecesRef_t = std::list<Piece&>;

	/**
		Member variable to hold references to the face's pieces.
	*/
	piecesRef_t piecesRef{};

	/**
		Adds the piece if it is on the face to the face's pieces member variable.
		@param &inputPiece The piece passed from the Cube class, which will be added to the piece member variable.
	*/
	void AddPieceToFace( Piece& inputPiece );

	/**
		Clears the pieces list for the face so that new faces can be added.
	*/
	void ResetPieces();

	/**
		Returns the colour of the face.
		@return Colour The colour of the face.
	*/
	Colour GetFaceColour();

	/**
		Rotates the face by the passed rotation angle.
		@param rotationAngle The desired rotation angle.
	*/
	void Rotate(Rotation &rotation);
	/**
		Returns whether the face is fully solved or not.
		@return bool Returns true if the face is solved, false otherwise.
	*/
	bool IsSolved();

	/**
		Returns true if the tile of the passed colour is on this face.
		@return bool Returns true if the tile of the passed colour is on this face, returns false otherwise.
	*/
	bool TileIsOnFace(Piece& piece,Colour tileColour);

	/**
		Returns true if the passed piece is on this face.
		@return bool Returns true if the passed piece is on this face, returns false otherwise.
	*/
	bool PieceIsOnFace(Piece& piece);

private:
	/**
		Member variable to hold the face's colour.
	*/
	Colour faceColour{};
};

