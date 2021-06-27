#pragma once

struct Node 
{
	Node(unsigned _x = 0, unsigned _y = 0) 
		: x(_x), y(_y) {}

	struct 
	{

		char sign = '0';

		unsigned x, y;

		int g_cost = -1;
		int h_cost = -1;
		int f_cost = -1;

		bool walkable = true;

		Node* parent = nullptr;

	};
	
	bool operator == (const Node* n) const {
		return x == n->x && y == n->y;
	}

	bool operator != (const Node* n) const {
		if (n == nullptr)
			return false;
		return x != n->x || y != n->y;
	}
};
