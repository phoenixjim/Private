#ifndef _Private_Private_h
#define _Private_Private_h

#include <CtrlLib/CtrlLib.h>
#include <SqlCtrl/SqlCtrl.h>

#include "Private/Tables/sqlIncludes.h"

using namespace Upp;

#define LAYOUTFILE <Private/Private.lay>
#include <CtrlCore/lay.h>
struct AddPass : public WithAddPassLayout<TopWindow> {
	public:
		SqlCtrls ctrls;
		AddPass();
		AddItem();
};

class Private : public WithPrivateLayout<TopWindow> {
public:
		AddPass ap;
		Private();
void	AddPW();
};

#endif
