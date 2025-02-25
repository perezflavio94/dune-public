#include "RaiderView.h"
#include "Model/Unit/Raider.h"
#include "SdlTexture.h"
#include "SdlWindow.h"
#include "Orientation.h"
#include <Area.h>
#include <map>
#include <iostream>
#include <vector>
#include <memory>
#include <Path.h>
#include "Sound.h"

std::map<int, std::unique_ptr<SdlTexture>> RaiderView::raider_sprites;
std::map<int, std::vector<std::unique_ptr<SdlTexture> > > RaiderView::attack_sprites;
std::vector<std::unique_ptr<SdlTexture> > RaiderView::dead_sprites;
std::unique_ptr<Mix_Chunk> RaiderView::deathFx;


RaiderView::RaiderView(Raider& raider, SdlWindow& window) :
	OffensiveUnitView(raider, Area(0, 0, 30, 30), window) {
    
	if (!deathFx) {
        deathFx = std::move(std::unique_ptr<Mix_Chunk>(Mix_LoadWAV(Path::rootVar("assets/sound/fx/rocket explosion.wav").c_str())));
    }
	if (raider_sprites.empty()) {
		raider_sprites.emplace(std::make_pair(Orientation::indefinida(), std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000a08e6.bmp"), window))));
		raider_sprites.emplace(std::make_pair(Orientation::norte(), std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/0009e6d8.bmp"), window))));
		raider_sprites.emplace(std::make_pair(Orientation::noroeste(), std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/0009eb8b.bmp"), window))));
		raider_sprites.emplace(std::make_pair(Orientation::oeste(), std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/0009f4f4.bmp"), window))));
		raider_sprites.emplace(std::make_pair(Orientation::sudoeste(), std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/0009fe42.bmp"), window))));
		raider_sprites.emplace(std::make_pair(Orientation::sur(), std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000a038f.bmp"), window))));
		raider_sprites.emplace(std::make_pair(Orientation::sudeste(), std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000a08e6.bmp"), window))));
		raider_sprites.emplace(std::make_pair(Orientation::este(), std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000a1090.bmp"), window))));
		raider_sprites.emplace(std::make_pair(Orientation::noreste(), std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/000a1992.bmp"), window))));

		std::vector<std::unique_ptr<SdlTexture> > norte;
		norte.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-n1.bmp"), window)));
		norte.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-n2.bmp"), window)));
		attack_sprites.emplace(std::make_pair(Orientation::norte(),
		                                      std::move(norte)));

		std::vector<std::unique_ptr<SdlTexture> > noroeste;
		noroeste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-nw1.bmp"), window)));
		noroeste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-nw2.bmp"), window)));
		attack_sprites.emplace(std::make_pair(Orientation::noroeste(),
		                                      std::move(noroeste)));

		std::vector<std::unique_ptr<SdlTexture> > oeste;
		oeste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-w1.bmp"), window)));
		oeste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-w2.bmp"), window)));
		attack_sprites.emplace(std::make_pair(Orientation::oeste(),
		                                      std::move(oeste)));

		std::vector<std::unique_ptr<SdlTexture> > sudoeste;
		sudoeste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-sw1.bmp"), window)));
		sudoeste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-sw2.bmp"), window)));
		attack_sprites.emplace(std::make_pair(Orientation::sudoeste(),
		                                      std::move(sudoeste)));

		std::vector<std::unique_ptr<SdlTexture> > sur;
		sur.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-s1.bmp"), window)));
		sur.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-s2.bmp"), window)));
		attack_sprites.emplace(std::make_pair(Orientation::sur(),
		                                      std::move(sur)));

		std::vector<std::unique_ptr<SdlTexture> > sudeste;
		sudeste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-se1.bmp"), window)));
		sudeste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-se2.bmp"), window)));
		attack_sprites.emplace(std::make_pair(Orientation::sudeste(),
		                                      std::move(sudeste)));

		std::vector<std::unique_ptr<SdlTexture> > este;
		este.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-e1.bmp"), window)));
		este.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-e2.bmp"), window)));
		attack_sprites.emplace(std::make_pair(Orientation::este(),
		                                      std::move(este)));

		std::vector<std::unique_ptr<SdlTexture> > noreste;
		noreste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-ne1.bmp"), window)));
		noreste.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/trike-ne2.bmp"), window)));

		attack_sprites.emplace(std::make_pair(Orientation::noreste(),
		                                      std::move(noreste)));

		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e004b.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e06d5.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e10e6.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e1d2a.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e2729.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e30a6.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e3d02.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e591c.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e6697.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e744d.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e81c8.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e8dcf.bmp"), window)));
		dead_sprites.emplace_back(std::unique_ptr<SdlTexture>(new SdlTexture(Path::rootVar("assets/img/sprites/002e99b9.bmp"), window)));
	}
}

void RaiderView::draw(Area& camara) {
	if (offensiveUnit.isAttacking() && (offensiveUnit.isShooting() || animating_attack)) {
		drawAttack(camara, attack_sprites);
	} else {
		animating_attack = false;
		UnitView::draw(camara, raider_sprites);
	}
}

std::vector<std::unique_ptr<SdlTexture> >& RaiderView::getDeadSprites() {
    Sound::getSound()->playDeathFx(deathFx.get());	
	return dead_sprites;
}

Area RaiderView::getDeadUnitSrcArea() {
	return Area(0, 0, 80, 80);
}

Area RaiderView::getDeadUnitDestArea() {
	return Area(0, 0, 40, 40);
}
