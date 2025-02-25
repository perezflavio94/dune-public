#ifndef __BUTTON_HANDLER_LIGHT_INFANTRY__
#define __BUTTON_HANDLER_LIGHT_INFANTRY__

#include "ButtonHandler.h"

class ButtonHandlerLightInfantry : public ButtonHandler {
public:
	ButtonHandlerLightInfantry(Player& player, GameView &view, CommunicationQueue& queue);

	~ButtonHandlerLightInfantry();

	virtual void execute() override;

	virtual bool canBeEnabled() override;

	virtual bool finishAction() override;
};

#endif	// __BUTTON_HANDLER_LIGHT_INFANTRY__
