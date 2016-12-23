#pragma once

#include <list>
#include "Piece.h"
#include "RotationAngles.h"

class Face
{
public:
	/**
		Class constructor that takes a colour to set the face's colour an adds any pieces that match the face colour to a reference list.
		@param faceColour The desired colour of the face.
	*/
	Face(Colour faceColour);
	~Face();

	/**
		Typedef of a list to hold the face's pieces.
	*/
	using piecesRef_t = std::list<Piece*>;

	/**
		Member variable to hold references to the face's pieces.
	*/
	piecesRef_t piecesRef{};

	/**
		Iterates through the passed list of references and adds any pieces that are on the face to the face's pieces member variable.
		@param &inputPieces The list of pieces passed from the Cube class, from which the pieces on this face will be added to 
							the piece member variable.
	*/
	void AddPiecesToFace( piecesRef_t &inputPieces );

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

private:
	/**
		Member variable to hold the face's colour.
	*/
	Colour faceColour{};
};

