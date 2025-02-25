#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <Model/Attackable.h>
#include <vector>
#include <nlohmann/json.hpp>

class Player;

class Building : public Attackable {
public:
	enum BuildingType {
		BARRACKS,
		CONSTRUCTION_YARD,
		HEAVY_FACTORY,
		LIGHT_FACTORY,
		SPICE_REFINERY,
		SPICE_SILO,
		WIND_TRAP
	};

	Building(const int x, const int y, int blockWidth, int blockHeight, const int energy, const int cost,
	         const int hitPoints, const int width,
	         const int height, BuildingType type);

	virtual ~Building();

	bool operator==(const Building& other);

	virtual void reciveBonusDammage(const Weapon &weapon) override;
    virtual int getCapacity();

	bool is(BuildingType type);
	void setPlayer(Player* player);
	Player* getPlayer();

	Position& getClosestPosition(Position& position) override;

	void demolish();

	nlohmann::json& getSerialization();

	bool hasNews();

	const int id;
	const int width, height;
	const int energy;
	const int cost;

private:
	static int counter;
	Player* player;
	BuildingType key;
	std::vector<Position> all_positions;

protected:
    bool news;
	nlohmann::json serialization;
};

#endif //__BUILDING_H__
