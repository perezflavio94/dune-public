#include <Model/GameConfiguration.h>
#include "ConstructionYard.h"

ConstructionYard::ConstructionYard(const int x, const int y, int blockWidth, int blockHeight) :
        Building(x, y, blockWidth, blockHeight,
                 GameConfiguration::getConfig().constructionYardEnergy,
                 GameConfiguration::getConfig().constructionYardCost,
                 GameConfiguration::getConfig().constructionYardHitPoints,
                 GameConfiguration::getConfig().constructionYardWidth,
                 GameConfiguration::getConfig().constructionYardHeight,
                 CONSTRUCTION_YARD)
{}

ConstructionYard::~ConstructionYard() {}
