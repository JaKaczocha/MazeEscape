/*
 * Map.h
 *
 *  Created on: 31 sty 2024
 *      Author: User
 */

#ifndef MAP_H_
#define MAP_H_

#include <cstdint>  // Include the header for uint16_t

class Map {
public:
	Map(const uint16_t* array2D, uint16_t numberOfRows, uint16_t numberOfCols);
    ~Map();

	const uint16_t* getMap() const;
private:
	const uint16_t* map;
	uint16_t numRows, numCols;
};

#endif /* MAP_H_ */
