#ifndef _Private_Private_h
#define _Private_Private_h

#include <CtrlLib/CtrlLib.h>
#include <SqlCtrl/SqlCtrl.h>

#include "Private/Tables/sqlIncludes.h"

using namespace Upp;

#define LAYOUTFILE <Private/Private.lay>
#include <CtrlCore/lay.h>
struct AddSite : public WithAddSiteLayout<TopWindow> {
public:
			AddSite();
	void	addNewSite();
};

class Secrets : public WithSecretsLayout<TopWindow> {
public:
			Secrets();
			
			AddSite newsite;
			
};

#endif
