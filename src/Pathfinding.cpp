#include "Pathfinding.hpp"


void Pathfinder::pathfind(std::vector<Node>& nodes, Node* start_node, Node* end_node) {
	std::vector<Node*> open_nodes;
	std::vector<Node*> closed_nodes;

	open_nodes.push_back(start_node);

	while (open_nodes.size() > 0) {
		Node* node = open_nodes[0];
		int id = 0;
		for (int i = 1; i < open_nodes.size(); i++) {
			auto& opnode = open_nodes[i];
			if (opnode->f_cost < node->f_cost || opnode->f_cost == node->f_cost) {
				if (opnode->h_cost < node->h_cost) {
					node = opnode;
					id = i;
				}
			}
		}

		closed_nodes.push_back(node);
		open_nodes.erase(open_nodes.begin() + id);

		node = closed_nodes.back();

		for (auto& n : this->getNeighbours(nodes, node)) {

			if (!n->walkable || this->contains(closed_nodes, *n))
				continue;
			
			const int new_cost_to_neighbour = node->g_cost + this->getDistanceConst(*node, *n);
			if (new_cost_to_neighbour < n->g_cost || !this->contains(open_nodes, *n)) {
				n->g_cost = new_cost_to_neighbour;
				n->h_cost = this->getDistanceConst(*n,*end_node);
				n->f_cost = n->g_cost + n->h_cost;
				n->parent = node;

				if (*n == end_node) {
					this->retracePath(n, start_node);
					return;
				}

				if (!this->contains(open_nodes, *n))
					open_nodes.push_back(n);
			}
			
		}
		
	}
	
	//LOG("sus");
}

void Pathfinder::retracePath(Node* end_node, Node* start_node) {
	Node* current_node = end_node;
	current_node->sign = '@';
	while (*current_node != start_node) {
		//LOG("sus");
		current_node->sign = '@';
		current_node = current_node->parent;
		/*if (current_node == nullptr || current_node->parent == nullptr)
			break;*/
	}
	current_node->sign = '@';
}

int Pathfinder::getIndex(const int X, const int Y) const {
	return Y* SIZE_X + X;
}

int Pathfinder::getDistanceConst(const Node& n1, const Node& n2) const {
	int dstX = abs(static_cast<int>(n1.x - n2.x));
	int dstY = abs(static_cast<int>(n1.y - n2.y));

	if (dstX > dstY)
		return 14 * dstY + 10 * (dstX - dstY);
	return 14 * dstX + 10 * (dstY - dstX);
}

bool Pathfinder::contains(std::vector<Node*> nodes, const Node& node) const {
	for (auto& n : nodes)
		if (*n == &node)
			return true;
	return false;
}

std::vector<Node*> Pathfinder::getNeighbours(std::vector<Node>& nodes, Node* current_node) {
	std::vector<Node*> neighbours;
	// ta fukcja bieerze sobei b rac
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			const int X = current_node->x + x;
			const int Y = current_node->y + y;

			if (X < 0 || Y < 0 || X > SIZE_X - 1 || Y > SIZE_Y - 1)
				continue;

			if (x == 0 && y == 0)
				continue;

			const int index = this->getIndex(X, Y);

			if (index < 0 || index > nodes.size() - 1)
				continue;

			neighbours.push_back(&nodes[index]);
		}
	}
	return neighbours;
}
