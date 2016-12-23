#pragma once

#include "Colour.h"
#include "Vector3.h"
#include "Rotation.h"

class Tile
{
public:
	Tile();
	/**
		Class constructor which requires the tile be assigned a colour and sets the tile to that colour and to be on that face.
		@param tileColour The colour of the tile.
	*/
	Tile(Colour tileColour);
	~Tile();

	/**
		Returns whether the tile's colour and direction match (i.e. the tile is on the correct face to be considered solved).
		@return A boolean representing whether the tile is solved (true) or not (false).
	*/
	bool IsSolved();

	/**
		Returns the colour of the tile.
		@return Colour The tile's colour.
	*/
	Colour GetTileColour();

	/**
		Returns the direction of the tile (which also represents the face it lies on).
		@return Vector3 The tile's direction.
	*/
	Vector3 GetTileDirection();

	/**
		Returns a reference to the direction of the tile (which also represents the face it lies on).
		@return Vector3 The tile's direction.
	*/
	Vector3& GetTileDirectionReference();

	/**
		Returns the tile's direction as a colour (i.e. returns which face the tile is currently on).
		@return Colour The tile's direction as a colour.
	*/
	Colour GetTileFace();

	/**
		Rotates the tile's direction by the passed rotation.
		@param &rotation Reference to the current rotation instance.
	*/
	void Rotate(Rotation &rotation);

private:
	/**
		Member variable to hold the tile's colour.
	*/
	Colour tileColour{};
	/**
		Member variable to hold the tile's direction.
	*/
	Vector3 tileDirection{};
};

