#pragma once

#include "Colour.h"
#include <list>

class Vector3
{
public:
	/**
		Instantiates a new Vector3 with coordinates { 0, 0, 0 }.
	*/
	Vector3();

	/**
		Instantiates a new Vector3 with coordinates { x, y, z }.
		@param x The vector's x coordinate
		@param y The vector's y coordinate
		@param z The vector's z coordinate
	*/
	Vector3(int x, int y, int z);

	/**
		Instantiates a new Vector3 with coordinates corresponding to a colour direction on the cube.
		@param Colour The colour of the face which the vector will be mapped to.
	*/
	Vector3(Colour inputColour);
	~Vector3();

	/**
		Returns the X coordinate of the vector.
		@return X The X coordinate of the vector.
	*/
	int GetX();

	/**
		Returns the Y coordinate of the vector.
		@return Y The Y coordinate of the vector.
	*/
	int GetY();

	/**
		Returns the Z coordinate of the vector.
		@return Z The Z coordinate of the vector.
	*/
	int GetZ();

	/**
		Returns the colour that the vector corresponds to on the cube's face.
		@return Colour The colour of the face that the vector corresponds to.
	*/
	Colour ToColour();

	/**
		Clones the passed vector into this vector.
	*/
	void CloneVector(Vector3 &inputVector);
	/**
		A static function that takes a colour and creates a new Vector3 with the corresponding coordinates
		@return vector A vector that corresponds the passed colour.
	*/
	Vector3 static ColourToVector(Colour inputColour);

	/**
		Returns the sum of the vector's components.
		@return sum The sum of the vector's components.
	*/
	int Magnitude();

	/**
		Reassigns the vector's components from the passed integers.
		@param X The desired X coordinate
		@param Y The desired Y coordinate
		@param Z The desired Z coordinate
	*/
	void SetVectorFromInts(int X, int Y, int Z);

	/**
		Returns a vector created by taking two or three passed colours, converting them to vectors then summing them.
	*/
	Vector3 static VectorFromColours(std::list<Colour> colours);

	/**
		Returns the cross product performed on the two passed vectors. The cross product vector is in a right-handed 
		coordinate system e.g. the cross product of the unit i and unit j vector produces the unit k vector.
		@param leftVector The left vector in the cross product.
		@param rightVector The right vector in the cross product.
		@return Vector3 The vector produced by the cross product.
	*/
	Vector3 static CrossProduct(Vector3 &leftVector, Vector3 &rightVector);

	/**
	Returns the cross product performed on the two passed colours as vectors . The cross product vector is in a right-handed
	coordinate system e.g. the cross product of the unit i and unit j vector produces the unit k vector.
	@param leftVector The left colour in the cross product.
	@param rightVector The right colour in the cross product.
	@return Vector3 The vector produced by the cross product, returned as a colour.
	*/
	Colour static CrossProduct(Colour &leftColour, Colour &rightColour);

	/**
		Returns a vector created by taking two or three passed colours, converting them to vectors then summing them.
	*/
	std::list<Colour> static ColoursFromVector(Vector3 &inputVector);

	/**
		Determines whether any of the vector's components match up to the passed colour.
		@param searchColour The colour to search the vector's components for.
		@return bool Return true if the searchColour is in the vector's components, otherwise return false.
	*/
	bool CheckVectorForColour( Colour searchColour );

	/**
		Returns true if the passed vector is the same.
		@return bool Returns true if the passed vector is the same.
	*/
	bool Equals(Vector3 &comparisonVector);

private:
	/**
		An integer representing the vector's X coordinate
	*/
	int X;

	/**
		An integer representing the vector's Y coordinate
	*/
	int Y;

	/**
		An integer representing the vector's Z coordinate
	*/
	int Z;

};