#include "Graph.h"

#include <iostream>	//used for debug purposes
#include <GL/glew.h> // window management library
#include <GL/glfw3.h>

using namespace std;

extern int window_width_g;
extern int window_height_g;
extern float cameraZoom;
extern float aspectRatio;


//class used to compare 2 nodeTuple structs

class compareNode
{
public:
	int operator() (const QNode& n1, const QNode& n2)
	{
		return n1.cost > n2.cost;
	}
};

//main constructor
//takes the width, height of graph, as well as a gameobject used to render each node.
Graph::Graph(int nodeWidth, int nodeHeight, GameObject nodeSprite) : nodeObj(nodeSprite) {
	//initializes the 2d nodes array and nodeMap
	Node::resetNodeCount();

	std::vector<std::vector<Node*>*> nodes;
	nodeMap = std::map<int, Node*>();
	//data for setting node positions on screen.
	float movementX = 1.0;
	float movementY = -1.0f;
	nodeWid = nodeWidth;
	size = nodeWidth * nodeHeight - 1;

	//sometimes missing nodes in center because of the rounding to nearest whole, this shouldn't be a problem in practice because you'll define your own graphs
	// you could round these vals to fix it but then its not centered anymore, but you'll probably just change both of these to 0 for your project anyway.
	start_x = (double)nodeWidth* movementX * -0.5 + 0.5f;   //0.0f
	start_y = (double)nodeHeight * movementY * -0.5 - 0.5f; //0.0f
	//fills the 2d nodes array with nodes.
	for (int i = 0; i < nodeHeight; i++) {
		std::vector<Node*>* nodeRow = new std::vector<Node*>();

		for (int j = 0; j < nodeWidth; j++) {
			//creates each node, starting at (start_x, start_y), topLeft, going down, right

			Node* newNode = new Node(start_x + j* movementX, start_y + i* movementY);
			nodeRow->push_back(newNode);

		}
		nodes.push_back(nodeRow);
	}
	//connects node to each other to form a 4-connected graph with random edge weights
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.at(i)->size(); j++) {

			//if there exists a node to the right of the current node, link them together
			if (j + 1 < nodes.at(i)->size()) {
				int randWeight = 10 + (rand() % 6);	//creates a random weight between 10-15

				Node *n1 = nodes.at(i)->at(j);		//referncec to current node in graph.
				Node *n2 = nodes.at(i)->at(j + 1);	//reference to node to the left of the current node.

				n1->addNode(*n2, randWeight);			//links both nodes together
			}

			//if there exists a node below the current node, link them together
			if (i + 1 < nodes.size()) {
				int randWeight = 10 + (rand() % 6);	//creates a random weight between 10-15

				Node *n1 = nodes.at(i)->at(j);		//referncec to current node in graph.
				Node *n2 = nodes.at(i + 1)->at(j);	//node below the current node.

				n1->addNode(*n2, randWeight);			//links both nodes together
			}
		}
	}
	//adds all nodes to map with nodeId as key and a pointer to the node
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.at(i)->size(); j++) {
			nodeMap.insert(std::pair<int, Node*>(nodes.at(i)->at(j)->getId(), nodes.at(i)->at(j)));
		}
	}

	std::vector<Node*> tempVec;
	for (std::map<int, Node*>::iterator it = nodeMap.begin(); it != nodeMap.end(); ++it) {
		//std::cout << "#:" << it->first << " x:" << it->second->getX() << " y:" << it->second->getY() << std::endl;
		tempVec.push_back(it->second);
	}


	formatNodes(tempVec);

	//sets the start/end nodes to the top_left and bottom_right nodes.
	setStart(0);
	setEnd(nodeWidth * nodeHeight - 1);
	pathfind();
}


Graph::Graph(std::vector<Node*>& nodes, GameObject nodeSprite) : nodeObj(nodeSprite) {
	nodeMap = std::map<int, Node*>();
	nodeVec = std::vector<std::vector<Node*>*>();

	formatNodes(nodes);

	setStart(0);
	setEnd(nodeMap.size()-1);
	pathfind();
}

//structures the nodes for later access
void Graph::formatNodes(std::vector<Node*>& nodes) {
	//adds all nodes to map with nodeId as key and a pointer to the node
	for (int i = 0; i < nodes.size(); i++) {
		nodes.at(i)->setX(round(nodes.at(i)->getX()));
		nodes.at(i)->setY(round(nodes.at(i)->getY()));
		nodeMap.insert(std::pair<int, Node*>(nodes.at(i)->getId(), nodes.at(i)));
	}

	std::sort(nodes.begin(), nodes.end(), Node::sortByY);
	minX = nodes.front()->getX();
	minY = nodes.front()->getY();

	float lastY = minY;
	
	Node* lastNode = NULL;
	for (std::vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		if ((*it)->getX() < minX) {
			minX = (*it)->getX();
		}
		if ((*it)->getY() < minY) {
			minY = (*it)->getY();
		}
		std::vector<Node*>* tempVec = new std::vector<Node*>;
		if (lastNode != NULL) {
			tempVec->push_back(lastNode);
			lastY = lastNode->getY();
		}
		else {
			lastY = (*it)->getY();
		}
		while (it != nodes.end()) {
			if (lastY == (*it)->getY()) {
				tempVec->push_back(*it);
				lastY = (*it)->getY();
			}
			else {
				lastNode = *it;
				if (std::next(it, 1) == nodes.end()) {
					std::sort(tempVec->begin(), tempVec->end(), Node::sortByX);
					nodeVec.push_back(tempVec);
					tempVec = new std::vector<Node*>;
					tempVec->push_back(lastNode);
				}
				break;
			}
			++it;
		}
		
		std::sort(tempVec->begin(), tempVec->end(), Node::sortByX);

		//error checking
		Node* n = NULL;
		for(Node* ele : *tempVec) {
			if (n != NULL && n->getX() == ele->getX()) {
				std:: cout << "ERROR: NODES CANNOT SHARE COORDS: ID " << ele->getId() << " & " << n->getId();
				throw "ya done goof'd. Check console to see the problematic nodes ^.";
			}
			n = ele;
		}
		nodeVec.push_back(tempVec);
		if (it == nodes.end()) { 
			break;
		}
	}
}

//these two searches are used to find the node the mouse is hovering on
int Graph::binarySearchY(std::vector<std::vector<Node*>*> vec, int l, int r, int dist){
	while (l <= r) {
		int m = l + (r - l) / 2;
		if (m < 0 || m >= vec.size()) {
			return -1;
		}
		// Check if x is present at mid 
		float yVal = vec.at(m)->front()->getY();
		if (yVal - minY == dist) {
			return m;
		}
		// If x greater, ignore left half 
		if (yVal - minY < dist) {
			l = m + 1;
		}
		// If x is smaller, ignore right half 
		else {
			r = m - 1;
		}
	}
	// if we reach here, then element was 
	// not present 
	return -1;
}

int Graph::binarySearchX(std::vector<Node*>* vec, int l, int r, int dist){
	while (l <= r) {
		int m = l + (r - l) / 2;
		if (m < 0 || m >= vec->size()) {
			return -1;
		}
		// Check if x is present at mid 
		float xVal = vec->at(m)->getX();
		if (xVal - minX == dist) {
			return m;
		}
		// If x greater, ignore left half 
		if (xVal - minX < dist) {
			l = m + 1;
		}
		// If x is smaller, ignore right half 
		else {
			r = m - 1;
		}
	}
	// if we reach here, then element was 
	// not present 
	return -1;
}



//Loops through array and prints out associated data for each node.
void Graph::printData() {
	for (int i = 0; i < nodeVec.size(); i++) {
		for (int j = 0; j < nodeVec.at(i)->size(); j++) {
			cout << i << ", " << j << " - " << nodeVec.at(i)->at(j)->getId() << " - " << &nodeVec.at(i)->at(j);
			cout << " - " << nodeVec.at(i)->at(j)->getEdges().size() << endl;
		}
	}
}

//gets mouse input, updates start and end position using that information
void Graph::update() {
	double xpos, ypos;
	glfwGetCursorPos(Window::getWindow(), &xpos, &ypos);
	//std::cout << "mouse coords: (" << xpos << "," << ypos << ")" << std::endl; //uncomment if interested
	//gets the node corresponding the mouseclick
	int n = selectNode(xpos, ypos);
	hover = n;

	if (glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		
		//set the start to selected node, if node exists and is not the end-node.
		if (n != -1 && n != endNodeId) {
			setStart(n);
		}
		pathfind();
	}

	if (glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

		//set the start to selected node, if node exists and is not the start-node.
		if (n != -1 && n != startNodeId) {
			setEnd(n);
		}
		pathfind();
	}
}



//returns the id of the node at the mouse coordinates
int Graph::selectNode(double x, double y) {

	glfwGetWindowSize(Window::getWindow(), &window_width_g, &window_height_g);
	//if the mouse is outside the window, return -1
	if (x < 0 || x > window_width_g || y < 0 || y > window_height_g) {
		return -1;
	}
	else {
		float cursor_x_pos = ((x + 0.5f) / (float)(window_width_g / 2.0f)) - 1.0f;
		float cursor_y_pos = 1.0f - ((y + 0.5f) / (float)(window_height_g / 2.0f));

		cursor_x_pos /= (cameraZoom*aspectRatio); //only x is scaled by using the aspect ratio atm.
		cursor_y_pos /= cameraZoom;	//transforms cursor position based on screen scale. used to be const 0.2

		int x = round(cursor_x_pos - minX);
		int y = round(cursor_y_pos - minY);

		int yindex = binarySearchY(nodeVec, 0, nodeVec.size()-1, y);
		if (yindex < 0 || yindex >= nodeVec.size()) {
			return -1;
		}
		int xindex = binarySearchX(nodeVec.at(yindex), 0, nodeVec.at(yindex)->size()-1, x);
		if (xindex == -1) {
			return -1;
		}
		int tryId = nodeVec.at(yindex)->at(xindex)->getId();
		std::cout << "tryId: " << tryId << std::endl;
		return tryId;
	}
}

//renders all the nodes in the graph
void Graph::render(Shader &shader) {

	//goes through each node and renders it, using the provided gameObject
	for (int j = 0; j < nodeVec.size(); j++) {
		
		if (nodeVec.size() == 0) {	//if there are no nodes, do nothing.
			return;
		}

		//get the location of the color uniform
		GLint color_loc = glGetUniformLocation(shader.getShaderID(), "colorMod");

		for (int i = 0; i < nodeVec.at(j)->size(); i++) {
			//gets the current node to draw
			Node currentNode = *(nodeVec.at(j)->at(i));

			//set the node 'pen' to the position of the current node.
			nodeObj.setPosition(glm::vec3(currentNode.getX(), currentNode.getY(), 0.0f));
			
			//set the color of the node via the color uniform. Default is green
			glUniform3f(color_loc, -0.15f, -0.15f, -0.15f);	//green

			//change the color uniform depending on if the node is the start or end node.
			if (currentNode.getId() == startNodeId) {
				glUniform3f(color_loc, 1.0f, -1.0f, -1.0f);	//red = start
			}
			else if (currentNode.getId() == endNodeId) {
				glUniform3f(color_loc, -1.0f, -1.0f, 1.0f); //blue = end
			}else if (hover == currentNode.getId()) {
				glUniform3f(color_loc, 1.0f, -0.4f, 1.0f);//pink = hovering over 
			}
			else if (currentNode.isOnPath()) {
				glUniform3f(color_loc, -0.4f, -0.4f, -0.4f);//dark green = on path
			}
			
			nodeObj.render(shader);
		}
	}
}

//returns a reference to the node with the supplied id.
Node& Graph::getNode(int id) {
	
	//because we also store the graph as a map with the id as the key, we can easily reference each node.
	return *nodeMap.at(id);
}

//using zombie-key based approach to Djikstra's algorithm, returns a vec with nodes on path from startNode to endNode inclusive
std::vector<Node*> Graph::pathfind() {

	//priority queue used in pathfinding.
	//it is created using the NodeTuple struct with a min compare function called compareNode
	priority_queue < QNode, vector<QNode>, compareNode> pq;
	//sets the costs of all nodes to infinity. reset all nodes to be off-path
	pathNodes.clear();
	for (int i = 0; i < nodeVec.size(); i++) {
		for (int j = 0; j < nodeVec.at(i)->size(); j++) {
			nodeVec.at(i)->at(j)->setCost(INT_MAX);
			nodeVec.at(i)->at(j)->setOnPath(false);
		}
	}

	//The startnode is added to the pq with cost 0
	QNode startNode = {&getNode(startNodeId), 0};
	pq.push(startNode);
	
	//now that the pq is setup, we can start the algorithm
	//keep in mind that the as the QNode struct has a pointer to the corresponding node
	//some function calls will use pointer syntax (->) 
	
	
	while (!pq.empty()) {
		//get the current lowest-cost node in pq
		QNode lowest = pq.top();
		
		//if the current node is the end node, done!
		if (lowest.node->getId() == endNodeId) {
			break;
		}

		//OPEN NODE
		vector<Edge> neighbours = lowest.node->getEdges();
		for (int i = 0; i < neighbours.size(); i++) {

			//compute cost to get to neighbouring node
			//cost = the cost to get the corrent node + cost to traverse the edge
			
			Node *n = &getNode(lowest.node->getOtherNode(neighbours.at(i)).getId());
			//Node *n = &(lowest.node->getOtherNode(neighbours.at(i)));
			
			int nodeCost = lowest.cost + neighbours.at(i).cost;

			//if current node cost is higher than calculated, update node, and add QNode to queue			
			if (n->getCost() > nodeCost) {
				n->setCost(nodeCost);	
				n->setPrev(lowest.node);
				
				QNode updatedNode = {n, nodeCost };
				pq.push(updatedNode);
			}
		}

		pq.pop();	//REMOVE NODE FROM QUEUE
	}

	//queue is done, go in reverse from END to START to determine path
	Node* currentNode = getNode(endNodeId).getPrev();
	
	//while the current node isn't null, or the end, mark the current node as on the path
	
	pathNodes.push_back(&getNode(endNodeId));
	while (currentNode != NULL && currentNode->getId() != startNodeId) {
		pathNodes.push_back(currentNode);
		currentNode->setOnPath(true);
		currentNode = currentNode->getPrev();
	}
	pathNodes.push_back(currentNode);
	std::reverse(pathNodes.begin(), pathNodes.end());
	//remove this, just for you to see the ids in order on the path 
	for (Node* ele : pathNodes) {
		std::cout << "id:" << ele->getId() << std::endl;
	}
	return pathNodes;

}