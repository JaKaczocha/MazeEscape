/*
 * Map.cpp
 *
 *  Created on: 31 sty 2024
 *      Author: User
 */

#include <Map.h>



Map::Map(const uint16_t* array2D, uint16_t numberOfRows, uint16_t numberOfCols) : numRows(numRows), numCols(numCols), map(array2D)
{
	
}


Map::~Map()
{
    
}

const uint16_t* Map::getMap() const
{
    return map;
}
