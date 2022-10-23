#ifndef _Private_Private_h
#define _Private_Private_h

#include <CtrlLib/CtrlLib.h>
#include <SqlCtrl/SqlCtrl.h>

#include "Private/Tables/sqlIncludes.h"

using namespace Upp;

#define LAYOUTFILE <Private/Private.lay>
#include <CtrlCore/lay.h>

class Private : public WithPrivateLayout<TopWindow> {
public:
		Private();
};

#endif
