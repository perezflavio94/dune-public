#ifndef __BUTTON_HANDLER_HEAVY_FACTORY_H__
#define __BUTTON_HANDLER_HEAVY_FACTORY_H__

#include "ButtonHandler.h"

class ButtonHandlerHeavyFactory : public ButtonHandler {
public:
	ButtonHandlerHeavyFactory(Player& player, GameView &view,
			BuildingConstructor& constructor, CommunicationQueue& queue);

	~ButtonHandlerHeavyFactory();

	virtual void execute() override;

	virtual bool canBeEnabled() override;

	virtual bool finishAction() override;

	virtual void executeReady() override;

	virtual bool finishReady() override;

private:
	BuildingConstructor& constructor;
};

#endif  // __BUTTON_HANDLER_HEAVY_FACTORY_H__
