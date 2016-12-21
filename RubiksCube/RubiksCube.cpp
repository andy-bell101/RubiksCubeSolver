// RubiksCube.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Vector3.h"

using namespace std;

int main()
{
	cout << "Hi there!" << endl;
	
	Vector3 testVector{0,0,1};
	Colour testColour = testVector.ToColour();

    return 0;
}

