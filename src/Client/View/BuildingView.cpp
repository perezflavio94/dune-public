#include "BuildingView.h"
#include "PlayerColorMaker.h"
#include <cstdlib>
#include <memory>
#include <vector>
#include <Path.h>
#include "Sound.h"

std::vector<std::unique_ptr<SdlTexture> > BuildingView::construction_sprites;
std::vector<std::unique_ptr<SdlTexture> > BuildingView::damage_sprites;
std::unique_ptr<Mix_Chunk> BuildingView::alertAttackFx;

BuildingView::BuildingView(Building& building, SdlWindow& window, Area src_area, Area dest_area) :
	building(building),
	window(window),
	life(building.getLife()),
	pos(building.getPosition()),
	destroyed(false),
	src_area(src_area),
	dest_area(dest_area),
	construido(false),
	update_sprite(0),
	damage_sprite_area(Area(0, 0, 15, 15)),
	damage_dest_area(Area(0, 0, 15, 15)),
	damage_anim_it(),
	damage_update(0),
	soundMonitor(false) {
	if (!alertAttackFx) {
		alertAttackFx = std::move(std::unique_ptr<Mix_Chunk>(Mix_LoadWAV(Path::rootVar("assets/sound/fx/building alert.wav").c_str())));
	}
	PlayerColorMaker::makeColor(*building.getPlayer(), &player_r, &player_g, &player_b);
	playerColorRect.x = dest_area.getX();
	playerColorRect.y = dest_area.getY();
	playerColorRect.w = dest_area.getWidth() + 8;
	playerColorRect.h = dest_area.getHeight() + 8;

	if (construction_sprites.empty()) {
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00015966.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00015d83.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000161a0.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000165bd.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000169da.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00016df7.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00017214.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00017631.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00017a4e.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00017e6b.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00018288.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000186a5.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00018ac2.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00018edf.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000192fc.bmp"), window)));
		construction_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/00019719.bmp"), window)));
	}
	construction_it = construction_sprites.begin();

	if (damage_sprites.empty()) {
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002ebc36.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002ebc00.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002ebbb2.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002ebb55.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002eb959.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002eb9fa.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002eba90.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002ebb55.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002ebbb2.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002ebc00.bmp"), window)));
		damage_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002ebc36.bmp"), window)));
	}
	damage_anim_it = damage_sprites.begin();
}

BuildingView::~BuildingView() {}

Building &BuildingView::getBuilding() {
	return building;
}

void BuildingView::drawConstruction(Area& camara) {
	if (!construido) {
		update_sprite++;
		if (camara.anyInteract(dest_area)) {
			(*construction_it)->render(src_area, dest_area);
		}
		if (update_sprite == 1) {
			construction_it++;
			update_sprite = 0;
			if (construction_it == construction_sprites.end()) {
				construido = true;
				construction_it--;
			}
		}
	} else {
		if (construction_it != construction_sprites.end()) {
			if (camara.anyInteract(dest_area)) {
				(*construction_it)->render(src_area, dest_area);
			}
			update_sprite++;
			if (update_sprite == 1) {
				update_sprite = 0;
				if (construction_it == construction_sprites.begin()) {
					construction_it = construction_sprites.end();
				} else {
					construction_it--;
				}
			}
		}
	}
}

void BuildingView::draw(Area& camara,  std::unique_ptr<SdlTexture>& sprite) {
	dest_area.setX(pos.x - camara.getX());
	dest_area.setY(pos.y - camara.getY());
	if (construido) {
		playerColorRect.x = dest_area.getX() - 4;
		playerColorRect.y = dest_area.getY() - 4;
		if (camara.anyInteract(dest_area)) {
			SDL_SetRenderDrawBlendMode(window.getRenderer(), SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(window.getRenderer(), player_r, player_g, player_b, 250);
			SDL_RenderDrawRect(window.getRenderer(), &playerColorRect);
			SDL_SetRenderDrawColor(window.getRenderer(), player_r, player_g, player_b, 30);
			SDL_RenderFillRect(window.getRenderer(), &playerColorRect);

			sprite->render(src_area, dest_area);
		}
		if (life > building.getLife()) {
			life = building.getLife();
			animating_damage = true;
			if (soundMonitor) {
				Sound::getSound()->playUnderAttackFx(alertAttackFx.get());
			}
		}
		if (animating_damage) {
			drawDamage(camara);
		}
	}
	drawConstruction(camara);
}

void BuildingView::draw(Area& camara,  std::unique_ptr<SdlTexture>& sprite, std::unique_ptr<SdlTexture>& base, int base_x, int base_y) {
	dest_area.setX(pos.x - camara.getX());

	dest_area.setY(pos.y - camara.getY());
	if (construido) {
		playerColorRect.x = dest_area.getX() - 8;
		playerColorRect.y = dest_area.getY();
		playerColorRect.w = dest_area.getWidth() + abs(base_x) + 8;
		playerColorRect.h = dest_area.getHeight() + abs(base_y) + 8;
		dest_area.setX(dest_area.getX() + base_x);
		dest_area.setY(dest_area.getY() + base_y);
		if (camara.anyInteract(dest_area)) {
			SDL_SetRenderDrawBlendMode(window.getRenderer(), SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(window.getRenderer(), player_r, player_g, player_b, 250);
			SDL_RenderDrawRect(window.getRenderer(), &playerColorRect);
			SDL_SetRenderDrawColor(window.getRenderer(), player_r, player_g, player_b, 30);
			SDL_RenderFillRect(window.getRenderer(), &playerColorRect);

			base->render(src_area, dest_area);
		}
		dest_area.setX(dest_area.getX() - base_x);
		dest_area.setY(dest_area.getY() - base_y);
		if (camara.anyInteract(dest_area)) {
			sprite->render(src_area, dest_area);
		}

		if (life > building.getLife()) {
			life = building.getLife();
			animating_damage = true;
			if (soundMonitor) {
				Sound::getSound()->playUnderAttackFx(alertAttackFx.get());
			}
		}
		if (animating_damage) {
			drawDamage(camara);
		}
	}
	drawConstruction(camara);
}

void BuildingView::drawDamage(Area& camara) {
	damage_dest_area.setX(dest_area.getX() + dest_area.getWidth() / 4);
	damage_dest_area.setY(dest_area.getY() + dest_area.getHeight() / 4);
	if (camara.anyInteract(damage_dest_area)) {
		(*damage_anim_it)->render(damage_sprite_area, damage_dest_area);
	}
	damage_dest_area.setX(dest_area.getX() + dest_area.getWidth() / 2);
	damage_dest_area.setY(dest_area.getY() + dest_area.getHeight() / 2);
	if (camara.anyInteract(damage_dest_area)) {
		(*damage_anim_it)->render(damage_sprite_area, damage_dest_area);
	}
	if (damage_update == 4) {
		damage_anim_it++;
		damage_update = 0;
		if (damage_anim_it == damage_sprites.end()) {
			animating_damage = false;
			damage_anim_it = damage_sprites.begin();
		}
	} else {
		damage_update++;
	}
}

DeadBuildingView* BuildingView::getDeadBuildingView() {
	return new DeadBuildingView(pos, src_area, dest_area, construction_sprites, player_r, player_g, player_b, window);
}

bool BuildingView::isDead(BuildingView* view) {
	if (view->building.isDead()) {
		return true;
	}
	return false;
}

void BuildingView::setSoundOn() {
	this->soundMonitor = true;
}

void BuildingView::setSoundOff() {
	this->soundMonitor = false;
}
