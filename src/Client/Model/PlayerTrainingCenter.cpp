#include "PlayerTrainingCenter.h"
#include "Unit/Unit.h"

PlayerTrainingCenter::PlayerTrainingCenter(nlohmann::json& j) : m() {
    update(j);
}

void PlayerTrainingCenter::update(nlohmann::json& j) {
    m.lock();
    for (unsigned i = 0; i < j["units"].size(); i++) {
        units[j["units"][i]] = j["time"][i];
    }
    m.unlock();
}

bool PlayerTrainingCenter::isTrainingLightInfantry() {
    return (units.at(Unit::LIGHT_INFANTRY) > 0);
}
bool PlayerTrainingCenter::isTrainingHeavyInfantry() {
    return (units.at(Unit::HEAVY_INFANTRY) > 0);
}

bool PlayerTrainingCenter::isTrainingHarvester() {
    return (units.at(Unit::HARVESTER)  > 0);
}

bool PlayerTrainingCenter::isTrainingTank() {
    return (units.at(Unit::TANK)  > 0);
}

bool PlayerTrainingCenter::isTrainingRaider() {
    return (units.at(Unit::RAIDER)  > 0);
}

bool PlayerTrainingCenter::isTrainingTrike() {
    return (units.at(Unit::TRIKE)  > 0);
}

void PlayerTrainingCenter::beginTraining(Unit::UnitType type) {
    units.at(type) = 1;
}

int PlayerTrainingCenter::remainingTime(Unit::UnitType unitType) {
    m.lock();
    int answer = units.at(unitType);
    m.unlock();
    return answer;
}
