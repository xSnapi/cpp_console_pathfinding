#pragma once
#include <vector>
#include "Node.h"
#include "Public Variables.h"

class Pathfinder {
public:
	void pathfind(std::vector<Node>& nodes, Node* start_node, Node* end_node);
private:
	void retracePath(Node* end_node, Node* finish_node);
	int getIndex(const int X, const int Y) const;
	int getDistanceConst(const Node& n1, const Node& n2) const;
	bool contains(std::vector<Node*> nodes, const Node& node) const;
	std::vector<Node*> getNeighbours(std::vector<Node>& nodes, Node* current_node);
};