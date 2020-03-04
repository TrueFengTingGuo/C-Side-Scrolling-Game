#pragma once

#include "Node.h"
#include "Shader.h"
#include "GameObject.h"
#include "Window.h"
#include "common.h"

#include <queue>
#include <map>
#include <algorithm>

//struct used to rank various nodes in the priority_queue
struct QNode{
	Node *node;
	int cost;
};

class Graph {
public:
	//constructor. 
	Graph(int nodeWidth, int nodeHeight, GameObject nodeSprite);
	Graph(std::vector<Node*>&, GameObject nodeSprite);

	void formatNodes(std::vector<Node*>& nodes);
	
	//Loops through array and prints out associated data for each node.
	void printData();

	//gets mouse input, updates start and end position using that information
	void update();


	//returns the id of a node from an x/y coordinate
	int selectNode(double x, double y);

	//returns a reference to the node with the supplied id.
	Node& getNode(int id);

	//renders all the nodes in the graph
	void render(Shader &shader);

	//creates and marks a path from start to end
	std::vector<Node*> pathfind();

	//setters
	inline void setStart(int nodeId) { startNodeId = nodeId; }
	inline void setEnd(int nodeId) { endNodeId = nodeId; }

	//getters
	inline int getStartId() { return startNodeId; }
	inline int getEndId() { return endNodeId; }



private:
	//node sprite used to draw each node.
	GameObject nodeObj;

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