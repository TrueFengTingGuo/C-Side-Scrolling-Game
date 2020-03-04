#include "Map.h"

Map::Map()
{
	
	ifstream inData;
	inData.open("Map.csv");

	if (inData.is_open()) {
		while (!inData.eof()) {
			vector<string> newRow;

			string line;

			//get one row of csv
			getline(inData, line, '\n'); 

			int count = 0;
			while (line.length() > count) {
				if (line.at(count) != ',') {
					string lineElement(1, line.at(count)); // char to string
					newRow.push_back(lineElement); 
					count += 2;

				}
				else if (line.at(count) == ',') {
					newRow.push_back(" ");
					count += 1;
				}
			}
			
			aLevelMap.push_back(newRow);
		}
		inData.close();
	}
	else {
		cout << "Unable to open file." << endl;
	}
	
	
}

//return the partial map depends on the player location
vector<vector<string>> Map::loadPartialMap()
{
	return aLevelMap;
}
