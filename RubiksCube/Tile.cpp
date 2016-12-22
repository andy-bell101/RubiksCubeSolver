#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(Colour tileColour)
{
	this->tileColour = tileColour;
	this->tileDirection = Vector3::ColourToVector(tileColour);
}


Tile::~Tile()
{
}

bool Tile::IsSolved()
{
	if (tileColour == tileDirection.ToColour())
	{
		return true;
	}

	return false;
}

Colour Tile::GetTileColour()
{
	return tileColour;
}

Vector3 Tile::GetTileDirection()
{
	return tileDirection;
}

Vector3 & Tile::GetTileDirectionReference()
{
	return tileDirection;
}

Colour Tile::GetTileFace()
{
	return tileDirection.ToColour();
}

void Tile::Rotate(Rotation & rotation)
{
	rotation.Rotate(tileDirection);
}
