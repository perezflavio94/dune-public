#ifndef __BUILDINGVIEW_H__
#define __BUILDINGVIEW_H__


#include "../Buildings/Building.h"
#include "SdlWindow.h"
#include "Area.h"
#include "SdlTexture.h"

class BuildingView {
public:
    BuildingView(Building& building);
    Building& getBuilding(); 
    virtual void draw(Area& camara) = 0;
protected:
    Building& building;
    Position pos;
    bool destroyed;
private:

};


#endif //__BUILDINGVIEW_H__
