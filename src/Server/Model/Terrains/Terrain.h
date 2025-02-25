#ifndef __TERRAIN_H__
#define __TERRAIN_H__

class Building;

class Terrain {
protected:
	char key;
	bool occupied;
	bool builtOn;
	int speed_factor;

public:
	Terrain();

	explicit Terrain(char key);

	void occupy();
	virtual void buildOn(Building* building);
	virtual void free();
	bool isOccupied();
	bool isBuiltOn();
	virtual int farm();
	virtual int getSpice();
	virtual bool hasFarm();
	virtual Building* getBuilding();
	int getSpeedFactor();

	bool operator==(const Terrain& terrain);

	virtual char getKey();
};

#endif	// __TERRAIN_H__
