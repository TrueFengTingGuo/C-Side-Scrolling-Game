#pragma once
using namespace std;

#include "Node.h"
#include "Shader.h"
#include "Window.h"
#include "common.h"

#include <queue>
#include <map>
#include <algorithm>

#include <string>

//struct used to rank various nodes in the priority_queue
struct QNode {
	Node* node;
	int cost;
};

class Graph {
public:
	//constructor. 
	Graph(glm::vec3 playerPosition, vector<vector<string>>&map);
	Graph(std::vector<Node*>&);

	void formatNodes(std::vector<Node*>& nodes);

	//Loops through array and prints out associated data for each node.
	void printData();

	//gets mouse input, updates start and end position using that information
	void update();


	//returns the id of a node from an x/y coordinate
	int selectNode(double x, double y);

	//returns the id of a node from an x/y game coordinate
	int selectNodeUsingGameCood(float x_axis, float y_axis);

	int selectNodeUsingTable(int row, float col);

	//returns a reference to the node with the supplied id.
	Node& getNode(int id);

	//renders all the nodes in the graph
	void render(Shader& shader);

	//creates and marks a path from start to end
	std::vector<Node*> pathfind();

	//setters
	inline void setStart(int nodeId) { if (nodeId != -1)startNodeId = nodeId; }
	inline void setEnd(int nodeId) { endNodeId = nodeId; }

	//getters
	inline int getStartId() { return startNodeId; }
	inline int getEndId() { return endNodeId; }
	//inline std::vector<Node*> getPath() { return pathNodes; };

	//get next node that player is going to use, delete it by the way
	inline glm::vec3 popNodeFromPath() {

		if (pathNodes.size() > 0) {

			float x = (*(pathNodes.begin()))->getX();
			float y = (*(pathNodes.begin()))->getY();

			(*(pathNodes.begin()))->setOnPath(false);// so the node is not on path anymore

			pathNodes.erase(pathNodes.begin());
			glm::vec3 nextNode = glm::vec3(x, -y, 0.f);
			return nextNode;
		}

	}

	inline int sizeOfPathNodes() {
		return pathNodes.size();
	}





private:

	//id of start and endnode
	int startNodeId, endNodeId;
	float start_x;
	float start_y;
	//2d vector containing all the nodes in the graph
	//std::vector<std::vector<Node>> nodes;
	std::vector<std::vector<Node*>*> nodeVec;

	std::vector<Node*> pathNodes;

	int nodeWid;
	int size;
	//map used for easy access to nodes via id
	std::map<int, Node*> nodeMap;
	int hover;

	float minX;
	float minY;

	int binarySearchY(std::vector<std::vector<Node*>*> vec, int l, int r, int dist);
	int binarySearchX(std::vector<Node*>* vec, int l, int r, int dist);
};