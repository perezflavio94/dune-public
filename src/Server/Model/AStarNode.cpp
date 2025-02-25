#include "Model/AStarNode.h"
#include "Model/Map.h"
#include <vector>

std::vector<AStarNode> AStarNode::getAdjacents(Map &map) {
    std::vector<AStarNode> vec;
    for (int i = -1 ; i <= 1 ; ++i) {
        for (int j = -1 ; j <= 1 ; ++j) {
            Position p(pos.getX() + i * BLOCK_HEIGHT, pos.getY() + j * BLOCK_WIDTH);
            if ((i != 0 || j != 0) && map.isValid(p)) {
                vec.push_back(AStarNode(p));
            }
        }
    }
    return std::move(vec);
}

AStarNode::AStarNode(Position pos) : f(0), g(0), h(0), pos(pos) {
    this->pos.normalizeToBlock();
}

bool AStarNode::operator==(const AStarNode &other) const {
    return other.pos == this->pos;
}

AStarNode::AStarNode() :
    f(0),
    g(0),
    h(0),
    pos(0, 0) {}
