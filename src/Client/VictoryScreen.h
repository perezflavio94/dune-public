#ifndef __VICTORYSCREEN_H__
#define __VICTORYSCREEN_H__


#include "VictoryScreenView.h"
#include "VictoryScreenHandler.h"

class VictoryScreen {
public:
    VictoryScreen(VictoryScreenView& view, VictoryScreenHandler& handler);

    void run();

private:
    VictoryScreenView& view;
    VictoryScreenHandler& handler;
};


#endif //__VICTORYSCREEN_H__
