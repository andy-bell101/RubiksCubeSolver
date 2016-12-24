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

	/**
		Shuffles the cube by randomly generating a sequence of faces and rotation amounts to perform.
		@param shuffleCount Integer representing the number of moves to perform in the shuffle.
	*/
	void Shuffle(int shuffleCount);

	/**
		Method to handle the solution steps.
	*/
	void SolveCube();

private:
	using pieces_t = std::list<Piece>;
	using piecesRef_t = std::list<Piece*>;
	using faces_t = std::list<Face>;

	/**
		Member variable to hold the currently hard coded bottom face.
	*/
	// TODO: Remove use of this hard coding to generalise the application.
	Colour hardcodedBottomFace{ Colour::WHITE };

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
		Member variable to hold the currently set directions of the faces.
	*/
	std::array<Colour, 6> directionToColour{};

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
		Method to set the new directions of the cube by passing the desired front face.
		e.g. setting the Blue face to be the Front face for use in algorithms.
		@param faceColour The face whose front direction we wish to set.
	*/
	void SetCubeDirections( Colour directionColour );

	/**
		Method to return the opposite direction the the passed direction.
		@param inputDirection The direction we wish to invert.
		@return Direction The opposite direction to the the direction passed.
	*/
	Direction GetOpposingDirection(Direction inputDirection);

	/**
		Method to reset the cube directions to Direction::NONE.
	*/
	void ClearCubeDirections();

	/**
		Sets up the 'top cross'.
	*/
	void TopCross();
};

