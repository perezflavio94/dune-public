#include <algorithm>
#include "Model.h"
#include "View/View.h"
#include "Unit/Harvester.h"
#include "View/UnitViewFactory.h"
#include "Buildings/Barracks.h"
#include "Buildings/HeavyFactory.h"
#include "Buildings/ConstructionYard.h"
#include "Buildings/LightFactory.h"
#include "Buildings/SpiceRefinery.h"
#include "Buildings/SpiceSilo.h"
#include "Buildings/WindTrap.h"

Model::Model(int width, int height, int n_player, View &view) : map(width, height), view(view){
    // reemplazar luego por un vector de players
    for (int i=0; i< n_player; ++i){
        players.emplace(players.end(),i);
    }
}

//Unit &Model::createUnit(int x, int y) {
Unit &Model::createUnit(Unit *unit) {
	units.push_back(std::move(unit));
	map.put(*units.back());
	return *units.back();
}

Building &Model::createBuilding(Building *building) {
	buildings.push_back(std::move(building));
	map.put(*buildings.back());
	return *buildings.back();
}

void Model::step() {
//    for (auto unit : units){
	for (auto itr = units.begin(); itr != units.end(); ++itr) {
//        (*itr)->move();
		(*itr)->makeAction(map);
//        (*itr)->automaticAttack(map);
    }
    this->cleanDeadUnits();
}

Unit *Model::selectUnit(int x, int y) {
	Position aux_pos(x, y);
	return map.getClosestUnit(aux_pos, LIMIT_TO_SELECT);
}

Map &Model::getMap() {
	return map;
}

void Model::cleanDeadUnits() {
    map.cleanDeadUnits();
    bool has_dead_unit = false;
    for (auto u : units){
        if (Unit::isDead(u)){
            has_dead_unit = true;
            delete u;
        }
    }
    if (has_dead_unit){
        units.erase(std::remove_if(units.begin(), units.end(), Unit::isDead));
    }
}

Player &Model::getPlayer(int player) {
    return players.at(player);
}

Model::~Model() {
    for (auto unit : units){
        delete unit;
    }
    for (auto building : buildings){
        delete building;
    }
}

void Model::createHarvester(int x, int y, int player) {
    Harvester* harvester = new Harvester(x,y);
    harvester->setPlayer(players.at(player)); //Quitar luego y hacer player.add(harvester)
    view.addUnitView(UnitViewFactory::createUnitView(*harvester,view.getWindow()));
    this->createUnit(harvester);
}

void Model::createHeavyInfantry(int x, int y, int player) {
    HeavyInfantry* heavyInfantry = new HeavyInfantry(x,y);
    heavyInfantry->setPlayer(players.at(player)); //Quitar luego y hacer player.add(heavyInfantry)
    view.addUnitView(UnitViewFactory::createUnitView(*heavyInfantry,view.getWindow()));
    this->createUnit(heavyInfantry);
}

void Model::createLightInfantry(int x, int y, int player) {
    LightInfantry* lightInfantry = new LightInfantry(x,y);
    lightInfantry->setPlayer(players.at(player)); //Quitar luego y hacer player.add(lightInfantry)
    view.addUnitView(UnitViewFactory::createUnitView(*lightInfantry,view.getWindow()));
    this->createUnit(lightInfantry);
}

void Model::createRaider(int x, int y, int player) {
    Raider* raider = new Raider(x,y);
    raider->setPlayer(players.at(player)); //Quitar luego y hacer player.add(raider)
    view.addUnitView(UnitViewFactory::createUnitView(*raider,view.getWindow()));
    this->createUnit(raider);
}

void Model::createTank(int x, int y, int player) {
    Tank* tank = new Tank(x,y);
    tank->setPlayer(players.at(player)); //Quitar luego y hacer player.add(tank)
    view.addUnitView(UnitViewFactory::createUnitView(*tank,view.getWindow()));
    this->createUnit(tank);
}

void Model::createTrike(int x, int y, int player) {
    Trike* trike = new Trike(x,y);
    trike->setPlayer(players.at(player)); //Quitar luego y hacer player.add(trike)
    view.addUnitView(UnitViewFactory::createUnitView(*trike,view.getWindow()));
    this->createUnit(trike);
}

// Se deben crear las vistas de cada edificio (o la fabrica de vistas para los edificios)
void Model::createBarracks(int x, int y, int player) {
    Barracks* building = new Barracks(x, y);
    // player.add(barracks);
    view.addBuildingView(std::move(new BuildingView(*building, view.getWindow())));
    this->createBuilding(std::move(building));
}

void Model::createConstructionYard(int x, int y, int player) {
    ConstructionYard* building = new ConstructionYard(x, y);
    // player.add(barracks);
    view.addBuildingView(std::move(new BuildingView(*building, view.getWindow())));
    this->createBuilding(std::move(building));
}

void Model::createHeavyFactory(int x, int y, int player) {
    HeavyFactory* building = new HeavyFactory(x, y);
    // player.add(barracks);
    view.addBuildingView(std::move(new BuildingView(*building, view.getWindow())));
    this->createBuilding(std::move(building));
}

void Model::createLightFactory(int x, int y, int player) {
    LightFactory* building = new LightFactory(x, y);
    // player.add(barracks);
    view.addBuildingView(std::move(new BuildingView(*building, view.getWindow())));
    this->createBuilding(std::move(building));
}

void Model::createSpiceRefinery(int x, int y, int player) {
    SpiceRefinery* building = new SpiceRefinery(x, y);
    // player.add(barracks);
    view.addBuildingView(std::move(new BuildingView(*building, view.getWindow())));
    this->createBuilding(std::move(building));
}

void Model::createSpiceSilo(int x, int y, int player) {
    SpiceSilo* building = new SpiceSilo(x, y);
    // player.add(barracks);
    view.addBuildingView(std::move(new BuildingView(*building, view.getWindow())));
    this->createBuilding(std::move(building));
}

void Model::createWindTrap(int x, int y, int player) {
    WindTrap* building = new WindTrap(x, y);
    // player.add(barracks);
    view.addBuildingView(std::move(new BuildingView(*building, view.getWindow())));
    this->createBuilding(std::move(building));
}
