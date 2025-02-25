#ifndef __ATTACKER_H__
#define __ATTACKER_H__

#include "Model/Weapons/Weapon.h"

class Attackable;

class Attacker {
protected:
    const Weapon& weapon;
    const int range;
    int actual_frec;
    bool shooting;
public:
    Attacker(const Weapon& weapon, const int range);
    virtual void shoot(Attackable &defender);
    const Weapon& getWeapon();
    virtual void attack(Attackable &defender);
    bool isShooting();
};

#endif //__ATTACKER_H__
