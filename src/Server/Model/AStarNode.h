#ifndef __ASTARNODE_H__
#define __ASTARNODE_H__

#include "Position.h"
#include "Model/Map.h"
#include <vector>

struct AStarNode {
	AStarNode();
	explicit AStarNode(Position pos);
	std::vector<AStarNode> getAdjacents(Map &map);

	bool operator==(const AStarNode& other) const;

	int f, g, h;
	Position pos;
};

#endif //__ASTARNODE_H__
