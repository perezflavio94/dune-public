#include "UnitView.h"
#include "UnitViewFactory.h"
#include "TrikeView.h"
#include "../Unit/trike.h"
#include "HarvesterView.h"
#include "../Unit/harvester.h"
#include "LightInfantryView.h"
#include "../Unit/light-infantry.h"
#include "HeavyInfantryView.h"
#include "../Unit/heavy-infantry.h"


UnitView* UnitViewFactory::createUnitView(Trike& trike, SdlWindow& window){
    return new TrikeView(trike,window);
}

UnitView* UnitViewFactory::createUnitView(Harvester& harvester, SdlWindow& window){
    return new HarvesterView(harvester,window);
}

UnitView* UnitViewFactory::createUnitView(LightInfantry& lightInfantry
            ,SdlWindow& window)
{
    return new LightInfantryView(lightInfantry,window);
}

UnitView* UnitViewFactory::createUnitView(HeavyInfantry& heavyInfantry
                                        ,SdlWindow& window)
{
    return new HeavyInfantryView(heavyInfantry,window);
}