#pragma once

#include <list>
#include "Piece.h"
#include "Face.h"
#include <iostream>

enum class Direction
{
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	NONE
};

class Cube
{
public:
	Cube();
	~Cube();

	/**
		Constructs the cube from the pieces. Begins in the solved state.
	*/
	void BuildSolvedCube();

	/**
		Rotates the face corresponding to the passed colour by the passed rotation amount.
		@param faceColour Colour of the face to be rotated.
		@param rotationAngle The desired amount of rotation.
	*/
	void RotateFace(Colour faceColour, RotationAngles rotationAngle);

	/**
		Returns whether the cube is solved or not.
		@return bool Returns true if the cube is solved, returns false otherwise.
	*/
	bool IsSolved();

private:
	using pieces_t = std::list<Piece>;
	using faces_t = std::list<Face>;

	/**
		Member variable to hold the cube pieces.
	*/
	pieces_t pieces{};

	/**
		Member variable to hold the cube faces.
	*/
	faces_t faces{};

	/**
		Member variable to hold the current rotation.
	*/
	Rotation rotation{};

	/**
		Method to return the passed colour's opposing colour on the cube.
		@param inputColour The colour whose opposite we want to find.
		@return opposingColour The colour on the opposite face of the cube to the colour passed.
	*/
	Colour GetOpposingColour(Colour inputColour);

	/**
		Method to ensure that the faces' piece references are updated after a move. Remember to ignore the face
		opposite the move to reduce compute time.
	*/
	void ResetFaceReferences();

	/**
		Method to set the new directions of the cube e.g. setting the Blue face to be the Front face for use in algorithms.
		@param faceColour The face whose direction we wish to set.
		@param direction The direction we wish to set that face to.
	*/
	void SetCubeDirections( Colour faceColour, Direction direction );
};

