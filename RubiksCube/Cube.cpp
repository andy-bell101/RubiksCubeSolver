#include "stdafx.h"
#include "Cube.h"


Cube::Cube()
{
	BuildSolvedCube();

}


Cube::~Cube()
{
}

void Cube::BuildSolvedCube()
{
	pieces.clear();

	// Create the cube's faces.
	// This code is shit
	for (int i = (int)Colour::WHITE; i < (int)Colour::NONE; i++)
	{
		faces.push_back({ (Colour)i });
	}

	// Create the pieces. Make sure not to create pieces at the face centres or the cube centre.
	// This is handled by the if statements. We want to make sure that we don't have 2 or more
	// components of our vector equal to 0.
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			for (int z = -1; z < 2; z++)
			{
				if ((x == 0 && y == 0) == false)
				{
					if ((x == 0 && z == 0) == false)
					{
						if ((y == 0 && z == 0) == false)
						{
							pieces.push_back(Piece(Vector3(x, y, z)));
						}
					}
				}
			}
		}
	}

	// Cube should now be constructed.
}

void Cube::RotateFace(Colour faceColour, RotationAngles rotationAngle)
{
	rotation.SetupRotation(faceColour, rotationAngle);

	for each (Face face in faces)
	{
		if (face.GetFaceColour() == faceColour)
		{
			face.Rotate(rotation);
			ResetFaceReferences();
		}
	}
}

bool Cube::IsSolved()
{
	for each (Piece piece in pieces)
	{
		if (piece.IsSolved() == false)
		{
			return false;
		}
	}

	return true;
}

void Cube::Shuffle(int shuffleCount)
{
	//TODO: Implement this function.
}

void Cube::SolveCube()
{
	TopCross();
}

Colour Cube::GetOpposingColour(Colour inputColour)
{
	switch (inputColour)
	{
	case Colour::WHITE:
		return Colour::YELLOW;
	case Colour::RED:
		return Colour::ORANGE;
	case Colour::BLUE:
		return Colour::GREEN;
	case Colour::YELLOW:
		return Colour::WHITE;
	case Colour::ORANGE:
		return Colour::RED;
	case Colour::GREEN:
		return Colour::BLUE;
	case Colour::NONE:
		std::cerr << "Cube::GetOpposingColour passed Colour::NONE";
		return Colour::NONE;
	default:
		std::cerr << "Cube::GetOpposingColour passed Colour::BLANK";
		return Colour::BLANK;
	}
}

void Cube::ResetFaceReferences()
{
	// The current rotation face and its opposite won't change in the rotation so we don't need to reset them.
	Colour faceColour{ rotation.GetRotationColourAxis() };
	Colour opposingFaceColour{ GetOpposingColour(faceColour) };

	for each (Face face in faces)
	{
		// Here we make sure not to change unchanged faces.
		if (face.GetFaceColour() != opposingFaceColour && face.GetFaceColour() != faceColour)
		{
			face.ResetPieces();

			// This could be very intensive.
			// TODO: Possibly implement more efficiently if possible.
			for each (Piece piece in pieces)
			{
				face.AddPieceToFace(piece);
			}
		}
	}
}

void Cube::SetCubeDirections(Colour faceColour)
{
	ClearCubeDirections();

	directionToColour[(int)Direction::FRONT] = faceColour;
	directionToColour[(int)Direction::BACK] = GetOpposingColour(faceColour);

	// TODO: This is where top and bottom hard coding happens. Fix this.
	directionToColour[(int)Direction::BOTTOM] = Colour::WHITE;
	directionToColour[(int)Direction::TOP] = Colour::YELLOW;

	directionToColour[(int)Direction::RIGHT] = Vector3::CrossProduct(directionToColour[(int)Direction::TOP], directionToColour[(int)Direction::FRONT]);
	directionToColour[(int)Direction::LEFT] = GetOpposingColour(directionToColour[(int)Direction::RIGHT]);
}

Direction Cube::GetOpposingDirection(Direction inputDirection)
{
	switch (inputDirection)
	{
	case Direction::FRONT:
		return Direction::BACK;
	case Direction::BACK:
		return Direction::FRONT;
	case Direction::LEFT:
		return Direction::RIGHT;
	case Direction::RIGHT:
		return Direction::LEFT;
	case Direction::TOP:
		return Direction::BOTTOM;
	case Direction::BOTTOM:
		return Direction::TOP;
	default:
		std::cerr << "Cube::GetOpposingDirection passed Direction::NONE";
		return Direction::NONE;
	}
}

void Cube::ClearCubeDirections()
{
	for (int i = 0; i < (int)directionToColour.size(); i++)
	{
		directionToColour[i] = Colour::NONE;
	}
}

void Cube::TopCross()
{
	// This will contain references to all the bottom edge pieces, regardless of their positioning
	piecesRef_t bottomEdgePieces{};
	// This will contain references to all the bottom edge pieces that are correctly positioned and oriented on the top face.
	piecesRef_t positionedEdgePieces{};

	Colour bottomColour{ directionToColour[(int)Direction::BOTTOM] };
	Colour topColour{ directionToColour[(int)Direction::TOP] };
	// Holds the other colour on the edge piece we will be working with. Declared outside of the loop to improve performance.
	Colour otherPieceColour{Colour::NONE};
	// Holds the colour of the face to be rotated. Declared outside of the loop to improve performance.
	Colour faceToRotate{ Colour::NONE };

	// This loop builds the list of bottomEdgePieces.
	for each (Piece piece in pieces)
	{
		if (piece.IsEdgePiece() && piece.HasColour(bottomColour))
		{
			bottomEdgePieces.push_back(piece);
		}
	}

	// This loop builds the list of positionedEdgePieces if any are in the correct position and orientation.
	for each (Piece& pieceRef in bottomEdgePieces)
	{
		if (pieceRef.TileIsOnFace(bottomColour, topColour) == true)
		{
			positionedEdgePieces.push_back(pieceRef);
		}
	}

	// Run through all the bottom edge pieces and position them.
	for each (Piece& pieceRef in bottomEdgePieces)
	{
		// Here we check that the piece isn't already in the correct position. As a result of some rotations we might
		// position the piece correctly unintentionally. We catch that case here and add it to the positionedEdgePieces
		// in the else statement.
		if (pieceRef.TileIsOnFace(bottomColour, topColour) == false)
		{
			// Since we are using generalised piece classes and not specific edge and corner piece classes we need to iterate
			// through the list of colours to get the other colour on the edge piece.
			for each (Colour colour in pieceRef.GetPieceColours())
			{
				if (colour != bottomColour)
				{
					otherPieceColour = colour;
					break;
				}
			}

			faceToRotate = pieceRef.GetFaceTileIsOn(otherPieceColour);

			// If faceToRotate corresponds to the top or bottom face then there is no single rotation that will
			// get us where we want. We have to deal with this case.
			if (faceToRotate != bottomColour && faceToRotate != topColour)
			{
				// Make sure that the rotation won't displace any of the pieces we've already positioned.
				if (positionedEdgePieces.size() != 0)
				{
					Piece& pieceOnRotateAndTopFaces{ GetPieceAt(faceToRotate, topColour) };

					for each (Piece& positionedEdgePiece in positionedEdgePieces)
					{

					}
				}
			}
			// The case that the face we would have to rotate is the top face.
			else if (faceToRotate == topColour)
			{

			}
			// The case that the face we would have to rotate is the bottom face.
			else
			{

			}
		}
		else
		{
			positionedEdgePieces.push_back(pieceRef);
		}
	}
}

Piece & Cube::GetPieceAt(Colour face1, Colour face2, Colour face3)
{
	Vector3 vector1{ face1 };
	Vector3 vector2{ face2 };
	Vector3 vector3{ face3 };

	Vector3 resultantVector
	{
		vector1.GetX() + vector2.GetX() + vector3.GetX(),
		vector1.GetY() + vector2.GetY() + vector3.GetY(),
		vector1.GetZ() + vector2.GetZ() + vector3.GetZ()
	};

	Vector3 piecePosition{};

	for each (Piece piece in pieces)
	{
		piecePosition = piece.GetPiecePositionReference();
		if (piecePosition.Equals(resultantVector) == true)
		{
			return piece;
		}
	}

	std::cerr << "Cube::GetPieceAt() passed an invalid combination of colours";
	exception{};
}
