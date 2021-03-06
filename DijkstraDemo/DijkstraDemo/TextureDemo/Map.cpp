#include "Map.h"

Map::Map(string fileName)
{

	ifstream inData;
	inData.open(fileName);

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
	/*
	for (int colCount = 0; colCount < aLevelMap.size(); colCount++) {
		cout << colCount;
		cout << "size: " << aLevelMap[colCount].size();
		for (int rowCount = 0; rowCount < aLevelMap[colCount].size(); rowCount++) {
			cout << aLevelMap[colCount][rowCount];
		}
		cout << endl;
	}
	cout << aLevelMap.size() << " , " << aLevelMap[aLevelMap.size() - 1].size() << endl;
	*/
}

Map::~Map()
{
	aLevelMap.clear();
	twoDTemp.clear();
}

//return true if a new map is created
bool Map::loadPartialMap(PlayerGameObject* player)
{

	glm::vec3 playerPosition = player->getPosition();
	int col_searching_range = 10;

	glm::vec2 inGameWallSize = glm::vec2(1.0f, 1.0f);

	//find player position on the table
	glm::vec3 playerPositionOnTheTable = playerPosition;
	playerPositionOnTheTable.x = round(playerPositionOnTheTable.x / inGameWallSize.x);
	playerPositionOnTheTable.y = -round(playerPositionOnTheTable.y / inGameWallSize.y);


	// if player is outside the partial map
	if (playerPositionOnTheTable.y > paritalLoadedMap_colRange.y - 2 ) {

		std::cout << "bottom outside" << std::endl;
		//empty the partial map vector and create a new one


		twoDTemp.clear();

		//limit all searching range
		int colEnd = playerPositionOnTheTable.y + col_searching_range;
		int colStart = playerPositionOnTheTable.y - 2;
		
		
		//cout << "col before adding " << colStart << " , " << colEnd << endl;
		if (colEnd > map_height) {
			colEnd = map_height;
		}
		if (colStart < 0) {
			colStart = 0;
		}

		int makeUpRange = 15 - (colEnd - colStart); //if range is too short
		if (makeUpRange > 0) {
			colStart -= makeUpRange;
		}


		if (colStart < 0) {
			colStart = 0;
		}

		cout << colStart << " , " << colEnd << endl;


		//save the parital map range
		paritalLoadedMap_colRange = glm::vec2(colStart, colEnd);
		player->setVelocity(player->getVelocity() * 0.3f);
		return true;

	}
	else if ( playerPositionOnTheTable.y < paritalLoadedMap_colRange.x + 2) {

		std::cout << "top outside" << std::endl;
		//empty the partial map vector and create a new one

		twoDTemp.clear();

		//limit all searching range

		int colEnd = playerPositionOnTheTable.y + 2;
		int colStart = playerPositionOnTheTable.y - col_searching_range;
		

		//cout << "col before adding " << colStart << " , " << colEnd << endl;
		if (colEnd > map_height) {
			colEnd = map_height;
		}
		if (colStart < 0) {
			colStart = 0;
		}

		int makeUpRange = 15- (colEnd - colStart); //if range is too short

		if (makeUpRange > 0) {
			colEnd += makeUpRange;
		}

		if (colEnd > map_height) {
			colEnd = map_height;
		}

		cout << colStart << " , " << colEnd << endl;


		//save the parital map range
		paritalLoadedMap_colRange = glm::vec2(colStart, colEnd);
		player->setVelocity(player->getVelocity() * 0.0f);
		return true;

	}

	else {
		return false;
	}
}
