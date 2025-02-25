#include "SelectorView.h"
#include "Selector.h"
#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include "Sound.h"
#include <Path.h>

SelectorView::SelectorView(Selector& selector, SdlWindow& window) :
    window(window),
    selector(selector),
    drag_rect(),
    max_life(),
    current_life(),
    selectionFx()
{
    max_life.h = 4;
    current_life.h = 4;
    selectionFx.insert(std::make_pair(Unit::HARVESTER, Mix_LoadWAV(Path::rootVar("assets/sound/fx/harvester.wav").c_str())));
    selectionFx.insert(std::make_pair(Unit::LIGHT_INFANTRY, Mix_LoadWAV(Path::rootVar("assets/sound/fx/light inf.wav").c_str())));
    selectionFx.insert(std::make_pair(Unit::HEAVY_INFANTRY, Mix_LoadWAV(Path::rootVar("assets/sound/fx/heavy inf.wav").c_str())));
    selectionFx.insert(std::make_pair(Unit::RAIDER, Mix_LoadWAV(Path::rootVar("assets/sound/fx/raider.wav").c_str())));
    selectionFx.insert(std::make_pair(Unit::TRIKE, Mix_LoadWAV(Path::rootVar("assets/sound/fx/trike.wav").c_str())));
    selectionFx.insert(std::make_pair(Unit::TANK, Mix_LoadWAV(Path::rootVar("assets/sound/fx/tank.wav").c_str())));
}

SelectorView::~SelectorView() {
    for (auto fx : selectionFx) {
        Mix_FreeChunk(fx.second);
    }
}

void SelectorView::drawLife(Building* building, Area& camara) {
    max_life.w = building->getInitialLife() / 4;
    if (max_life.w > 80)
        max_life.w = 80;
    max_life.x = building->getPosition().x  - camara.getX();
    max_life.y = building->getPosition().y + 10 - camara.getY();
    Area life_area(max_life);
    if (camara.anyInteract(life_area)) {
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 0xFF);
        SDL_RenderFillRect(window.getRenderer(), &max_life);
    }
    float factor = float(building->getLife()) / float(building->getInitialLife());
    current_life.w = max_life.w * factor;
    current_life.x = max_life.x;
    current_life.y = max_life.y;
    int r, g;
    if (factor < 0.65) {
        if (factor < 0.3) {
            r = 128;
            g = 0;
        } else {
            r = 160;
            g = 160;
        }
    } else {
        r = 0;
        g = 128;
    }
    if (camara.anyInteract(life_area)) {
        SDL_SetRenderDrawColor(window.getRenderer(), r, g, 0, 0xFF);
        SDL_RenderFillRect(window.getRenderer(), &current_life);
    }
}

void SelectorView::drawLife(Unit* unit, Area& camara) {
    max_life.w = unit->getInitialLife() / 2;
    max_life.x = unit->getPosition().x - 20 - camara.getX();
    max_life.y = unit->getPosition().y + 10 - camara.getY();
    if (max_life.w > 80)
        max_life.w = 80;
    Area life_area(max_life);
    if (camara.anyInteract(life_area)) {
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 0xFF);
        SDL_RenderFillRect(window.getRenderer(), &max_life);
    }
    float factor = float(unit->getLife()) / float(unit->getInitialLife());
    current_life.w = max_life.w * factor;
    current_life.x = max_life.x;
    current_life.y = max_life.y;
    int r, g;
    if (factor < 0.65) {
        if (factor < 0.3) {
            r = 128;
            g = 0;
        } else {
            r = 160;
            g = 160;
        }
    } else {
        r = 0;
        g = 128;
    }
    if (camara.anyInteract(life_area)) {
        SDL_SetRenderDrawColor(window.getRenderer(), r, g, 0, 0xFF);
        SDL_RenderFillRect(window.getRenderer(), &current_life);
    }
}

void SelectorView::drawSelection(Area& camara) {
    SDL_SetRenderDrawBlendMode(window.getRenderer(), SDL_BLENDMODE_NONE);
    std::vector<Unit*>& units = selector.selection.getSelectedUnits();
    std::vector<Unit*>::iterator units_it = units.begin();
    while (units_it != units.end()) {
        drawLife((*units_it), camara);
        units_it++;
    }
    std::vector<Building*>& buildings = selector.selection.getSelectedBuildings();
    std::vector<Building*>::iterator building_it = buildings.begin();
    while (building_it != buildings.end()) {
        drawLife((*building_it), camara);
        building_it++;
    }
}

void SelectorView::draw(Area& camara) {
    if (selector.newUnits) {
        Sound::getSound()->playSelectionFX(selectionFx.at(selector.selection.getSelectedUnits().front()->getUnitType()));
        selector.newUnits = false;
    }
    if (selector.drag) {
        drag_rect.x = selector.drag_source.x - camara.getX();
        drag_rect.y = selector.drag_source.y - camara.getY();
        drag_rect.w = selector.pos.x - selector.drag_source.x;
        drag_rect.h = selector.pos.y - selector.drag_source.y;
        Area life_area(drag_rect);
        if (camara.anyInteract(life_area)) {
            SDL_SetRenderDrawBlendMode(window.getRenderer(), SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(window.getRenderer(), 0, 128, 0, 0xFF);
            SDL_RenderDrawRect(window.getRenderer(), &drag_rect);
            SDL_SetRenderDrawColor(window.getRenderer(), 0, 128, 64, 80);
            SDL_RenderFillRect(window.getRenderer(), &drag_rect);
        }
    } else {
        drawSelection(camara);
    }
}
