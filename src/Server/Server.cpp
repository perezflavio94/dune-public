#define _POSIX_C_SOURCE 200112L
#include <sys/socket.h>
#include <chrono>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <yaml-cpp/yaml.h>

#include "Server.h"
#include "Model/Model.h"
#include "CustomException.h"
#include "GameInterface.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_timer.h>

Server::Server(const char *service, const char* mapFile) :
	commonQueue(),
	mapLayout(mapFile),
	maxPlayers(mapLayout.getPlayers()),
	manualShutDown(false),
	acceptSkt(nullptr, service, AI_PASSIVE),
	players(),
	model(mapFile) {
	this->acceptSkt.bind();
	this->acceptSkt.listen(MAX_LISTEN);
}

Server::~Server() {
	if (!manualShutDown) {
		this->shutdown();
	}
}

void Server::shutdown() {
	this->manualShutDown = true;
	this->disconectAllPlayers();
	this->acceptSkt.shutdown(SHUT_RDWR);
	this->acceptSkt.close();
}

Socket Server::accept() const {
	try {
		int peerSkt = this->acceptSkt.accept();
		if (peerSkt == -1) {
			throw CustomException("Server error");
		}
		return Socket(peerSkt);
	} catch (const std::runtime_error &error) {
		throw CustomException("Server error");
	}
}

void Server::waitPlayers() {
	GameInterface interface(model);
	std::cout << "Start to accept Players" << std::endl;
	for (unsigned i = 0; i < this->maxPlayers; ++i) {
		this->players.push_back(new AcceptedPlayer(*this));
		std::cout << "Player Accepted!" << std::endl;
	}
	std::cout << "Start Program!!!" << std::endl;
	for (unsigned i = 0; i < this->maxPlayers; ++i) {
		this->players[i]->start();
		std::string house = commonQueue.dequeue()["house"];
		std::string name = commonQueue.dequeue()["playerName"];
		model.addPlayer(house, name);
		this->players[i]->setId(i);
	}

	nlohmann::json step;
	step["class"] = "Step";

	for (unsigned i = 0; i < this->maxPlayers; ++i) {
		this->players[i]->queue.enqueue(model.getMap().getSerialization());
		this->players[i]->queue.enqueue(model.getPlayer(this->players[i]->getId()).getSerialization());
		this->players[i]->queue.enqueue(GameConfiguration::getConfig().initWithJson());
		this->players[i]->queue.enqueue(model.getPlayer(this->players[i]->getId()).getConstructionYard().getSerialization());

		for (unsigned j = 0; j < this->maxPlayers; ++j) {
			this->players[i]->queue.enqueue(model.getPlayer(j).getSerialization());
			this->players[i]->queue.enqueue(model.getPlayer(this->players[j]->getId()).getConstructionYard().getSerialization());
		}
		this->players[i]->queue.enqueue(step);
	}




	const int time_step = SECOND / MAX_FPS;
	int sleep_extra = 0;
	while (!model.isGameFinished() && !players.empty()) {
		unsigned int loop_init = SDL_GetTicks();
		model.serialize(players);
        model.step();
		this->cleanDisconectedPlayers();
		if (!commonQueue.recvEmpty())
			interface.execute(commonQueue.dequeue());

		unsigned int loop_end = SDL_GetTicks();

		int step_duration = (loop_end - loop_init);
		int sleep_delay = time_step - step_duration - sleep_extra;
		sleep_delay = (sleep_delay < 0) ? 0 : sleep_delay;

		SDL_Delay(sleep_delay);
		unsigned int delay_end = SDL_GetTicks();

		sleep_extra = (delay_end - loop_end) - sleep_delay;
	}
	model.serialize(players);
}

void Server::cleanDisconectedPlayers() {
    auto itr = std::remove_if(this->players.begin(), this->players.end(),
                   [](AcceptedPlayer *&player) {
                       if (!player->is_alive()){
                           delete player;
                           return true;
                       }
                       return false;
                   });
    if (itr != players.end()){
        players.erase(itr, this->players.end());    
    }
}

void Server::disconectAllPlayers() {
	std::for_each(this->players.begin(), this->players.end(),
				  [](AcceptedPlayer *&AcceptedPlayer) {
//					  AcceptedPlayer->disconnect();
					  delete AcceptedPlayer;
				  });
	players.clear();
}
