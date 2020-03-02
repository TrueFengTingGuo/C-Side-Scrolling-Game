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

//return the partial map depends on the player location
vector<vector<string>> Map::loadPartialMap(glm::vec3 playerPosition)
{

	vector<vector<string>> twoDTemp;
	int col_range = 10;
	int row_range = 10;

	float imageSize = 1.0f; // image size of the map block
	float partialMapX_axis = col_range * imageSize;
	float partialMapY_axis = row_range * imageSize;


	//load only the block which are near the player
	for (int col_count = 0; col_count < col_range; col_count++) {

		vector<string> temp;//save a row of block

		for (int row_count = 0; row_count < row_range; row_count++) {
			if ((row_count* imageSize + playerPosition.x < (partialMapX_axis/2 + playerPosition.x) && row_range * imageSize + playerPosition.y < (partialMapY_axis/2 + playerPosition.y)) ||
				(row_range * imageSize + playerPosition.x > (-partialMapX_axis / 2 + playerPosition.x) && row_range * imageSize + playerPosition.y > (-partialMapY_axis / 2 + playerPosition.y))) {

				temp.push_back(aLevelMap[row_count][col_count]);
			}
		}
		twoDTemp.push_back(temp);
	}

	return twoDTemp;
}
