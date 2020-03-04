#include "Map.h"

Map::Map()
{
	
	ifstream inData;
	inData.open("Map.csv");

	map_height = 0;

	if (inData.is_open()) {
		while (!inData.eof()) {
			vector<string> newRow;

			string line;

			//get one row of csv
			getline(inData, line, '\n'); 

			int count = 0;
			while (line.length() > count) {
				map_width = 0;
				if (line.at(count) != ',') {
					string lineElement(1, line.at(count)); // char to string
					newRow.push_back(lineElement); 
					count += 2;
					map_width += 1;
				}
				else if (line.at(count) == ',') {
					newRow.push_back(" ");
					count += 1;
					map_width += 1;
				}
			}
			map_height += 1;
			aLevelMap.push_back(newRow);
		}

		inData.close();
	}
	else {
		cout << "Unable to open file." << endl;
	}
	
	
}

//return true if a new map is created
bool Map::loadPartialMap(glm::vec3 playerPosition)
{

	
	int col_searching_range = 10;
	int row_searching_range = 10;

	glm::vec2 inGameWallSize  = glm::vec2(1.0f,1.0f);

	//find player position on the table
	glm::vec2 playerPositionOnTheTable;
	playerPositionOnTheTable.x = round(playerPositionOnTheTable.x / inGameWallSize.x);
	playerPositionOnTheTable.y = round(playerPositionOnTheTable.y / inGameWallSize.y);

	// if player is outside the map
	if (playerPositionOnTheTable.x > paritalLoadedMap_botRight.x || playerPositionOnTheTable.x < paritalLoadedMap_topLeft.x
		|| playerPositionOnTheTable.y > paritalLoadedMap_botRight.y || playerPositionOnTheTable.y < paritalLoadedMap_topLeft.y) {
	
		//empty the partial map vector and create a new one
		
		twoDTemp.empty();

		//limit all searching range
		int rowStart = playerPositionOnTheTable.x - row_searching_range;
		int rowEnd = playerPositionOnTheTable.x + row_searching_range;
		if (rowStart < 0) {
			rowStart = 0;
		}
		else if (rowEnd > map_width) {
			rowEnd = map_width;
		}

		int colStart = playerPositionOnTheTable.y - col_searching_range;
		int colEnd = playerPositionOnTheTable.y + col_searching_range;
		if (colStart < 0) {
			colStart = 0;
		}
		else if (rowEnd > map_width) {
			colEnd = map_height;
		}

		//save the parital map range
		paritalLoadedMap_topLeft = glm::vec2(rowStart, colStart);
		paritalLoadedMap_botRight = glm::vec2(rowEnd, colEnd);

		//create a new partial map
		for (colStart; colStart < colEnd; colStart++) {
			vector<string> temp;
			for (rowStart; rowStart < rowEnd; rowStart++) {
				temp.push_back(aLevelMap[colStart][rowStart]);
			}
			twoDTemp.push_back(temp);
		}
		return true;
	}
	else {
		return false;
	}
}
