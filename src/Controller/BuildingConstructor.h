#ifndef __BUILDING_CONSTRUCTOR_H__
#define __BUILDING_CONSTRUCTOR_H__

#include "../Model/Buildings/Building.h"
#include "../Model/Model.h"
#include "../Model/Player.h"
#include "../View/GameView.h"

class GameView;

class BuildingConstructor{
    private:
        Model& model;
        Player& player;
        GameView& view;
    
    
    public:
        bool on;
        Position pos;
        Building::BuildingType building;
        int width, height;
        int cost;

        
        BuildingConstructor(Model& model, Player& player, GameView& view);
        void build();
        bool canWeBuild();
        Player& getPlayer();
};

#endif