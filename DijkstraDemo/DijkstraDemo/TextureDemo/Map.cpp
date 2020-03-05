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
			map_width = 0;
			while (line.length() > count) {
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

		cout << "Map size: " << map_width << ", " << map_height << endl;

		inData.close();
	}
	else {
		cout << "Unable to open file." << endl;
	}
}

//return true if a new map is created
bool Map::loadPartialMap(glm::vec3 playerPosition)
{
	/*
	for (int colCount = 0; colCount < aLevelMap.size(); colCount++) {
		cout << colCount;
		cout << "size: "<< aLevelMap[colCount].size();
		for (int rowCount = 0; rowCount < aLevelMap[colCount].size(); rowCount++) {
			cout << aLevelMap[colCount][rowCount];
		}
		cout << endl;
	}
	*/
	int col_searching_range = 10;
	int row_searching_range = 10;

	glm::vec2 inGameWallSize  = glm::vec2(1.0f,1.0f);

	//find player position on the table
	glm::vec3 playerPositionOnTheTable = playerPosition;
	playerPositionOnTheTable.x = round(playerPositionOnTheTable.x / inGameWallSize.x) ;
	playerPositionOnTheTable.y = -round(playerPositionOnTheTable.y / inGameWallSize.y) ;

	//cout << "(" << playerPositionOnTheTable.x << ", " << playerPositionOnTheTable.y << ")" << "|" << "(" << aLevelMap[0].size() << ", " << map_height << ")" << endl;

	if (playerPositionOnTheTable.x < 0 || playerPositionOnTheTable.x > aLevelMap[0].size()
		|| playerPositionOnTheTable.y < 0 || playerPositionOnTheTable.y > map_height) {
		cout << "Player outside map" << endl;
		return false;
	}
	
	// if player is outside the map
	
	if (playerPositionOnTheTable.x > paritalLoadedMap_botRight.x || playerPositionOnTheTable.x < paritalLoadedMap_topLeft.x
		|| playerPositionOnTheTable.y > paritalLoadedMap_botRight.y || playerPositionOnTheTable.y < paritalLoadedMap_topLeft.y) {
	
		std::cout << "outside" << std::endl;
		//empty the partial map vector and create a new one
		
		twoDTemp.empty();

		//limit all searching range
		int rowStart = playerPositionOnTheTable.x - row_searching_range;
		int rowEnd = playerPositionOnTheTable.x + row_searching_range;

		cout << "row before adding " << rowStart << " , " << rowEnd << endl;
		if (rowStart < 0) {
			rowStart = 0;
		}
		if (rowEnd > aLevelMap[0].size()-1) {
			rowEnd = aLevelMap[0].size() - 1;
		}
		
		int colEnd = playerPositionOnTheTable.y + col_searching_range;
		int colStart = playerPositionOnTheTable.y - col_searching_range;
		cout << "col before adding " << colStart << " , " << colEnd << endl;
		if (colEnd > map_height - 1) {
			colEnd = map_height - 1;
		}
		if (colStart < 0) {
			colStart = 0 ;
		}

		cout << rowStart << " , " << rowEnd << endl;
		cout << colStart << " , " << colEnd << endl;

		//save the parital map range
		paritalLoadedMap_topLeft = glm::vec2(rowStart, colStart);
		paritalLoadedMap_botRight = glm::vec2(rowEnd, colEnd);

		//create a new partial map
		for (int colCount = colStart ; colCount < colEnd; colCount++) {
			vector<string> temp;
			for (int rowCount = rowStart; rowCount < rowEnd; rowCount++) {
				//cout << colCount << " , " << rowCount ;
				cout << aLevelMap[colCount][rowCount] ;
				temp.push_back(aLevelMap[colCount][rowCount]);
				
			}
			twoDTemp.push_back(temp);
			cout << endl;
		}

		return true;
		
	}
	else {
		return false;
	}
}
