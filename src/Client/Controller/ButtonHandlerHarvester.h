#ifndef __BUTTON_HANDLER_HARVESTER_H__
#define __BUTTON_HANDLER_HARVESTER_H__

#include "ButtonHandler.h"

class ButtonHandlerHarvester : public ButtonHandler {
public:
	ButtonHandlerHarvester(Player& player, GameView &view, CommunicationQueue& queue);

	virtual ~ButtonHandlerHarvester() = default;

	virtual void execute() override;

    virtual bool canBeEnabled() override;

	virtual bool finishAction() override;
};

#endif  // __BUTTON_HANDLER_HARVESTER_H__
