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
	Colour opposingColour{ GetOpposingColour(rotation.GetRotationColourAxis()) };

	for each (Face face in faces)
	{
		if (face.GetFaceColour() != opposingColour)
		{
			face.ResetPieces();

			for each (Piece piece in pieces)
			{
				face.AddPieceToFace(&piece);
			}
		}
	}
}

void Cube::SetCubeDirections(Colour faceColour)
{
	ClearCubeDirections();

	// TODO: This is where top and bottom hard coding happens. Fix this.
	directionToColour[(int)Direction::BOTTOM] = Colour::WHITE;
	directionToColour[(int)Direction::TOP] = Colour::YELLOW;

	directionToColour[(int)Direction::FRONT] = faceColour;
	directionToColour[(int)Direction::BACK] = GetOpposingColour(faceColour);

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
	piecesRef_t bottomEdgePieces{};

	Colour colourToFind{ directionToColour[(int)Direction::BOTTOM] };

	Piece debugPiece{};

	for each (Piece piece in pieces)
	{
		if (piece.IsEdgePiece() && piece.HasColour(colourToFind))
		{
			bottomEdgePieces.push_back(&piece);
			debugPiece = piece;
		}
	}
}
