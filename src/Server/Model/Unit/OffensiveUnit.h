#ifndef __OffensiveUnit_H__
#define __OffensiveUnit_H__

#include "Model/Attacker.h"

#include "Model/Unit/Unit.h"

#include "Model/Map.h"

class OffensiveUnit : public Unit, public Attacker {
public:
	OffensiveUnit(const int x, const int y, const int hitPoints, const int range,
	              const Weapon &weapon, const int speed, const int cost);

	virtual UnitState * makeFollow(Map &map) override;
	virtual UnitState * makeAttack(Map &map) override;
	virtual UnitState * makeStopped(Map &map) override;
	virtual UnitState * makeDefending(Map &map) override;

	bool automaticAttack(Map &map);

	Position& getVictimPosition();
//    bool attacking;
private:
	Position victim_pos;
//    void follow(Unit* other, Map& map);
//private:
//    Unit* foll_unit;
//    Position prev_foll_unit_pos;
};

#endif //__OffensiveUnit_H__
